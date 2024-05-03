/*
adding two arrays each of them with 16 element
*/
#include <iostream>
#include <mpi.h>
#include <cmath>
using namespace std;

int main()
{
    MPI_Init(NULL, NULL);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int arr1[16];
    int arr2[16];
    int localArr1[4];
    int localArr2[4];
    int localSum[4];
    int result[16];
    if (rank == 0) {
        for (int i = 0; i < 16; i++)
        {
            arr1[i] = i + 1;
            arr2[i] = i + 1;
        }
    }
    MPI_Scatter(arr1, 4, MPI_INT, localArr1, 4, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr2, 4, MPI_INT, localArr2, 4, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 4; i++) {
        localSum[i] = localArr1[i] + localArr2[i];
    }
    MPI_Gather(localSum,4,MPI_INT,result,4,MPI_INT,0,MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < 16; i++) {
            cout << result[i]<<" ";
        }
    }
    MPI_Finalize();
    return 0;
}
