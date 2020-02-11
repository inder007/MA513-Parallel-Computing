#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
    int my_id, size;

    int n = atoi(argv[1]);

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int p_per_row = sqrt(size);
	int row_per_process = n/p_per_row;

	int row_color = my_id/p_per_row;
	int col_color = my_id%p_per_row;

	MPI_Comm row_comm, col_comm;
	MPI_Comm_split(MPI_COMM_WORLD, row_color, my_id, &row_comm); 
	MPI_Comm_split(MPI_COMM_WORLD, col_color, my_id, &col_comm); 

	int my_row_id, my_col_id;
	MPI_Comm_rank(row_comm, &my_row_id);
	MPI_Comm_rank(col_comm, &my_col_id); 

	int no_per_process = (n*n)/size;
	int* a = (int*)malloc(sizeof(int)*n*n);
	int* x = (int*)malloc(sizeof(int)*n);
	int* b = (int*)malloc(sizeof(int)*n);

	int root_process = 0;
	if(my_id == root_process){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				// a[i*n+j] = i*n+j;
				if(i==j){
					a[i+n*j] = 1;
				}
				else{
					a[i+n*j] = 0;
				}
			}
			// x[i] = 1;
			// b[i] = 0;
		}
	}
	if(my_id == p_per_row - 1){
		for(int i=0;i<n;i++){
			x[i] = 1;
		}
	}

	if(my_id%p_per_row == 0){
		MPI_Scatter(a, no_per_process*p_per_row, MPI_INT, a, no_per_process*p_per_row, MPI_INT, root_process, col_comm);
	}

	for(int i=0;i<row_per_process;i++){
		MPI_Scatter(&a[i*n], row_per_process, MPI_INT, &a[i*row_per_process], row_per_process, MPI_INT, 0, row_comm);
	}

	// printf("PID  %d\n", my_id);
	// for(int i=0;i<row_per_process;i++){
	// 	for(int j=0;j<row_per_process;j++){
	// 		printf("%d-%d ",my_id, a[row_per_process*i+j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");

	if(my_row_id == p_per_row-1){
		// for(int i=0;i<row_per_process;i++){
		// 	printf("%d-%d ", my_id, x[i]);
		// }
		// printf("\n");
		MPI_Scatter(x, row_per_process, MPI_INT, x, row_per_process, MPI_INT, 0, col_comm);
	}

	double t1, t2, pt, time, pt2;
	t1 = MPI_Wtime();

	for(int k=0;k<5;k++){
		if(my_row_id == p_per_row-1 && my_id != size-1){
			MPI_Send(x, row_per_process, MPI_INT, my_col_id, 0, row_comm);
		}
		if(my_row_id == my_col_id){
			if(my_id != size-1)MPI_Recv(x, row_per_process, MPI_INT, MPI_ANY_SOURCE, 0, row_comm, MPI_STATUS_IGNORE);
		}
		MPI_Bcast(x, row_per_process, MPI_INT, my_row_id, col_comm);
		// for(int i=0;i<row_per_process;i++){
		// 	printf("%d-%d ", my_id, x[i]);
		// }
		// printf("\n");
		// printf("%d reached\n", my_id);
		

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0;i<row_per_process;i++){
			b[i] = 0;
			for(int j=0;j<row_per_process;j++){
				b[i] += a[i*row_per_process + j]*x[j];
			}
		}

		
		MPI_Reduce(b, x, row_per_process, MPI_INT, MPI_SUM, p_per_row-1, row_comm);


	}

	if(my_row_id == p_per_row-1){
		MPI_Gather(x, row_per_process, MPI_INT, x, row_per_process, MPI_INT, root_process, col_comm);
	}

	t2 = MPI_Wtime();
	MPI_Reduce(&t1, &pt, 1, MPI_DOUBLE, MPI_MIN, root_process, MPI_COMM_WORLD);
	MPI_Reduce(&t2, &pt2, 1, MPI_DOUBLE, MPI_MAX, root_process, MPI_COMM_WORLD);

	// if(my_id == p_per_row-1){
	// 	for(int i=0;i<n;i++){
	// 		printf("%d ", x[i]);
	// 	}
	// 	printf("\n");
	// }
	if(my_id == root_process){
		time = pt2 - pt;
		printf("%lf\n", time);
	}


	MPI_Finalize();
    
	return 0;
}