# MANET Routing Protocol Comparison using NS-3

## Overview

This project implements a comparative performance study of three popular MANET routing protocols:

- AODV (Ad hoc On-Demand Distance Vector)
- DSDV (Destination-Sequenced Distance Vector)
- OLSR (Optimized Link State Routing)

All protocols are evaluated under identical simulation conditions using the NS-3 network simulator to analyze their behavior in mobile ad-hoc networks.

---

## Objectives

- Design reproducible MANET simulation experiments in NS-3  
- Compare reactive and proactive routing protocols  
- Evaluate protocols using standard performance metrics:
  - Packet Delivery Ratio (PDR)
  - End-to-End Delay
  - Throughput
- Analyze performance trade-offs under node mobility

---

## Experimental Setup

- Simulator: NS-3  
- Network Type: Mobile Ad-hoc Network (MANET)  
- Protocols Compared: AODV, DSDV, OLSR  
- Mobility Model: Random Waypoint (change if different)  
- Traffic Type: CBR over UDP (change if different)  
- Evaluation Metrics:
  - Packet Delivery Ratio
  - Average End-to-End Delay
  - Throughput  

All simulations are run with the same topology, number of nodes, mobility pattern, and traffic configuration to ensure a fair comparison.

---

## Methodology

1. Configure a common MANET scenario in NS-3  
2. Run the simulation separately using:
   - AODV
   - DSDV
   - OLSR
3. Collect trace files for each run  
4. Compute:
   - Packet Delivery Ratio
   - End-to-End Delay
   - Throughput  
5. Compare and analyze the results

---

## Project Structure

