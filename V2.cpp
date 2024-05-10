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
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    //On 3 processors "-n 3"
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[150];
    int N;

    if (rank == 0)
    {
        for (int i = 0; i < 150; i++)
            arr[i] = i;

        cout << "Enter any number to search" << endl;
        cin >> N;
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int recv[50];

    MPI_Scatter(arr, 50, MPI_INT, recv, 50, MPI_INT, 0, MPI_COMM_WORLD);


    int found = 0;
    int The_rank = 0;
    int x = 1;

    for (int i = 0; i < 50; i++)
    {
        if (N == recv[i])
        {
            if (rank == 0)
                x = 0;
            found = rank;
        }
    }

    MPI_Reduce(&found, &The_rank, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        if (The_rank != 0 || x == 0)
            cout << "Number found at rank " << The_rank << endl;
        else
            cout << "-1" << endl;
    }

    MPI_Finalize();
    return 0;
}
