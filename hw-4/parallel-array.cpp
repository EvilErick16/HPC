/* 
Erick Juarez
CPSC 479 Sec 1
HOMEWORK 4 - 3/4/20
developed and tested using g++ version 5.3.0
*/
#include<omp.h>
#include<stdio.h>
#define THREADS 8

int main(){

    // Initialize 
    const int SIZE = 64;
    int array[SIZE];
    int tid, private_sum, odd_count;
    omp_set_num_threads(THREADS);

    // Parallel region for Problem 1 
    #pragma omp parallel shared(array)
    {
        // Initialize all array values to 0
        #pragma omp for schedule(static)
        for (int i = 0; i < SIZE; i++){
            array[i] = 0;
        }
    }

    // Parallel region Problem 2
    #pragma omp parallel shared(array) private(tid)
    {
        tid = omp_get_thread_num();
        // Add 3 * i to array[i] for i = 0 to i = 63
        #pragma omp for schedule(static, 1)
        for (int i = 0; i < SIZE; i++){
            array[i] += 3 * i;
            printf("Thread: %d Array Index: %d Value: %d\n", tid, i, array[i]);
        }
    }

    // Parallel region for problem 3
    #pragma omp parallel private(tid, private_sum) shared(array, odd_count)
    {
        tid = omp_get_thread_num();
        private_sum = 0; 
        // Calculate odd number count privately in a cyclic distribution
        #pragma omp for schedule(static, 1)
        for (int i = 0; i < SIZE; i++){
            if(array[i] % 2 != 0) { 
                private_sum+= 1; 
                }
        }
        // Collect all private counts
        #pragma omp critical
        {
            odd_count+= private_sum;
        }
        // Master thread prints result
        if(tid == 0){
            printf("=========================\nOdd numbers in array[]: %d\n", odd_count);
        }
    }
    return 0; 
}