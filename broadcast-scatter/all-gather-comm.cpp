#include <stdio.h> 
#include <mpi.h> 

int main(int argc, char *argv[]){

    // Initialize 
    int rank; 
    int size; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int n = 10;
    int a[10]; 
    int b[2] = {rank, rank};
    for(int i = 0; i < n; i++) { a[i] = 0; }
    printf("1. Process of rank %d has array a =  [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d] and array b = %d, %d\n",
     rank, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], b[0], b[1]);

    // All ranks gather values from other processes
    MPI_Allgather(&b, 1, MPI_INT, a, 1, MPI_INT, MPI_COMM_WORLD);  
    printf("2. Process of rank %d has array a =  [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d] and array b = %d, %d\n", 
    rank, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], b[0], b[1]);

    
    MPI_Finalize();

    return 0; 
}