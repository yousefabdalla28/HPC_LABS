
#include <mpi.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
	MPI_Init(NULL, NULL);
	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int sum0 = 0;
	int sum1 = 0;
	int sum2 = 0;
	int totalSum = 0;
	if (rank == 0) {
		MPI_Status stat;
		int data[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
		for (int i = 0; i < 5; i++) {
			sum0 += data[i];
		}
		cout << "sum of rank 0 is " << sum0 << endl;
		MPI_Send(&data[5], 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&data[10], 5, MPI_INT, 2, 0, MPI_COMM_WORLD);
		MPI_Recv(&sum1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,&stat);
		MPI_Recv(&sum2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &stat);
		totalSum = sum0 + sum1 + sum2;
		cout << "Total sum is  " << totalSum << endl;

	}
	if (rank == 1) {
		int data[5];
		MPI_Status stat;
		MPI_Recv(&data, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
		for (int i = 0; i < 5; i++) {
			sum1 += data[i];
		}
		cout << "sum of rank 1 is " << sum1 << endl;
		MPI_Send(&sum1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	if (rank == 2) {
		int data[5];
		MPI_Status stat;
		MPI_Recv(&data, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
		for (int i = 0; i < 5; i++) {
			sum2 += data[i];
		}
		cout << "sum of rank 2 is " << sum2 << endl;
		MPI_Send(&sum2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
