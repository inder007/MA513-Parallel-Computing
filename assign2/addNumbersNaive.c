#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
	int my_id, size, n, no_per_process, sum=0;
	MPI_Status status;
	int arr[1000];
	int arr1[1000];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int root_process=0;
	if(my_id == root_process){
		printf("please enter the number of numbers to sum: ");
        scanf("%i", &n);
        for(int i=0;i<n;i++){
        	arr[i] = i+1;
        }
        no_per_process = n/size;
        for(int i=1;i<size;i++){
        	int start=i*no_per_process;
        	MPI_Send(&no_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        	MPI_Send(&arr[start], no_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for(int i=0;i<no_per_process;i++){
			sum+=arr[i];
		}

		for(int i=1;i<size;i++){
			int partial_sum=0;
			MPI_Recv(&partial_sum, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);

			//debug statements
			// sender = status.MPI_SOURCE;
            // printf("Partial sum %i returned from process %i\n", partial_sum, sender);

            sum+=partial_sum;
		}
		printf("final sum %d\n", sum);
	}
	else{
		int numbers_to_recieve=0;
		MPI_Recv(&numbers_to_recieve, 1, MPI_INT, root_process, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&arr1, numbers_to_recieve, MPI_INT, root_process, 0, MPI_COMM_WORLD, &status);
		int partial_sum=0;
		for(int i=0;i<numbers_to_recieve;i++){
			partial_sum += arr1[i];
		}
		MPI_Send(&partial_sum, 1, MPI_INT, root_process, 1, MPI_COMM_WORLD);
	}
	

	MPI_Finalize();
	return 0;
}