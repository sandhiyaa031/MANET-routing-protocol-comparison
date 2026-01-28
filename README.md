# 📡 MANET Routing Protocol Comparison using NS-3

## 🧭 Overview

This project presents a comparative performance study of three popular MANET routing protocols:

- **AODV** (Ad hoc On-Demand Distance Vector)  
- **DSDV** (Destination-Sequenced Distance Vector)  
- **OLSR** (Optimized Link State Routing)

All protocols are evaluated under identical simulation conditions using the **NS-3 network simulator** to analyze their behavior in mobile ad-hoc networks.

---

## 🎯 Objectives

- Design reproducible MANET simulation experiments in NS-3  
- Compare reactive and proactive routing protocols  
- Evaluate protocols using standard performance metrics:
  - Packet Delivery Ratio (PDR)
  - End-to-End Delay
  - Throughput
- Analyze performance trade-offs under node mobility  

---

## 🧪 Experimental Setup

- **Simulator:** NS-3  
- **Network Type:** Mobile Ad-hoc Network (MANET)  
- **Protocols Compared:** AODV, DSDV, OLSR  
- **Mobility Model:** Random Waypoint  
- **Traffic Type:** CBR over UDP  
- **Evaluation Metrics:**
  - Packet Delivery Ratio  
  - Average End-to-End Delay  
  - Throughput  

All simulations are run with the **same topology, number of nodes, mobility pattern, and traffic configuration** to ensure a **fair and controlled comparison**.

---

## 🔬 Methodology

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

## 🗂️ Project Structure
├── scripts/ # NS-3 simulation scripts
├── results/ # Output trace files / processed data
├── plots/ # Graphs for PDR, delay, throughput
└── README.md


---

## ▶️ How to Run

1. Install **NS-3**
2. Copy the script(s) into your NS-3 workspace
3. Run:

```bash
./waf --run "your-script-name"
```
## 📊 Results

### 📉 End-to-End Delay vs Number of Nodes
<img src="https://github.com/user-attachments/assets/a904989f-c040-4e7b-898e-4672ed815eaa" width="400"/>

### 📈 Packet Delivery Ratio vs Number of Nodes
<img src="https://github.com/user-attachments/assets/7f1245c1-e05c-4bc8-ace9-c6ee2409a9a5" width="400"/>

### 🚀 Throughput vs Number of Nodes
<img src="https://github.com/user-attachments/assets/38183c1f-8b28-4cd7-8415-c937b2d2fe5c" width="400"/>

---

## 🧠 Observations

- **AODV** performs well in highly dynamic networks due to on-demand route discovery  
- **OLSR** performs better in relatively stable networks due to proactive routing  
- **DSDV** shows higher overhead when topology changes frequently  

---

## 🛠️ What This Project Demonstrates

- Understanding of MANET routing protocols  
- Hands-on experience with NS-3 simulations  
- Performance evaluation of network protocols  
- Experimental comparison under controlled conditions  

---

## 🚀 Future Work

- Test with different node densities and mobility speeds  
- Add more routing protocols  
- Automate batch simulations and result analysis  

---

## 👩‍💻 Author

**Sandhiya D**
