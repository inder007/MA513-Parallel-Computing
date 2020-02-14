#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv){
    int my_id, size;

    int n = atoi(argv[1]);

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int no_per_process = (n*n)/size;
	int no_of_rows = n/size;
	int* a = (int*)malloc(sizeof(int)*n*n);
	int* x = (int*)malloc(sizeof(int)*n);
	int* b = (int*)malloc(sizeof(int)*n);

	int root_process = 0;
	if(my_id == root_process){
		// int* a = (int*)malloc(sizeof(int)*n*n);
		// int* x = (int*)malloc(sizeof(int)*n);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				// a[i*n+j] = 1;
				if(i==j){
					a[i+n*j] = 1;
				}
				else{
					a[i+n*j] = 0;
				}
			}
			x[i] = 1;
			b[i] = 0;
		}
	}

	MPI_Scatter(a, no_per_process, MPI_INT, a, no_per_process, MPI_INT, root_process, MPI_COMM_WORLD);
	MPI_Scatter(x, no_of_rows, MPI_INT, x, no_of_rows, MPI_INT, root_process, MPI_COMM_WORLD);

	// MPI_Barrier(MPI_COMM_WORLD);
	double t1, t2, pt, time, pt2;

	t1 = MPI_Wtime();

	for(int k=0;k<50;k++){
		for(int i=0;i<n;i++){
			b[i] = 0;
			for(int j=0;j<no_of_rows;j++){
				b[i] += a[i+n*j]*x[j];
			}
		}
		MPI_Reduce(b, x, n, MPI_INT, MPI_SUM, root_process, MPI_COMM_WORLD);
		MPI_Scatter(x, no_of_rows, MPI_INT, x, no_of_rows, MPI_INT, root_process, MPI_COMM_WORLD);
	}

	// MPI_Gather(x, no_of_rows, MPI_INT, x, no_of_rows, MPI_INT, root_process, MPI_COMM_WORLD);


	// if(my_id == root_process){
	// 	for(int i=0;i<n;i++){
	// 		printf("%d ", x[i]);;
	// 	}
	// 	printf("\n");
	// }


	t2 = MPI_Wtime();
	MPI_Reduce(&t1, &pt, 1, MPI_DOUBLE, MPI_MIN, root_process, MPI_COMM_WORLD);
	MPI_Reduce(&t2, &pt2, 1, MPI_DOUBLE, MPI_MAX, root_process, MPI_COMM_WORLD);

	if(my_id == root_process){
		time = pt2 - pt;
		printf("%lf\n", time);
	}


	MPI_Finalize();
    
	return 0;
}