/*
parallel program iterate on array containing 1000 element and
 1) adds to each even number the value 2 
 2) sub from each odd number the value 1
 3) sum all new numbers

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
	int arr[1000];
	int localArr[250];
	int localSum = 0;
	int sum = 0;
	if (rank == 0) {
		for (int i = 0; i < 1000; i++) {
			arr[i] = i + 1;
		}
		cout << "Data generated at rank 0" << endl;
	}
	MPI_Scatter(&arr,250,MPI_INT,localArr,250,MPI_INT,0,MPI_COMM_WORLD);
	for (int i = 0; i < 250; i++) {
		if (localArr[i] % 2 == 0)
			localSum += localArr[i] + 2;
		else 
			localSum += localArr[i] - 1;
	}
	MPI_Reduce(&localSum,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) {
		cout << "sum is " << sum << endl;
	}
	MPI_Finalize();
	return 0;
}
