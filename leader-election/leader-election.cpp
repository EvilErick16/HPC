/* 
Erick Juarez
CPSC 479 Sec 1
Project 1 - 3 / 14 / 20 
developed and tested using g++ version 5.3.0 using mpic++ 
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    // Initialize
    int even_rank_odd_rank[4]; // Array stucture: [even, rank, odd, rank] where rank is the rank that generated even or odd  
    int rand_value; 
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    // Rank 0 will generate the first value and send both values to Rank 1 
    if (rank == 0) {
        srand(time(NULL));
        rand_value = rand() % 90 + 11;
        even_rank_odd_rank[1] = rank;
        even_rank_odd_rank[3] = rank;
        // If rand_value is even append rand_value and 9999 to array tha will be sent 
        if(rand_value % 2 == 0) {
            even_rank_odd_rank[0] = rand_value; 
            even_rank_odd_rank[2] = 9999;
        }
        // If rand_value is odd append 9990 and rand_value to array that will be sent 
        else {
            even_rank_odd_rank[0] = 9990; 
            even_rank_odd_rank[2] = rand_value;
        }
        // Rank 0 sends values to rank 1 
        printf("Rank %d  generated: %d sends: %d, %d\n", rank, rand_value, even_rank_odd_rank[0], even_rank_odd_rank[2]);
        MPI_Send(even_rank_odd_rank, 4, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);

        // Rank 0 Recieves values from last rank, then declares President and Vice-president
        MPI_Recv(even_rank_odd_rank, 4, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("=================================\n     President: rank %d value: %d\nVice-president: rank %d value: %d\n",
            even_rank_odd_rank[1], even_rank_odd_rank[0], even_rank_odd_rank[3], even_rank_odd_rank[2]);

    }

    // All other ranks will first recieve values from the previous rank, generate a value, then send it to the next rank 
    else {

        // Rank recieves values from Rank - 1 and generates a random value
        MPI_Recv(even_rank_odd_rank, 4, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        srand(time(NULL) + rank);
        rand_value = rand() % 90 + 11; 
        // If rand_value is even, compare it with even value received 
        if(rand_value % 2 == 0) {
            if(rand_value < even_rank_odd_rank[0]) {
                even_rank_odd_rank[0] = rand_value;
                even_rank_odd_rank[1] = rank;
                }
        }
        // If rand_value is odd compare it with odd value received 
        else {
            if(rand_value < even_rank_odd_rank[2]) {
                even_rank_odd_rank[2] = rand_value;
                even_rank_odd_rank[3] = rank;
                }
        }
        // Send values to the next Rank (last rank sends to rank 0)
        printf("Rank %d  generated: %d sends: %d, %d\n", rank, rand_value, even_rank_odd_rank[0], even_rank_odd_rank[2]);
        MPI_Send(even_rank_odd_rank, 4, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}