/*
*
MPI Array Calculation This program performs a calculation on a given 4x4 array. The array is initially defined as follows:

[
  1 ,1, 1, 1
  2, 2, 2, 2
  3, 3, 3, 3
  4, 4, 4, 4
]
The calculation is performed on each row of the array, using a value provided by the user. The specific operation to be applied on each row is as follows:

Addition (+) on the first row
Multiplication (*) on the second row
Subtraction (-) on the third row
Division (/) on the fourth row
For example, let's assume the user enters the value 3. The result of the calculation will be a modified array:

[ 4, 4, 4, 4,
  6, 6, 6, 6,
  0, 0, 0, 0,
  1.3, 1.3, 1.3, 1.3]

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
	float arr[16] = { 1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4 };
	float localArr[4];
	float num = 0;
	if (rank == 0) {
		cout << "Enter the number" << endl;
		cin >> num;
	}
	MPI_Bcast(&num, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatter(arr, 4, MPI_FLOAT, localArr, 4, MPI_FLOAT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < 4; i++) {
		if (rank == 0) {
			localArr[i] += num;
		}
		else if (rank == 1) {
			localArr[i] *= num;
		}
		else if (rank == 2) {
			localArr[i] -= num;
		}
		else if (rank == 3) {
			localArr[i] /= num;
		}
	}
	float result[16];
	MPI_Gather(localArr,4,MPI_FLOAT,result,4,MPI_FLOAT,0,MPI_COMM_WORLD);
	if (rank == 0) {
		cout << "The Matrix Result is " << endl;
		for (int i = 0; i < 16; i++) {
			cout << result[i] << endl;
		}
	}
	MPI_Finalize();

	return 0;
}
