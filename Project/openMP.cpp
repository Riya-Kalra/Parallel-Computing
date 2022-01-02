#include <omp.h>
#include"mainHelper.h"

double **mat;
double **loMat;
double **upMat;
double **permMat;
int matSize = 0;		//size of matrix.

string findLUDecompositionUsingOpenMP(int size, double **input) {
	int maxThreads = 5, currentThread;
	struct timeval tstart, tend;
	double exectime;
	string stats;
	matSize = size;
	ifstream file;
	mat = new double*[matSize];
	loMat = new double*[matSize];
	upMat = new double*[matSize];
	permMat = new double*[matSize];
	for (int i = 0; i < matSize; ++i){
		mat[i] = new double[matSize];
		loMat[i] = new double[matSize];
		upMat[i] = new double[matSize];
		permMat[i] = new double[matSize];
	}
	for (int noOfThreads = 1; noOfThreads <= maxThreads; noOfThreads++){
		for (int i = 0; i < matSize; ++i){
			for(int j = 0; j < matSize; j++){
				if(i == j){
					loMat[i][j] = 1;
					permMat[i][j] = 1;
				}else{
					loMat[i][j] = 0;
					permMat[i][j] = 0;
				}
				upMat[i][j] = 0;
				mat[i][j] = input[i][j];
			}
		}
		gettimeofday( &tstart, NULL );
		currentThread = noOfThreads;
		stats += to_string(matSize)+", "+to_string(noOfThreads);
    		for(int k = 0; k < matSize; k++) {
       		double maxEle = 0;
        		int swapRow = k;
        		for(int i = k; i < matSize; i++) {
            			if(maxEle < abs(mat[i][k])) {
                			maxEle = abs(mat[i][k]);
                			swapRow = i;
            			}
        		}	
        		if(maxEle == 0) {
            			cout << "Given matrix is singular. LU decomposition can't be calculated.\n";
            			break;
        		}
        		int remainingRows = matSize - (k + 1);
			while (remainingRows < currentThread)
				currentThread = currentThread / 2;
			omp_set_num_threads(currentThread);
	
        		//swap(mat[k], mat[swapRow]);
			//swap(permMat[k], permMat[swapRow]);
			for(int i = 0; i < matSize; i++){
				int temp = mat[k][i];
				mat[k][i] = mat[swapRow][i];
				mat[swapRow][i] = temp;
				temp = permMat[k][i];
				permMat[k][i] = permMat[swapRow][i];
				permMat[swapRow][i]  = temp;
          }
			if(currentThread > 0){
        		swappingUsingOpenMP(k, swapRow);
        		}
        		upMat[k][k] = mat[k][k];
        		if(currentThread > 0){
        		getLowerUpperMatrixUsingOpenMP(k+1);
        		}
        	}
        	gettimeofday( &tend, NULL );
		exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
  		exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms
  		stats += ", " + to_string(exectime/1000.0) + "\n";
    	}
    	saveMatrix(loMat, "lowerMatrix", size);
	saveMatrix(upMat, "upperMatrix", size);
	saveMatrix(permMat, "permutationMatrix", size);
    	return stats;
}
void getLowerUpperMatrixUsingOpenMP(int col){
	int i,j, rows, start, end, threadId, rowsPerThread, numThreads;
	rows = matSize - col;
	
	#pragma omp parallel shared(mat, loMat, upMat, matSize, col, rows) private(start,end, threadId, rowsPerThread)
	{
		#ifdef _OPENMP
			numThreads = omp_get_num_threads();
		#endif
		#ifdef _OPENMP
			threadId = omp_get_thread_num();
		#endif
		rowsPerThread = rows/numThreads;
		if(rowsPerThread == 0){
			rowsPerThread = rows;
		}
		start = col + rowsPerThread * threadId;
		end = start + rowsPerThread - 1;
		if(threadId == numThreads - 1 || end >= matSize){
			end = matSize - 1;
		}
	
		for (int i = start; i <= end;++i){	
            		loMat[i][col-1] = mat[i][col-1] / upMat[col-1][col-1];
            		upMat[col-1][i] = mat[col-1][i];
        	}
        	#pragma omp barrier
        	for (int i = start; i <= end;++i){
			for (int j = col; j < matSize; ++j){
				mat[i][j] -= loMat[i][col-1]*upMat[col-1][j];
			}
		}
        }
}
void swappingUsingOpenMP(int col, int swapRow){
	int i,j, start, end, threadId, rowsPerThread, numThreads, elements, elementsPerThread;
	elements = col;
	#pragma omp parallel shared(mat, loMat, upMat, matSize, elements, col, elementsPerThread, swapRow) private(start,end, threadId)
	{
		#ifdef _OPENMP
			numThreads = omp_get_num_threads();
		#endif
		#ifdef _OPENMP
			threadId = omp_get_thread_num();
		#endif
		elementsPerThread = elements / numThreads;
		if (elementsPerThread == 0)
			elementsPerThread = elements;
		int start = elementsPerThread*threadId, end = start + elementsPerThread - 1;
		//Condition for last thread allocation
		if (threadId == numThreads-1 or end >= elements)
			end = elements-1;
		
		for(int i = start; i <= end; i++) {			
            		swap(loMat[col][i], loMat[swapRow][i]);
        	}
        	
        }
}

