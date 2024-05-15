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
	if (rank == 0) {
		for (int i = 0; i < 200; i++) {
			arr[i] = i + 1;
		}
	}
	int length = 200 / size;
	int* localarr = new int[length];
	MPI_Scatter(arr, length, MPI_INT, localarr, length, MPI_INT, 0, MPI_COMM_WORLD);
	int max = 0;
	for (int i = 0; i < length; i++) {
		if (localarr[i] > max) {
			max = localarr[i];
		}
	}
	int* maxs = new int[size];
	int result = 0;
	MPI_Gather(&max, 1, MPI_INT, maxs,1, MPI_INT, 0, MPI_COMM_WORLD);
	// OR Reduce no need for gather or maxs or loop in rank 0
	if (rank == 0) {
		for (int i = 0; i < size; i++) {
			if (maxs[i] > result) {
				result = maxs[i];
			}
		}
		int r = 200 - (200 % size);
		for (int i = r; i < 200; i++) {
			if (arr[i] > result) {
				result = arr[i];
			}
		}
		cout << result << endl;
	}
	MPI_Finalize();
	return 0;
}
