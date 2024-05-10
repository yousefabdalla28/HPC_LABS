// count numbers divided by 7 in array contain 150 element
// from 1 to 150
// array declaration in the master rank
// at least 3 ranks parallel
// result printed via master rank

#include <iostream>
#include <mpi.h>
using namespace std;


int main()
{
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[150];

    if (rank == 0)
    {

        for (int i = 0; i < 150; i++)
        {
            a[i] = i + 1;
        }
    }

    int length = 150 / size;
    int* localarr = new int[length];

    MPI_Scatter(&a, length, MPI_INT, localarr, length, MPI_INT, 0, MPI_COMM_WORLD);

    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (localarr[i] % 7 == 0)
        {
            count++;
        }
    }

    int result;
    MPI_Reduce(&count, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {

        // handle the remaining elements
        int reminder = 150 - (150 % size);
        for (int i = reminder; i < 150; i++)
        {
            if (a[i] % 7 == 0)
            {
                result++;
            }
        }
        cout << "Total numbers divisible by 7: " << result << endl;
    }

    MPI_Finalize();
}
