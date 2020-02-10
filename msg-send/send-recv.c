//Send and Receive
// Include Libs 
#include <stdio.h>
#include <mpi.h>

// Main function definition 
int main( int argc, char *argv[] )
{

// Initialize env
int rank, size;
MPI_Init( &argc, &argv );
MPI_Comm_rank( MPI_COMM_WORLD, &rank );
MPI_Comm_size( MPI_COMM_WORLD, &size );

printf( "Process # %d of %d\n", rank, size - 1);

//int number = 0;
int array[3]; 
array[0] = 0, array[1] = 0, array[2] = 0; 

printf( "Process %d starts with array: [%d, %d, %d]\n", rank, array[0], array[1], array[2]);



if (rank == 0) {
    //number = -1;
    //MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

    array[0] = -10, array[1] = -10, array[2] = -10; 
    MPI_Send(array, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
    printf("Process 0 sent  array: [%d, %d, %d]\n", array[0], array[1], array[2]);
} 
else if (rank == 1) {
    //MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(array, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 1 received array: [%d, %d, %d]\n", array[0], array[1], array[2]);
}

printf( "Process %d ends with array: [%d, %d, %d]\n", rank, array[0], array[1], array[2]);


MPI_Finalize();
return 0;
}