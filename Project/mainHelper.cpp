#include <iostream>
#include <fstream>
using namespace std;

void saveMatrix(double **matrix, string fileName, int size){
	ofstream file;
	file.open(fileName, std::ios_base::app);
	if (!file){
		cerr << "Error: file could not be opened" << endl;
		exit(1);	
	}
	for (int row = 0; row < size; ++row){
		for (int col = 0; col < size; ++col){
			file << matrix[row][col] << " ";
		}
		file << "\n";
	}
}

void printMatrix(double **matrix, int size){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "-------------------------------\n";
}
void generateRandomMatrix(double** matrix, int size){
	matrix = new double*[size];
	for (int i = 0; i < size; ++i){
		matrix[i] = new double[size];
		for (int j = 0; j < size; ++j){
			matrix[i][j] = rand() % 10;	
		}
	}
}
