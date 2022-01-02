#include "mainHelper.h"
using namespace std;
int main(int argc, char** argv) {
	fstream serialFile;
	serialFile.open("serialStats", ios::out);
	fstream pThreadFile;
	pThreadFile.open("pThreadStats", ios::out);
	fstream openMPFile;
	openMPFile.open("openMPStats", ios::out);
   	ifstream file;
   	int matrixSize;
   	double **input;
	if (argc == 2) {
        	file.open(argv[1], ios::in);
        	if (!file.is_open()) {
          		cout << "Can't open the file. Exiting..." << endl;
          		exit(1);
        	}
        	int totalMatrices;
        	file >> totalMatrices;
        	for(int num = 0; num < totalMatrices; num++){
					file >> matrixSize;
					input = new double*[matrixSize];
					
					for (int i = 0; i < matrixSize; i++) {
						input[i] = new double[matrixSize];
		 				for (int j = 0; j < matrixSize; j++) {
		  	 				file >> input[i][j];
		 				}
		  			}
		  			//remove("lowerMatrix");remove("upperMatrix");remove("permutationMatrix");
					//string a = findLUDecompositionUsingSerial(matrixSize, input);
					//remove("lowerMatrix");remove("upperMatrix");remove("permutationMatrix");
					string b = luDecompositionUsingPthread(matrixSize, input);
					//remove("lowerMatrix");remove("upperMatrix");remove("permutationMatrix");
					//string c = findLUDecompositionUsingOpenMP(matrixSize, input);
					//serialFile << a;
					pThreadFile << b;
					//openMPFile << c;
		}
	}
}

