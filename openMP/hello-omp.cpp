// Include libraries 
#include <omp.h>
#include <stdio.h>
#include <mpi.h>


int main (int argc , char* argv[]) {
    // Initialize 
    int rank , nprocs , thread_id , nthreads;
    int name_len;
    MPI_Init (&argc , &argv);
    MPI_Comm_size (MPI_COMM_WORLD , &nprocs);
    MPI_Comm_rank (MPI_COMM_WORLD , &rank);

    #pragma omp parallel private(thread_id , nthreads) 
    {
    thread_id = omp_get_thread_num ();
    nthreads = omp_get_num_threads ();
    printf("Process: %d - Thread: %d\n", rank, thread_id); 
    }

    MPI_Finalize();
    return 0;
    
}
