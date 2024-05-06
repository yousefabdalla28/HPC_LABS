/*
 x,y are arrays from 1 to 50
 sum i=1 to n (x^2*y)
 run your code with only 5 processors
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
    int  localSum = 0, result;
    int x[50];
    int y[50];
    int localX[10];
    int localY[10];
    if (rank == 0) {
        for (int i = 0; i < 50; i++) { 
            x[i] = i + 1;
            y[i] = i + 1;
        }  
    }
    MPI_Scatter(&x,50/size,MPI_INT,localX, 50 / size,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(&y, 50 / size, MPI_INT, localY, 50 / size, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 50 / size; i++) {
        localSum += (localX[i] * localX[i]) * localY[i];
    }
    MPI_Reduce(&localSum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = (50 / size) * size; i < 50; i++) {
            result += (x[i]*y[i])*y[i];
        }
        cout << "Result is = " << result << endl;
    }
    MPI_Finalize();
    return 0;
}
