#!/bin/sh
g++ inputG.cpp -o inputG
echo $1
echo $(./inputG $1)
echo "Clearing matrices files"
rm -f PA-LU-Testing lowerMatrix upperMatrix permutationMatrix
echo "Compiling testing file..."
g++ testing.cpp -o testing
echo "Compiling files..."
g++ -pthread -fopenmp main.cpp serial.cpp  pThread.cpp  openMP.cpp mainHelper.cpp -o main
echo "LU decomposition processing...."
./main test.txt
echo "Testing LU Decomposition..."
./testing test.txt permutationMatrix lowerMatrix upperMatrix
echo "Please check PA-LU-Testing file..."
echo $(./pThreadGraphPlot.py)
echo $(./openMPGraphPlot.py)
echo $(./plotAll.py)
