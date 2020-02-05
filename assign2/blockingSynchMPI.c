#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){

	int rank, data[100], size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank%2 == 0){
		MPI_Ssend(&data, 100, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);
		// printf("send complete of %d\n", rank);
	}
	else{
		MPI_Ssend(&data, 100, MPI_INT, (rank-1)%size, 1, MPI_COMM_WORLD);

	}
	// else if(rank==1){
	if(rank%2 == 0){
		MPI_Recv(data, 100, MPI_INT, (rank+1)%size, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	else{
		// printf("%d recieving\n", rank);
		MPI_Recv(data, 100, MPI_INT, (rank-1)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	}
	// }
	printf("I am %d \n", rank+1);
	MPI_Finalize();
	return 0;

}