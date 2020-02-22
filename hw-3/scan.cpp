#include <mpi.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/* 
Erick Juarez
CPSC 479 Sec 1
HOMEWORK 3 - 2/26/20
developed and tested using g++ version 5.3.0 (compiled wiht mpic++ to use MPI library)

The purpose of this assignment is to "allocate" slices of an arbitrary large array for each process to use exclusively
request_array contains the number of elements each array is requesting.
    Example: if the request array is {1, 4, 2} then process 0 will get 1 element, process 1 will get 4 elements, and process 2 will get 2 elements for a total of 7 elements
this program simply returns the start and end indices that each process will receive. 
Simplifications for this porgram:
    Request array is the size of the number of processors used to run it
    values of request array are randomly generated odd numbers from 1-11
    range starts at index 1 
*/

int main(int argc, char *argv[]){

    // Initialize  
    int rank; 
    int size; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int request_array[size];
    int range_array[2] = {1, 0};
    int scanned_sum;
    //Fill request array with random odd numbers from 1-11
    srand(time(NULL)); 
    for(int i = 0; i < size; i++) { 
        int odd_num = rand() % 10 + 1; 
        if (odd_num % 2 == 0) {odd_num++;}
        request_array[i] = odd_num; 
        }
    int num_to_send = request_array[rank];      // nth process will use nth element of request array to compute scan sum

    // Rank 0 will display contents of the request array. 
    if(rank == 0){
        printf("Request Array = [ ");
        for(int i = 0; i < size; i++) {
            printf("%d ", request_array[i]);
        }
        printf("]\n");
    }
    
    // All ranks execute Scan operation and store partal sums in scanned_sum
    MPI_Scan(&num_to_send, &scanned_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD); 

    // Rank 0 will range from 1 TO first number of request array (1 - [0])
    // Rank 1 will range from first number of request array +1 TO first number of request array + second number of request array ([0]+1 + [0]+[1])
    // Rank 2 will range from [0]+[1] + 1 TO [0]+[1]+[2]
    // Rank 3 will range from [0]+[1]+[2] + 1 TO  [0]+[1]+[2]+[3] and so on...
    range_array[1] = scanned_sum;                           // Since we're starting at index 1, scanned_sum contains the end of the range. 
    range_array[0] = scanned_sum - request_array[rank] + 1; // this computes the start of the range. 

    // Each rank will display its corresponding start and end indices
    printf("Rank %d: [%d - %d]\n", rank, range_array[0], range_array[1]);

    MPI_Finalize();

    return 0; 
}