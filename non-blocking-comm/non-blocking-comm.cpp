#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
#include <math.h> 

int main (int argc, char* argv[]) {

    // Declare variables
    int rank; 
    int numprocs; 
    int tag; 
    int source; 
    int destination; 
    int count; 
    int buffer; 
    MPI_Status status; 
    MPI_Request request; 

    // Initialize MPI interface 
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
    tag = 2312;         // Default tag for the message 
    source = 0;         // Processor with rank 0 is the source of the message  
    destination = 1;    // Processor with rank 1 is the destination for the message
    count = 1;          // Count of items in the message 
    request = MPI_REQUEST_NULL; // request object returns a *flag=1 when the operation *req has completed, and 0 otherwise 

    // Send message if you are the source rank 
    if(rank == source){
        buffer = 2015; 
        MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request); 
    }
    // Receive message if you are the destination rank 
    if(rank == destination){
        MPI_Irecv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &request); 
    }
 
    // Wait for request to be processed 
    MPI_Wait(&request, &status); 

    // Print messages 
    if(rank == source){
        printf("Processor %d sent %d\n", rank, buffer); 
    }
    else if(rank == destination){
        printf("Process %d received %d\n", rank, buffer); 
    }
    else
        printf("Process %d didn't send or receive anything\n", rank);

    MPI_Finalize(); 
}