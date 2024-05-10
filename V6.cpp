/*
you should take N : the size of the array from user
you should initalize the array from 1 to N
Add specific value B to Matrix values
YOUR CODE SHOULD RUN AT ANY NUM OF PROCESSORS
*/

#include <iostream>
#include <mpi.h>

using namespace std;
int main()
{
	// intialize MPI
	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int B, N;
	if (rank == 0)
	{
		cout << "Enter the size of the array: ";
		cin >> N;
		cout << "Enter the value of b: ";
		cin >> B;
	}

	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&B, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int* A = new int[N];

	if (rank == 0)
	{
		for (int i = 0; i < N; i++)
		{
			A[i] = (i + 1);
		}
	}

	int length = N / size;

	int* local_A = new int[length];
	MPI_Scatter(A, length, MPI_INT, local_A, length, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < length; i++)
	{
		local_A[i] += B;
	}
	int* result = new int[N];

	MPI_Gather(local_A, length, MPI_INT, result, length, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{

		// handling the remainders
		int reminder = N - (N % size);

		for (int i = reminder; i < N; i++)
		{
			result[i] = A[i] + B;
		}
		cout << "The result is: ";

		for (int i = 0; i < N; i++)
		{
			cout << result[i] << " ";
		}

		cout << endl;
	}

	MPI_Finalize();
}
