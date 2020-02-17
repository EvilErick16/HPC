#include <stdio.h> 
#include <mpi.h> 

int main(int argc, char *argv[]){

    // Initialize 
    int rank; 
    int size; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int n = 5;
    int a[5]; 
    int b = rank;
    for(int i = 0; i < 5; i++) { a[i] = 0; }
    printf("1. Process of rank %d has array a =  [%d, %d, %d, %d, %d] and b = %d\n", rank, a[0], a[1], a[2], a[3], a[4], b);

    // All ranks execute reduce operation, rank 2 is set as the root
    MPI_Reduce(&b, &a,1 , MPI_INT, MPI_SUM, 2, MPI_COMM_WORLD);  
    printf("2. Process of rank %d has array a =  [%d, %d, %d, %d, %d] and b = %d\n", rank, a[0], a[1], a[2], a[3], a[4], b);

    
    MPI_Finalize();

    return 0; 
}