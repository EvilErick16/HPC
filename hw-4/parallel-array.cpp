/* 
Erick Juarez
CPSC 479 Sec 1
HOMEWORK 4 - 3/4/20
developed and tested using g++ version 5.3.0 (compiled wiht mpic++ to use MPI library)

Program has 3 parts
1. Initialize an array of 64 elements with values of 0 using 8 threads 
2. Use a parallel construct to add 2 * i to array[i] for i = 0 to i = 63
3. 
*/
#include<omp.h>
#include<stdio.h>
#define THREADS 8

int main(){

    // Initialize 
    const int SIZE = 64;
    int array[SIZE];
    int tid; 
    omp_set_num_threads(THREADS);

    // Parallel region using the shared array 
    #pragma omp parallel private(tid) shared(array)
    {
        tid = omp_get_thread_num();
        // Parallel for loop initializes all array values to 0
        #pragma omp for schedule(static, 1)
        for (int i =0; i < SIZE; i++){
            array[i] = 0;
            printf("Thread: %d Array Index: %d Value: %d\n", tid, i, array[i]);
        }
    }

    return 0; 
}