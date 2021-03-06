#include "mainHelper.h"
#include <pthread.h>

double **matrix;
double **lowerMatrix;
double **upperMatrix;
double **permutationMatrix;
int matrixSize, no_of_thread, threads = 5;

typedef struct arrguments{
	int threadNo;
	int col;
}arg;

int swapRowNo = 0;
    
string luDecompositionUsingPthread(int size, double **input){
	pthread_t t[threads];
	string stats = "";
	struct timeval tstart, tend;
	double exectime;
	matrixSize = size;
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
	
	for (int noOfThreads = 1; noOfThreads <= threads; ++noOfThreads){
		for (int i = 0; i < matrixSize; ++i){
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
		//cout << "Original Matrix is:\n" << endl;
		//printMatrix(matrix,matrixSize);
		gettimeofday( &tstart, NULL );
		no_of_thread = noOfThreads;
		stats += to_string(matrixSize)+", "+to_string(noOfThreads);
		for (int col = 0; col < matrixSize; ++col){
			double maxPivot = 0;
			swapRowNo = col;

			for (int i = col; i < matrixSize; ++i){
				if (abs(matrix[i][col]) > maxPivot){
					maxPivot = abs(matrix[i][col]);
					swapRowNo = i;
				}
			}

			if(maxPivot == 0) {
       			cout << "Given matrix is singular. LU decomposition can't be calculated.\n";
       			break;
   			}
			//swap(matrix[col], matrix[swapRowNo]);
			//swap(permutationMatrix[col], permutationMatrix[swapRowNo]);
			for(int i = 0; i < matrixSize; i++){
				int temp = matrix[col][i];
				matrix[col][i] = matrix[swapRowNo][i];
				matrix[swapRowNo][i] = temp;
				temp = permutationMatrix[col][i];
				permutationMatrix[col][i] = permutationMatrix[swapRowNo][i];
				permutationMatrix[swapRowNo][i]  = temp;
          }
   			int remainingRows = matrixSize - (col + 1);
			while (remainingRows < no_of_thread)
				no_of_thread = no_of_thread / 2;


			for (int threadNo = 0; threadNo < no_of_thread; ++threadNo){
				arg *args = new arg();
				args->threadNo = threadNo;
				args->col = col;
				pthread_create(t+threadNo, NULL, &swappingUsingPthread, (void*)args);
			}

			for (int i = 0; i < no_of_thread; ++i)
				pthread_join(t[i], NULL);
			upperMatrix[col][col] = matrix[col][col];
   			

			for (int threadNo = 0; threadNo < no_of_thread; ++threadNo){
				arg *args = new arg();
				args->threadNo = threadNo;
				args->col = col;
				pthread_create(t+threadNo, NULL, &calculate_lower_upper_matrixUsingPthread, (void*)args);
			}
			for (int i = 0; i < no_of_thread; ++i)
				pthread_join(t[i], NULL);
			//Get the requirment of threads.
			
			for (int threadNo = 0; threadNo < no_of_thread; ++threadNo){
				arg *args = new arg();
				args->threadNo = threadNo;
				args->col = col;
				pthread_create(t+threadNo, NULL, &getLowerUpperMatrixUsingPthread, (void*)args);
			}

			for (int i = 0; i < no_of_thread; ++i)
				pthread_join(t[i], NULL);

		}
		gettimeofday( &tend, NULL );

		exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; 
  		exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; 
 
  		stats += ", "+to_string(exectime/1000.0) + "\n";
	}
	saveMatrix(lowerMatrix, "lowerMatrix", size);
	saveMatrix(upperMatrix, "upperMatrix", size);
	saveMatrix(permutationMatrix, "permutationMatrix", size);
	return stats;
}

void *calculate_lower_upper_matrixUsingPthread(void *tmp){
	arg *args = (arg*)tmp;
	int col = args->col + 1;
	int totalRows = matrixSize - col; //get total rows
	int rowsPerThread = totalRows / no_of_thread;
	if (rowsPerThread == 0)
		rowsPerThread = totalRows;
	int start = col + rowsPerThread*(args->threadNo), end = start + rowsPerThread - 1;

	//Condition for last thread allocation
	if (args->threadNo == no_of_thread-1 or end >= matrixSize)
		end = matrixSize-1;

	for (int i = start; i <= end;++i){ //parallalize
            lowerMatrix[i][col-1] = matrix[i][col-1] / upperMatrix[col-1][col-1];
            upperMatrix[col-1][i] = matrix[col-1][i];
        }
        pthread_exit(NULL);
}
   
void *swappingUsingPthread(void *tmp){
	arg *args = (arg*)tmp;
	int col = args->col ;
	int totalElements = col; //get total rows
	int elementsPerThread = totalElements / no_of_thread;
	if (elementsPerThread == 0)
		elementsPerThread = totalElements;
	int start = elementsPerThread*(args->threadNo), end = start + elementsPerThread - 1;

	//Condition for last thread allocation
	if (args->threadNo == no_of_thread-1 or end >= col)
		end = col-1;

	//cout << args->threadNo << " " << start << " " << end << endl; //Debug
	for(int i = start; i <=end; i++) { //parallalize
            swap(lowerMatrix[col][i], lowerMatrix[swapRowNo][i]);
        }
      	pthread_exit(NULL);
}
void *getLowerUpperMatrixUsingPthread(void *tmp){
	arg *args = (arg*)tmp;
	int col = args->col + 1;
	int totalRows = matrixSize - col; //get total rows
	int rowsPerThread = totalRows / no_of_thread;
	if (rowsPerThread == 0)
		rowsPerThread = totalRows;
	int start = col + rowsPerThread*(args->threadNo), end = start + rowsPerThread - 1;

	//Condition for last thread allocation
	if (args->threadNo == no_of_thread-1 or end >= matrixSize)
		end = matrixSize-1;

	for (int i = start; i <= end;++i){ //parallalize
		for (int j = col; j < matrixSize; ++j){
			matrix[i][j] -= lowerMatrix[i][col-1]*upperMatrix[col-1][j];
		}
	}
	pthread_exit(NULL);
}
