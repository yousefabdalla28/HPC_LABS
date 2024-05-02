// count numbers divided by 7 in array contain 150 element
// from 1 to 150
// array declaration in the master rank
// at least 3 ranks parallel
// result printed via master rank
#include <stdio.h>
#include<iostream>
#include <mpi.h>
using namespace std;
int main() {
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int arr[150];
	if (rank == 0) {
		for (int i = 0; i < 150; i++) {
			arr[i] = i + 1;
		}
		cout << "data generated at rank 0" << endl;
	}
	int processors[3] = { 0,0,0 };
	int localCount = 0;
	int localArr[50];
	int totalCount = 0;
	MPI_Scatter(&arr,50,MPI_INT,&localArr,50,MPI_INT,0,MPI_COMM_WORLD);
	for (int i = 0; i < 50; i++) {
		if (localArr[i] % 7 == 0) {
			localCount++;
		}
	}
	MPI_Reduce(&localCount,&totalCount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) {
		cout << "The count of numbers divided by 7 is : " << totalCount;
	}
	MPI_Finalize();

	return 0;
}
