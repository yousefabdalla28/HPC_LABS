// sum i=1 to 100 --> (3 - 2*i)^2 
#include <stdio.h>
#include<iostream>
#include <mpi.h>
using namespace std;

int main() {
	MPI_Init(NULL, NULL);


	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int  N, localSum=0, result;
	if (rank == 0) {
		cout << " Enter value for N " << endl;
		cin >> N;
	}
	MPI_Bcast(&N, 1,MPI_INT, 0, MPI_COMM_WORLD);
	int length = N / size;
	for (int i = (rank * length) + 1; i <= (rank + 1) * length; i++) {
		localSum += (3 - (2 * i)) * (3 - (2 * i));
	}
	cout << "local" << localSum << endl;
	MPI_Reduce(&localSum, &result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) {
		for (int i = (size * length) + 1; i <= N; i++) {
			result += (3 - 2 * i) * (3 - 2 * i);
		}
		cout << "Result is = " << result<<endl;
	}

	MPI_Finalize();
	return 0;
}
