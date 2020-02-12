#include <stdio.h> 
#include <mpi.h> 

int main(int argc, char *argv[]){

    // Initialize 
    int n = 5;
    int a[5]; 
    int i;
    int b = 0;
    int rank; 
    int size; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    for(i = 0; i < 5; i++) { a[i] = 0; }
    printf("Process of rank %d has value of %d\n", rank, b);  

    // Rank 2 modifies array values 
    if(rank == 2){
        for(i = 0; i < n; i++){ a[i] = i; }
    }

    // Rank 2 scatters new values to other ranks 
    MPI_Scatter(a, 1, MPI_INT, &b, 1, MPI_INT, 2, MPI_COMM_WORLD);
    printf("Process of rank %d has value of %d\n", rank, b);
    
    MPI_Finalize();

    return 0; 
}