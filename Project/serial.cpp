#include "mainHelper.h"

string findLUDecompositionUsingSerial(int size, double **input) {
	struct timeval tstart, tend;
	double exectime, **matrix, **lowerMatrix, **upperMatrix, **permutationMatrix;
    	int matrixSize = size;
    	matrix = new double*[size];
	lowerMatrix = new double*[size];
	upperMatrix = new double*[size];
	permutationMatrix = new double*[size];
	for (int i = 0; i < size; ++i){
		matrix[i] = new double[size];
		lowerMatrix[i] = new double[size];
		upperMatrix[i] = new double[size];
		permutationMatrix[i] = new double[size];
	}
    	for (int i = 0; i < matrixSize; i++){
		for(int j = 0; j < matrixSize; j++){
			if(i == j){
				lowerMatrix[i][j] = 1;
				permutationMatrix[i][j] = 1;
			}else{
				lowerMatrix[i][j] = 0;
				permutationMatrix[i][j] = 0;
			}
			
			upperMatrix[i][j] = 0;
			matrix[i][j] = input[i][j];
		}
	}
    	gettimeofday( &tstart, NULL );
    	for(int k = 0; k < matrixSize; k++) {
        	double maxPivot = 0;
        	int swapRowNo = k;
        	for(int i = k; i < matrixSize; i++) {
            		if(abs(matrix[i][k]) > maxPivot) {
                		maxPivot = abs(matrix[i][k]);
                		swapRowNo = i;
            		}
       	 }
        	if(maxPivot == 0) {
            		cout << "Given matrix is singular. LU decomposition can't be calculated.\n";
            		break;
        	}
        	
        	//swap(matrix[k], matrix[swapRowNo]);
			//swap(permutationMatrix[k], permutationMatrix[swapRowNo]);
			for(int i = 0; i < matrixSize; i++){
				int temp = matrix[k][i];
				matrix[k][i] = matrix[swapRowNo][i];
				matrix[swapRowNo][i] = temp;
				temp = permutationMatrix[k][i];
				permutationMatrix[k][i] = permutationMatrix[swapRowNo][i];
				permutationMatrix[swapRowNo][i]  = temp;
          }
        	for(int i = 0; i < k; i++) {
           		swap(lowerMatrix[k][i], lowerMatrix[swapRowNo][i]);
        	}
        	upperMatrix[k][k] = matrix[k][k];
        	for(int i = k+1; i < matrixSize; i++) {
            		lowerMatrix[i][k] = matrix[i][k] / upperMatrix[k][k];
            		upperMatrix[k][i] = matrix[k][i];
        	}
        	for (int i = k + 1; i < matrixSize; ++i){
            		for(int j = k+1; j < matrixSize; j++) {
                		matrix[i][j] -= lowerMatrix[i][k] * upperMatrix[k][j];
            		}
        	}        
    	}
    	gettimeofday( &tend, NULL );
    	exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
    	exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms
    	string stats = to_string(matrixSize)+", " + to_string(exectime/1000.0) + "\n";
    	saveMatrix(lowerMatrix, "lowerMatrix", size);
	saveMatrix(upperMatrix, "upperMatrix", size);
	saveMatrix(permutationMatrix, "permutationMatrix", size);
    	return stats;
}

