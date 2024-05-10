// parallel array search
//array containing numbers from 0 to 149
// print "rank id" if you find the target else print -1
// Test cases :
//    . Target = 3 print-->1
//    . Target = 145 print--> 7 "if you have 8 ranks"
//    . Target = 200 print--> -1
// All ranks must search for the target 
// At least 3 ranks
#include <iostream>
#include <mpi.h>
using namespace std;
int main()
{
	MPI_Init(NULL, NULL);

	int rank,size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int arr[150];
	int target;

	if (rank == 0)
	{
		// initialize array with numbers from 0 to 149
		for (int i = 0; i < 150; i++)
		{
			arr[i] = i;
		}
		cout << "Enter the target number: ";
		cin >> target;
	}

	MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int length = 150 / size;
	int* localarr = new int[length];

	MPI_Scatter(&arr, length, MPI_INT, localarr, length, MPI_INT, 0, MPI_COMM_WORLD);

	int found = -1;
	for (int i = 0; i < length; i++)
	{
		if (localarr[i] == target)
		{
			found = rank;
			break;
		}
	}
	int r;
	MPI_Reduce(&found, &r, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		// handling the remainder of the array
		int reminder = 150 - (150 % size);
		for (int i = reminder; i < 150; i++)
		{
			if (arr[i] == target)
			{
				r = rank;
				break;
			}
		}
		if (r >= 0) {
			cout << "Number found at rank " << r << endl;
		}
		else
		{
			cout << "-1" << endl;
		}
	}
	MPI_Finalize();
}
