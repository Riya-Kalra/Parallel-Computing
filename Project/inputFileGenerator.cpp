#include <fstream>
using namespace std;
int main(int argc, char** argv) {
	fstream inputFile;
	inputFile.open("input", ios::out);
	int matrixSize = 0;
	inputFile << 20 << "\n";
	for(int i = 50; i <= 1000; i+=50){
		matrixSize = i;
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
}
