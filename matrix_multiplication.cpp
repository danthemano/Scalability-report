#include <stdio.h> /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <iostream>
#include "omp.h"

using namespace std;

double** create_matrix(int rows, int cols)
{	
	double** mat = new double* [rows]; //Allocate rows.
	
	for (int i = 0; i < rows; ++i)
	{
		mat[i] = new double[cols](); //Allocate each row and zero initialize..
	}
	
	for(int j = 0; j < rows; j++)
	{
		for(int k = 0; k < cols; k++)
		{	
			mat[j][k] = rand() % 10 + 1; // generate random matrix values...	
		{
	}
	
	return mat;
}

void destroy_matrix(double** &mat, int rows)
{
	if(mat)
	{
		for (int i = 0; i < rows; ++i)	
		{
			delete[] mat[i]; //delete each row..	
		}
	
		delete[] mat; //delete the rows..
	
		mat = nullptr;	
	}
}

int main(int argc, char *argv[])

{
	int m = atoi(argv[1]);	
	int n = atoi(argv[2]);	
	int l = atoi(argv[3]);	
	
	int rows = m;	
	int cols = n;
		
	double** matA = create_matrix(rows, cols);
	double** matB = create_matrix(rows, cols);	
	double** matC = create_matrix(rows, cols);
	
	omp_set_num_threads(l);
	
	//Multiplication
	
	int i, j, k;
	
	#pragma omp parallel for private(i ,j ,k)
	
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{	
			for(int k = 0; k < cols; ++k) //ColsA..	
			{	
				matC[i][j] += matA[i][k] * matB[k][j];	
			}	
		}	
	}
	
	destroy_matrix(matA, rows);	
	destroy_matrix(matB, rows);	
	destroy_matrix(matC, rows);
	
	return 0;
}
