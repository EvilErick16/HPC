/* Erick Juarez
// CPSC 479 SEC 1 - HIGH PERFORMANCE COMPUTING 
// Juarez.erick16@csu.fullerton.edu
// Feb 10 2020
 
This program compares execution time of different communication types between parallel processors 
1. A single transmission using blocking communication
2. A round trip transmission using blocking communication 
3. Barrier is placed to synchornize processes 
4. A single transmission using non-blocking communication 
5. A round trip transmission using non-blocking communication
*/

// Include libraries 
#include <iostream>
#include "mpi.h"


int main(int argc, char* argv[]){

    // Initialize Communication 
    int rank, size;
    double start_time, end_time;  
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Request request; 
    MPI_Status status; 

    double msg; 

    // Blocking communication
    if(rank == 0){
        // Rank 0 sends a message 
        start_time = MPI_Wtime();   // Time before sending message
        msg = start_time; 
        MPI_Send(&msg, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD); 
       
        // Rank 0 waits until it receives a response 
        MPI_Recv(&msg, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        end_time = MPI_Wtime();     // Time when response is received 
        std::cout << "Blocking round trip transmission: " << end_time - msg << " sec\n"; 
    }
    else if (rank == 1){

        // Rank 1 expects a message 
        MPI_Recv(&msg, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        end_time = MPI_Wtime();     // Time when first message is received 
        std::cout << "Blocking single transmission: " << end_time - msg << " sec\n";
        
        // Rank 1 sends a response 
        MPI_Send(&msg, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); 
    }

    // Synchronization barrier 
    MPI_Barrier(MPI_COMM_WORLD); 

    // Non-Blocking communicaton
    if(rank == 0){
        // Rank 0 sends a non blocking message 
        start_time = MPI_Wtime();       // Time before sending message 
        msg = start_time; 
        MPI_Isend(&msg, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &request); 
        
        // Rank 0 expects a response
        MPI_Irecv(&msg, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &request); 
        MPI_Wait(&request, &status); 
        end_time = MPI_Wtime();     // Time when response is received 
        std::cout << "Non-Blocking round trip transmission: " << end_time - msg << "sec\n"; 
    }
    else if(rank == 1){
        // Rank 1 expects a message
        MPI_Irecv(&msg, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status); 
        end_time = MPI_Wtime();       // Time when first message is received 
        std::cout << "Non-Blocking single transmission: " << end_time - msg << " sec\n"; 

        // Rank 1 responds to the message and exits immediately 
        MPI_Isend(&msg, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request); 
    }

    MPI_Finalize();
    return 0;
}