//Erick Juarez
#include <iostream>
#include "mpi.h"


int main(int argc, char* argv[]){

    int rank, size;
    double start_time, end_time;  
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    double msg; 

    if(rank == 0){
        // When rank is 0 first we send a message, then we expect a response 
        start_time = MPI_Wtime(); 
        msg = start_time; 
        MPI_Send(&msg, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD); 
        //std::cout << "Processor " << rank << " sent non blocking message to processor " << rank + 1 << std::endl;
       
        // Now we expect the response 
        MPI_Recv(&msg, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        end_time = MPI_Wtime();
        std::cout << "Processor " << rank << " received response after: " << end_time - msg << " seconds\n"; 
    }
    else if (rank == 1){
        // When rank is 1, we first expect a message, then we send a response. 
        MPI_Recv(&msg, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        end_time = MPI_Wtime(); 
        std::cout << "Processor " << rank << " received message after: " << end_time - msg << " seconds\n";
        
        // Now we send the response 
        MPI_Send(&msg, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        //std::cout << "Processor " << rank << "responded to processor " << rank - 1 << std::endl; 
    }


    MPI_Finalize();
    return 0;
}