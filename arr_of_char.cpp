#include <mpi.h>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int array_size = 8;
    char arr[array_size + 1]; // +1 for null terminator
    char target_char;
    int found = 0;
    int global_found;

    if (rank == 0) {
        cout << "Enter a string of 8 chars: ";
        cin >> arr;
        cout << "Enter a target character: ";
        cin >> target_char;
    }

    // Broadcast the array to all processes
    MPI_Bcast(arr, array_size + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Broadcast the target character to all processes
    MPI_Bcast(&target_char, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Each process checks if the target character exists in the array
    for (int i = 0; i < array_size; i++) {
        if (arr[i] == target_char) {
            found = 1;
            break;
        }
    }

    // Reduce the results to determine if the target character was found
    MPI_Reduce(&found, &global_found, 1, MPI_INT, MPI_LOR, 0, MPI_COMM_WORLD);

    // Rank 0 prints the result
    if (rank == 0) {
        if (global_found) {
            cout << "The target character '" << target_char << "' was found in the array." << endl;
        }
        else {
            cout << "The target character '" << target_char << "' was not found in the array." << endl;
        }
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
