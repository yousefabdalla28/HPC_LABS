/*
you should take N : the size of the array from user
you should initalize the array from 1 to N
Add specific value B to Matrix values
YOUR CODE SHOULD RUN AT ANY NUM OF PROCESSORS
*/
#include <stdio.h>
#include<iostream>
#include <mpi.h>
using namespace std;
int main() {
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int N, B;
	if (rank == 0) {
		cout << "Please enter the size of array N: " << endl;
		cin >> N;
		cout << "Please enter the values to be added B:" << endl;	
		cin >> B;
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&B, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int* arr = new int[N];
	int* localArr = new int[N / size];
	if (rank == 0) {
		for (int i = 0; i < N; i++) {
			arr[i] = i + 1;
		}
		cout << "data generated at rank 0" << endl;
	}
	MPI_Scatter(arr, N / size, MPI_INT, localArr, N / size, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < N / size; i++) {
		localArr[i] += B;
	}
	int* result = new int[N];
	MPI_Gather(localArr, N / size, MPI_INT, result, N / size, MPI_INT,0, MPI_COMM_WORLD);
	if (rank == 0) {
		cout << "the matrix result is " << endl;
		for (int i = 0; i < N; i++) {
			cout << result[i] << endl;
		}
	}
	MPI_Finalize();
	return 0;
}
