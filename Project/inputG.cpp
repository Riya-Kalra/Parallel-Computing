#include <fstream>
#include <iostream>
 
using namespace std;
int main(int argc, char** argv) {
	fstream inputFile;
	inputFile.open("test.txt", ios::out);
	int matrixSize = 0;
	inputFile << 1 << "\n";
	matrixSize= atoi(argv[1]);
	inputFile << matrixSize << "\n";
	srand (time(NULL));
	//Random matrix is created.
	for (int row = 0; row < matrixSize; row++) {
		for (int col = 0; col < matrixSize; col++) {
			inputFile << rand() % 100 <<" ";
		}
		inputFile << "\n";
	}
}

