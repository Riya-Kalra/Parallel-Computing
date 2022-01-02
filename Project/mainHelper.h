#include <iostream>
#include <cmath>
#include <sys/time.h>
#include <fstream>
#include<string>
using namespace std;

void saveMatrix(double **matrix, string fileName, int size);
void printMatrix(double **mat, int size);
void generateRandomMatrix();
std::string findLUDecompositionUsingSerial(int size, double **input);
std::string luDecompositionUsingPthread(int size, double **input);
void *getLowerUpperMatrixUsingPthread(void *tmp);
void *swappingUsingPthread(void *tmp);
void *calculate_lower_upper_matrixUsingPthread(void *tmp);
std::string findLUDecompositionUsingOpenMP(int size, double **input);
void getLowerUpperMatrixUsingOpenMP(int col);
void swappingUsingOpenMP(int col, int swapRowNum);
