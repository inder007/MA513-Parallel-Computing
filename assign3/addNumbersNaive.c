#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int my_id, size, n, no_per_process, sum=0;
	MPI_Status status;
	// printf("please enter the number of numbers to sum: ");
 //    scanf("%i", &n);
	n=atoi(argv[1]);
	// printf("%d\n", n);
	// int arr[1000];
	// int* arr = (int*)malloc(sizeof(int)*n);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    no_per_process = n/size;
	int* arr = (int*)malloc(sizeof(int)*n);

	int root_process=0;
	if(my_id == root_process){
        	// printf("test\n");
	    for(int i=0;i<n;i++){
	    	arr[i] = i+1;
	    }
        for(int i=1;i<size;i++){
        	int start=i*no_per_process;
        	MPI_Send(&arr[start], no_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        
	}
	else{
		MPI_Recv(arr, no_per_process, MPI_INT, root_process, 0, MPI_COMM_WORLD, &status);
	}

	double t1, t2, pt, time, pt2;
	MPI_Barrier(MPI_COMM_WORLD);
	
	t1 = MPI_Wtime();
	if(my_id == root_process){
		for(int i=0;i<no_per_process;i++){
			sum+=arr[i];
		}

		for(int i=1;i<size;i++){
			int partial_sum=0;
			MPI_Recv(&partial_sum, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            sum+=partial_sum;
		}
		// printf("Final Sum: %d\n", sum);
	}
	else{
		int partial_sum=0;
		for(int i=0;i<no_per_process;i++){
			partial_sum += arr[i];
		}
		MPI_Send(&partial_sum, 1, MPI_INT, root_process, 0, MPI_COMM_WORLD);
	}
	t2 = MPI_Wtime();
	MPI_Reduce(&t1, &pt, 1, MPI_DOUBLE, MPI_MIN, root_process, MPI_COMM_WORLD);
	MPI_Reduce(&t2, &pt2, 1, MPI_DOUBLE, MPI_MAX, root_process, MPI_COMM_WORLD);
	// pt = t2 - t1;
	if(my_id == root_process){
		// printf("Time elapsed is %lf \n", time);
		time = pt2 - pt;
		printf("%lf\n", time);
	}
	MPI_Finalize();
	return 0;
}