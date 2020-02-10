#include <stdio.h> 
#include <mpi.h> 


int main(int argc, char *argv[]){

    int rank; 
    int size; 
    double start_time; 
    double end_time; 

    MPI_Init( &argc, &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Request request; 
    MPI_Status status; 

    int number = 0;

    if(rank == 0){
        start_time = MPI_Wtime(); 
        number = -1; 
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request); 
        printf("Porcess 0 sent number %d to process 1\n", number); 
        MPI_Wait(&request, &status); 
        end_time = MPI_Wtime();
        printf("Non-blocking with wait: %f\n", end_time - start_time);
    }
    else if(rank == 1){
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status); 
        //printf("Porcess 1 received number %d form process 0\n", number); 
    }

    MPI_Finalize();

    return 0; 
}