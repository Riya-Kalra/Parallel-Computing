all: main

main:
	g++ -pthread -fopenmp main.cpp serial.cpp  pThread.cpp  openMP.cpp mainHelper.cpp -o main
	
clean:
	rm *.o main
