#! /usr/bin/python3
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('serialStats', header=None)
#Data preprocessing
serial = []
for index,row in df.iterrows():
	 serial.append(row[1])
df = pd.read_csv('pThreadStats', header=None)
#Data preprocessing
parallel = []
for index, row in df.iterrows():
	if index % 5 == 3:
		parallel.append(row[2])
df = pd.read_csv('openMPStats', header=None)
#Data preprocessing
openMP = []
for index, row in df.iterrows():
	if index % 5 == 3:
		openMP.append(row[2])
matrixSizeList = list(dict.fromkeys(df[0]))

plotData = pd.DataFrame({"Serial": serial, "pThread": parallel, "openMP": openMP}, matrixSizeList)
plotData.plot.bar(width=0.5)
plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='y', alpha=0.7)
plt.title("Serial-pThread-OpenMP")
plt.xlabel("Matrix Size")
plt.ylabel("Execution Time(seconds)")
plt.show()

