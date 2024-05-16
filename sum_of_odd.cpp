// using parallel code
// given array of 15 element 
// from 1 to 16
// get the sum of odd numbers 
// with dynamic number of cpus
#include <stdio.h>
#include<iostream>
#include <mpi.h>
using namespace std;
int main() {
	MPI_Init(NULL, NULL);
	const int array_size = 15;
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int  arr[15];
	if (rank == 0) {
		for (int i = 0; i < 15; i++) {
			arr[i] = i + 1;
		}
	}
	int length = array_size / size;
	int* local_arr = new int[length];
	MPI_Scatter(arr, length, MPI_INT, local_arr, length, MPI_INT, 0, MPI_COMM_WORLD);
	int sum = 0;
	for (int i = 0; i < length; i++) {
		if (local_arr[i] % 2 == 1) {
			sum += local_arr[i];
		}
	}
	int result;
	MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		
		int reminder = array_size - (array_size % size);
		for (int i = reminder; i < array_size; i++) {
			if (arr[i] % 2 == 1) {
				result += arr[i];
			}
		}
		cout << "Result is = " << result << endl;
	}

	MPI_Finalize();
	return 0;
}
