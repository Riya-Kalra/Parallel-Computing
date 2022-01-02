#!/bin/sh
echo "Clearing matrices files"
make clean
echo "LU decomposition processing...."
make
./main input
echo "Ploting graph..."
echo $(./pThreadGraphPlot.py)
echo $(./openMPGraphPlot.py)
echo $(./lineAll.py)
echo $(./plotAll.py)
