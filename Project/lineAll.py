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
plt.plot(matrixSizeList, serial,"red", label ="Serial")
plt.plot(matrixSizeList, parallel,"yellow",  label ="pThread")
plt.plot(matrixSizeList, openMP,"blue",  label ="OpenMP")
plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='y', alpha=0.7)
plt.legend(loc='upper center')
plt.title("Serial-pThread-OpenMP")
plt.xlabel("Matrix Size")
plt.ylabel("Execution Time (seconds)")
plt.show()

