/* Erick Juarez
// CPSC 479 SEC 1 - HIGH PERFORMANCE COMPUTING 
// Juarez.erick16@csu.fullerton.edu
// Feb 10 2020
 
This program  establishes a ring topology of communicating processes and calculates the time it takes 
a message to travel through the entire ring
*/

// Include Libraries 
#include <iostream>
#include "mpi.h"

int main(int argc, char* argv[]){

    // Initialize communication 
    int rank, size;
    double start_time, end_time; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int token; 

    if (rank != 0) {
        // Ranks that are not 0 will first wait for a message to be availabe  
        MPI_Recv(&token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else {
        // Rank 0 sets the token value and starts the timer
        token = -1;
        start_time = MPI_Wtime();
    }

    // Rank 0 sends the first messge, then other processes send one as soon as they receive it
    MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Rank 0 expects message from the last process then stops the timer when the message is received
        MPI_Recv(&token, 1, MPI_INT, (size - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        end_time = MPI_Wtime();
        std::cout << "Message traveled through " << size << " nodes in :" << end_time - start_time << "sec\n";
    }

    // Finalize communication
    MPI_Finalize();
    return 0;
}