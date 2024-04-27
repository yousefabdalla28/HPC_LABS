#include <mpi.h>
#include<stdio.h>
#include <iostream>
// mpiexec -n 3 "MPI6.exe"
using namespace std;
int main()
{
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int localsum=0,sum=0;
	int data[15];
	int localData[5];
	int sums[3] = {0,0,0};
	if (rank == 0) {
		for (int i = 0; i < 15; i++) {
			data[i] = i+1;
		}
		cout << "Data generated" << endl;
	}
	MPI_Scatter(&data, 5, MPI_INT, &localData, 5, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < 5; i++) {
		localsum += localData[i];
	}
	cout << "localsum at rank "<<rank<<" is = "<<localsum << endl;
	MPI_Gather(&localsum,1,MPI_INT,&sums,1,MPI_INT,0,MPI_COMM_WORLD);
	if (rank == 0) {
		for (int i = 0; i < 3; i++) {
			sum += sums[i];
		}
		cout << "Total sum is =" << sum << endl;
	}

	MPI_Finalize();
	return 0;
}
