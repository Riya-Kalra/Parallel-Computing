#! /usr/bin/python3
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('serialStats', header=None)
serial = []
for index,row in df.iterrows():
	 serial.append(row[1])
df = pd.read_csv('openMPStats', header=None)
#Data preprocessing
thread1 = []
thread2 = []
thread3 = []
thread4 = []
thread5 = []

for index, row in df.iterrows():
	if index % 5 == 0:
		thread1.append(row[2])
	elif index % 5 == 1:
		thread2.append(row[2])
	elif index % 5 == 2:
		thread3.append(row[2])
	elif index % 5 == 3:
		thread4.append(row[2])
	else:
		thread5.append(row[2])
matrixSizeList = list(dict.fromkeys(df[0]))
#Plotting bar chart
plotData = pd.DataFrame({"thread1": thread1, "thread2": thread2,  "thread3": thread3, "thread4": thread4, "thread5": thread5, "serial" : serial}, matrixSizeList)


plotData.plot.bar(width=0.5)
plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='y', alpha=0.7)
plt.title("openMP v/s Serial")
plt.xlabel("Matrix Size")
plt.ylabel("Execution Time(seconds)")
plt.show()

