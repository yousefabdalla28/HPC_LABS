// parallel array search
//array containing numbers from 0 to 149
// print "rank id" if you find the target else print -1
// Test cases :
//    . Target = 3 print-->1
//    . Target = 145 print--> 7 "if you have 8 ranks"
//    . Target = 200 print--> -1
// All ranks must search for the target 
// At least 3 ranks

#include <stdio.h>
#include<iostream>
#include <mpi.h>
using namespace std;
int main() {
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int arr[150];
	int num;
	if (rank == 0) {
		for (int i = 0; i < 150; i++) {
			arr[i] = i ;
		}
		cout << "Enter any num between 0 and 149" << endl;
		cin >> num;
	}
	MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int localArr[50];

	int found = 0;
	int the_rank = 0;
	int x = 1;
	MPI_Scatter(&arr,50,MPI_INT,&localArr,50,MPI_INT,0,MPI_COMM_WORLD);
	for (int i = 0; i < 50; i++) {
		if (num = localArr[i]) {
			if (rank == 0) {
				x = 0;
			}
		found = rank;
		}
	}
	MPI_Reduce(&found,&the_rank,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) {
		if (the_rank != 0 || x == 0) {
			cout << "The rank is " << the_rank;
		}
		else {
			cout << "-1" << endl;
		}
	}
	MPI_Finalize();
	return 0;
}
