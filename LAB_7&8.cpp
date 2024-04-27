// DOT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <mpi.h>
#include <iostream>
using namespace std;
int main()
{
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int a[100];
	int b[100];
	int localSum = 0;
	int* sums = new int[size];
	int* recivedA = new int[100 / size];
	int* recivedB = new int[100 / size];
	int result = 0;
	if (rank == 0) {
		for (int i = 0; i < 100; i++) {
			a[i] = 1;
			b[i] = 2;
		}
	}
	MPI_Scatter(&a, 100 / size, MPI_INT, recivedA, 100 / size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&b, 100 / size, MPI_INT, recivedB, 100 / size, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < 100 / size; i++) {
		localSum += recivedA[i] * recivedB[i];
	}

	// MPI_Gather(&localSum, 1, MPI_INT, sums, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Reduce(&localSum,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if (rank == 0) {
		/*for (int i = 0; i < size; i++)
		{
			result += sums[i]; // when you using Gather
		}*/

		for (int i = (100 / size) * size; i < 100; i++) {
			result += a[i] * b[i];
		}
		cout << "dot product of a and b is " << result << endl;
	}
	MPI_Finalize();
}
