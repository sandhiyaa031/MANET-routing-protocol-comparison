# MANET-routing-protocol-comparison
A comparative performance analysis of MANET routing protocols (AODV, DSDV, and OLSR) based on delay, packet delivery ratio, and throughput.
# MANET Routing Protocol Performance Analysis 📡

## Overview
This project presents a comparative performance analysis of Mobile Ad Hoc Network (MANET) routing protocols — **AODV**, **DSDV**, and **OLSR**.  
The evaluation is carried out by analyzing key network performance metrics as the number of nodes increases.

The goal of this project is to study the behavior and efficiency of different MANET routing protocols under varying network sizes.

---

## Routing Protocols Compared
- **AODV (Ad hoc On-Demand Distance Vector)**
- **DSDV (Destination-Sequenced Distance Vector)**
- **OLSR (Optimized Link State Routing)**

---

## Performance Metrics
The following metrics are used for comparison:

- **Average End-to-End Delay**
- **Packet Delivery Ratio (PDR)**
- **Throughput**

---

## Experimental Setup
- Network type: Mobile Ad Hoc Network (MANET)
- Number of nodes: 60 to 130
- Evaluation method: Simulation-based analysis
- Data analysis and plotting performed using Python

---

## Results

### 🔹 Delay vs Number of Nodes
This plot shows how the average end-to-end delay varies as the number of nodes increases for each routing protocol.


---

### 🔹 Packet Delivery Ratio vs Number of Nodes
This plot compares the reliability of each protocol in terms of successful packet delivery.


---

### 🔹 Throughput vs Number of Nodes
This plot illustrates the data transmission efficiency of each routing protocol.


---

## Observations
- OLSR demonstrates stable performance with higher packet delivery ratio as node density increases.
- AODV shows fluctuating delay and throughput due to its on-demand routing nature.
- DSDV exhibits consistent but comparatively lower performance across metrics.

---

## Project Structure
