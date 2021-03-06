#include <pthread.h>
#include <iostream>
#include <climits>
#include <cmath>
#include <fstream>
using namespace std;
double **matrix;
double **lowerMatrix;
double **upperMatrix;
double **permutationMatrix;
int matrixSize = 0;		//size of matrix.
ofstream outputFile;
void save_matrix(double **matrix);
void printMatrix(double **matrix){
	for (int i = 0; i < matrixSize; ++i){
		for (int j = 0; j < matrixSize; ++j){
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "-------------------------------\n";
}
double** mulMat(double **mat1, double **mat2) {
	double **rslt = new double*[matrixSize];
	for (int i = 0; i < matrixSize; ++i){
		rslt[i] = new double[matrixSize];
	}
 
    
 
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            rslt[i][j] = 0;
 
            for (int k = 0; k < matrixSize; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    save_matrix(rslt);
    return(rslt);
}
void areSame(double **A, double **B)
{
    int i, j;
    double **rslt = new double*[matrixSize];
	for (int i = 0; i < matrixSize; ++i){
		rslt[i] = new double[matrixSize];
	
	}
    for (i = 0; i < matrixSize; i++)
        for (j = 0; j < matrixSize; j++)
            rslt[i][j] = A[i][j] - B[i][j];
    save_matrix(rslt);    
}
int main(int argc, char **argv){
    outputFile.open("PA-LU-Testing", std::ios_base::app);
    ifstream file[4];
    file[0].open(argv[1], ios::in);
    file[1].open(argv[2], ios::in);
    file[2].open(argv[3], ios::in);
    file[3].open(argv[4], ios::in);
    int totalMatrices;
    file[0] >> totalMatrices;
    for (int t = 0; t < totalMatrices; ++t){
		file[0] >> matrixSize;
		outputFile <<"Size: " << matrixSize << "\n";
		matrix = new double*[matrixSize];
		
		for (int i = 0; i < matrixSize; i++) {
			matrix[i] = new double[matrixSize];
		  	for (int j = 0; j < matrixSize; j++) {
		    		file[0] >> matrix[i][j];
		  	}
	  	}
	  	
	  	for(int  k = 0; k < 3; k++){
			lowerMatrix = new double*[matrixSize];
			upperMatrix = new double*[matrixSize];
			permutationMatrix = new double*[matrixSize];
			for (int i = 0; i < matrixSize; ++i){
				//matrix[i] = new double[matrixSize];
				lowerMatrix[i] = new double[matrixSize];
				upperMatrix[i] = new double[matrixSize];
				permutationMatrix[i] = new double[matrixSize];
			}
			//cout << "Original Matrix is:\n" << endl;
						//printMatrix(matrix);
	  	
	  		for (int i = 0; i < matrixSize; i++) {
		  		for (int j = 0; j < matrixSize; j++) {
		    			file[1] >> permutationMatrix[i][j];
		  		}
	  		}
	  	
		
	  		for (int i = 0; i < matrixSize; i++) {
		  		for (int j = 0; j < matrixSize; j++) {
		    			file[2] >> lowerMatrix[i][j];
		  		}
	  		}
	  	
		
	  		for (int i = 0; i < matrixSize; i++) {
		  		for (int j = 0; j < matrixSize; j++) {
		    			file[3] >> upperMatrix[i][j];
		 	 	}
	  		}
	  	/*cout << "Original Matrix is:\n" << endl;
		printMatrix(matrix);
		cout << "Permutation Matrix is:\n" << endl;
		printMatrix(permutationMatrix);
		cout << "Lower Matrix is:\n" << endl;
		printMatrix(lowerMatrix);
		cout << "Upper Matrix is:\n" << endl;
		printMatrix(upperMatrix);*/

			outputFile << "Multiplication of lowerMatrix and upperMatrix is:" << endl;
			double** res1 = mulMat(lowerMatrix, upperMatrix);
			outputFile << "Multiplication of permutationMatrix and matrix is:" << endl;
			double** res2 = mulMat(permutationMatrix, matrix);
			outputFile << "Resultant Matrix PA-LU is:" << endl;
			areSame(res1, res2);
		}
	}
}
void save_matrix(double **matrix){
	if (!outputFile){
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
	for (int row = 0; row < matrixSize; ++row){
		for (int col = 0; col < matrixSize; ++col){
			outputFile << matrix[row][col] << " ";
		}
		outputFile << "\n";
	}
	outputFile<<"--------------------------------------------------------------------------\n\n";
}
