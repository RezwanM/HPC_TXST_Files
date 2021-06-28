#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[]) {

	int size, rank, namelen;
  	char processor_name[MPI_MAX_PROCESSOR_NAME];
  	int tid = 0, nt = 1;

  	MPI_Init(&argc, &argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &size);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  	MPI_Get_processor_name(processor_name, &namelen);

  	omp_set_num_threads(28);

	#pragma omp parallel private(tid, nt)
  	{
    		nt = omp_get_num_threads();
    		tid = omp_get_thread_num();
    		printf("Hello from thread %d out of %d from process %d out of %d on %s\n", tid, nt, rank, size, processor_name);
  	}

  	MPI_Finalize();
}
