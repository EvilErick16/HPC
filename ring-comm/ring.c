// Ring topology example


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

int token;
if (rank != 0) {
    MPI_Recv(&token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", rank, token, (rank - 1) % size);
}
else {
    // Set the token's value if you are process 0
    token = -1;
}

MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

// Now process 0 can receive from the last process.
if (rank == 0) {
    MPI_Recv(&token, 1, MPI_INT, (size - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", rank, token, (size - 1) % size);
}


MPI_Finalize();
return 0;
}