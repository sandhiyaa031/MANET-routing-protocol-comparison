#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/wifi-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/aodv-module.h"
#include "ns3/dsdv-module.h"
#include "ns3/dsr-module.h"
#include "ns3/olsr-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include <fstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ManetComparison");

int main (int argc, char *argv[])
{
  // Default parameters
  std::string protocol = "aodv";     // Routing protocol
  uint32_t nWifis = 50;              // Number of nodes
  uint32_t nFlows = 10;              // Number of flows
  uint32_t packetSize = 1024;        // Packet size (bytes)
  double simTime = 150.0;            // Simulation time (s)
  double dataRateMbps = 0.128;       // Flow data rate (Mbps)

  CommandLine cmd;
  cmd.AddValue ("protocol", "Routing protocol: aodv, dsdv, dsr, olsr", protocol);
  cmd.AddValue ("nWifis", "Number of nodes", nWifis);
  cmd.AddValue ("nFlows", "Number of flows", nFlows);
  cmd.AddValue ("packetSize", "Packet size in bytes", packetSize);
  cmd.AddValue ("simTime", "Simulation time in seconds", simTime);
  cmd.AddValue ("dataRate", "Traffic rate per flow (Mbps)", dataRateMbps);
  cmd.Parse (argc, argv);

  // Create nodes
  NodeContainer nodes;
  nodes.Create (nWifis);

  // Position allocator
  Ptr<UniformRandomVariable> randX = CreateObject<UniformRandomVariable> ();
  randX->SetAttribute ("Min", DoubleValue (0.0));
  randX->SetAttribute ("Max", DoubleValue (1500.0));

  Ptr<UniformRandomVariable> randY = CreateObject<UniformRandomVariable> ();
  randY->SetAttribute ("Min", DoubleValue (0.0));
  randY->SetAttribute ("Max", DoubleValue (900.0));

  Ptr<RandomRectanglePositionAllocator> positionAlloc = CreateObject<RandomRectanglePositionAllocator> ();
  positionAlloc->SetX (randX);
  positionAlloc->SetY (randY);

  // Mobility model
  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                             "Speed", StringValue ("ns3::UniformRandomVariable[Min=1.0|Max=20.0]"),
                             "Pause", StringValue ("ns3::ConstantRandomVariable[Constant=2.0]"),
                             "PositionAllocator", PointerValue (positionAlloc));
  mobility.Install (nodes);

  // WiFi setup
  WifiHelper wifi;
  wifi.SetStandard (WIFI_STANDARD_80211b);

  YansWifiPhyHelper wifiPhy;
  wifiPhy.SetChannel (YansWifiChannelHelper::Default ().Create ());

  WifiMacHelper wifiMac;
  wifiMac.SetType ("ns3::AdhocWifiMac");

  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, nodes);

  // Internet + Routing
  InternetStackHelper internet;
  if (protocol == "aodv")
    {
      AodvHelper aodv;
      internet.SetRoutingHelper (aodv);
      internet.Install (nodes);
    }
  else if (protocol == "dsdv")
    {
      DsdvHelper dsdv;
      internet.SetRoutingHelper (dsdv);
      internet.Install (nodes);
    }
  else if (protocol == "olsr")
    {
      OlsrHelper olsr;
      internet.SetRoutingHelper (olsr);
      internet.Install (nodes);
    }
  else if (protocol == "dsr")
    {
      // DSR has its own installation sequence
      internet.Install (nodes);
      DsrMainHelper dsrMain;
      DsrHelper dsr;
      dsrMain.Install (dsr, nodes);
    }
  else
    {
      std::cerr << "Unknown protocol: " << protocol << ". Use aodv, dsdv, olsr, or dsr.\n";
      return 1;
    }

  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  // Populate routing tables
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  // Enable PCAP for debugging
  wifiPhy.EnablePcapAll ("manet");

  // Print expected Tx count for verification (safe integer math)
  uint32_t expectedTxPerFlow = static_cast<uint32_t>((dataRateMbps * 1e6 / (packetSize * 8.0)) * (simTime - 2.0));
  std::cout << "Expected packets per flow ≈ " << expectedTxPerFlow
            << "  -> total ≈ " << (uint64_t)expectedTxPerFlow * nFlows << std::endl;

  // Traffic setup
  ApplicationContainer apps;
  // Build a robust DataRate string: if dataRateMbps < 1, use kbps to avoid ambiguity
  std::string rateStr;
  if (dataRateMbps < 1.0)
    {
      int kb = static_cast<int> (std::round (dataRateMbps * 1000.0));
      rateStr = std::to_string (kb) + "kbps";
    }
  else
    {
      // if user sets e.g., 1.5 -> "1.5Mbps"
      rateStr = std::to_string (dataRateMbps) + "Mbps";
    }

  for (uint32_t i = 0; i < nFlows; ++i)
    {
      uint32_t src = i % nWifis;
      uint32_t dst = (nWifis - 1) - (i % nWifis);
      uint16_t port = 9000 + (uint16_t)i;  // unique port per flow

      std::cout << "Flow " << i << ": src=" << src
                << " dst=" << dst
                << " dstIP=" << interfaces.GetAddress (dst)
                << " port=" << port << " rate=" << rateStr << std::endl;

      OnOffHelper onoff ("ns3::UdpSocketFactory",
                         InetSocketAddress (interfaces.GetAddress (dst), port));
      onoff.SetConstantRate (DataRate (rateStr), packetSize);
      apps.Add (onoff.Install (nodes.Get (src)));

      PacketSinkHelper sink ("ns3::UdpSocketFactory",
                             InetSocketAddress (Ipv4Address::GetAny (), port));
      apps.Add (sink.Install (nodes.Get (dst)));
    }

  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (simTime));   // ensure apps run until simTime

  // Flow Monitor setup (with correct start time)
  FlowMonitorHelper flowmon;
  flowmon.SetMonitorAttribute ("StartTime", TimeValue (Seconds (0.0)));
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

  Simulator::Stop (Seconds (simTime));
  Simulator::Run ();

  // Collect results
  monitor->CheckForLostPackets ();
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

  double totalTx = 0, totalRx = 0;
  double sumDelay = 0;
  int countedFlows = 0;
  uint64_t totalRxBytes = 0;

  for (auto &flow : stats)
    {
      if (flow.second.txPackets > 0)
        {
          totalTx += static_cast<double> (flow.second.txPackets);
          totalRx += static_cast<double> (flow.second.rxPackets);
          totalRxBytes += flow.second.rxBytes;

          if (flow.second.rxPackets > 0)
            {
              double delay = flow.second.delaySum.GetSeconds() / static_cast<double> (flow.second.rxPackets);
              sumDelay += delay;
              countedFlows++;
            }
        }
    }

  // Metrics
  double aggregateThroughput = (static_cast<double> (totalRxBytes) * 8.0) / (simTime * 1e6); // Mbps
  double avgDelay = (countedFlows > 0) ? sumDelay / countedFlows : 0;
  double pdr = (totalTx > 0) ? (totalRx / totalTx) * 100.0 : 0;

  // Print summary
  std::cout << "\n========================================\n";
  std::cout << "Protocol: " << protocol << "\n";
  std::cout << "  Nodes: " << nWifis << "  Flows: " << nFlows << "\n";
  std::cout << "  Total Tx: " << totalTx << "\n";
  std::cout << "  Total Rx: " << totalRx << "\n";
  std::cout << "  Aggregate Throughput: " << aggregateThroughput << " Mbps\n";
  std::cout << "  Avg Delay: " << avgDelay << " s\n";
  std::cout << "  Overall PDR: " << pdr << " %\n";
  std::cout << "========================================\n";

  // Save summary to CSV (organized, add header if file doesn't exist)
  bool fileExists = std::ifstream("manet-results.csv").good();
  std::ofstream outFile;
  outFile.open ("manet-results.csv", std::ios::app);
  if (!fileExists)
    {
      outFile << "Protocol,Nodes,Flows,TotalTx,TotalRx,Throughput (Mbps),Average Delay (s),Packet Delivery Ratio (%)\n";
    }
  outFile << protocol << ","
          << nWifis << ","
          << nFlows << ","
          << static_cast<uint64_t> (totalTx) << ","
          << static_cast<uint64_t> (totalRx) << ","
          << aggregateThroughput << ","
          << avgDelay << ","
          << pdr << "\n";
  outFile.close ();

  monitor->SerializeToXmlFile ("manet-results-" + protocol + ".xml", true, true);

  Simulator::Destroy ();
  return 0;
}
