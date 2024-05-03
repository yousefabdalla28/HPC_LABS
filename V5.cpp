/*
 x,y are arrays from 1 to 50
 sum i=1 to n (x^2*y)
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
    int N, localSum = 0, result;
    int x[50];
    int y[50];
    if (rank == 0) {
        for (int i = 0; i < 50; i++) { 
            x[i] = i + 1;
            y[i] = i + 1;
        }
        cout << "Enter value for N" << endl;
        cin >> N;
    }
    MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
    int length = N / 5;
    for (int i = (rank * length) + 1; i <= (rank + 1) * length; i++) {
        localSum += (x[i] * x[i]) * y[i];
    }
    MPI_Reduce(&localSum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = (size * length) + 1; i <= N; i++) {
            result += (x[i] * x[i]) * y[i];
        }
        cout << "Result is = " << result << endl;
    }
    MPI_Finalize();
    return 0;
}
