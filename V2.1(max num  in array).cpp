// Parallel code to calculate the max num in an arr 1-->200
//without using Reductioin function

#include <stdio.h>
#include<iostream>
#include <mpi.h>
using namespace std;
int main() {
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int arr[200];
	int num;
	if (rank == 0) {
		for (int i = 0; i < 200; i++) {
			arr[i] = i+1;
		}
		cout << "Data generated at rank 0" << endl;
	}
	int localArr[50];
	int processors[4];
	MPI_Scatter(&arr, 50, MPI_INT, &localArr, 50, MPI_INT, 0, MPI_COMM_WORLD);
	int max = 0;
	for (int i = 0; i < 50; i++) {
		if (localArr[i] >max) {
			max = localArr[i];
		}
	}
	MPI_Gather(&max,1,MPI_INT,processors,1,MPI_INT,0,MPI_COMM_WORLD);
	int finalMax = 0;
	if (rank == 0) {
		for (int i = 0; i < 4; i++) {
			finalMax = processors[i];
		}
		cout << "Max number in the array is :" << finalMax << endl;
	}
	MPI_Finalize();
	return 0;
}
