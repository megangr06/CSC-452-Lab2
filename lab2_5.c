#include <stdio.h>
#include <time.h>
#include "mpi.h"
int main(int argc, char *argv[]) {
	int rank, size, type=99;
	char m1[22], m2[23];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	double start = MPI_Wtime();
	sprintf(m2,"Hello, mcg033 from #%2d!\n", rank);
	if (rank==0){
		MPI_Send(m2,23,MPI_CHAR,1,type,MPI_COMM_WORLD);
		MPI_Recv(m1,23,MPI_CHAR,size-1,type,MPI_COMM_WORLD,&status);
		printf("Message at proc #%2d: %.22s\n",rank,m1);
	}
	else{
		MPI_Send(m1,23,MPI_CHAR,rank-1,type,MPI_COMM_WORLD);
		printf("Message at proc #%2d: %.22s\n",rank,m1);
		MPI_Recv(m2,23,MPI_CHAR,(rank+1)%size,type,MPI_COMM_WORLD, &status);
		
	}
	
	double end = MPI_Wtime();
	if (rank == 0){
		printf("Time elapsed is %f seconds. \n", end-start);
	}
	MPI_Finalize();
	return 0;
}