import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("manet-results.csv")

protocols = ['aodv', 'dsdv', 'olsr']
colors = {'aodv': 'tab:blue', 'dsdv': 'tab:orange', 'olsr': 'tab:green'}

# PDR vs Nodes
plt.figure()
for p in protocols:
    data = df[df['Protocol'] == p]
    plt.plot(data['Nodes'], data['PDR'], marker='o', label=p.upper(), color=colors[p])
plt.xlabel("Number of Nodes")
plt.ylabel("Packet Delivery Ratio (%)")
plt.title("PDR vs Number of Nodes")
plt.legend()
plt.grid(True)
plt.savefig("pdr_vs_nodes.png", dpi=300)

# Throughput vs Nodes
plt.figure()
for p in protocols:
    data = df[df['Protocol'] == p]
    plt.plot(data['Nodes'], data['Throughput'], marker='o', label=p.upper(), color=colors[p])
plt.xlabel("Number of Nodes")
plt.ylabel("Throughput (Mbps)")
plt.title("Throughput vs Number of Nodes")
plt.legend()
plt.grid(True)
plt.savefig("throughput_vs_nodes.png", dpi=300)

# Delay vs Nodes
plt.figure()
for p in protocols:
    data = df[df['Protocol'] == p]
    plt.plot(data['Nodes'], data['Delay'], marker='o', label=p.upper(), color=colors[p])
plt.xlabel("Number of Nodes")
plt.ylabel("Average Delay (s)")
plt.title("Delay vs Number of Nodes")
plt.legend()
plt.grid(True)
plt.savefig("delay_vs_nodes.png", dpi=300)

print("Plots saved as: pdr_vs_nodes.png, throughput_vs_nodes.png, delay_vs_nodes.png")
