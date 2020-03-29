/* 
Erick Juarez
CPSC 479 Sec 1
HOMEWORK 5 - 3/25/20
tested using nvcc - CUDA compiler driver release 9.0, V9.0.176
*/

#include <stdio.h>
#include <cuda.h>
#define P1 16     // Size of array for problem 1
#define P2 1024   // Size of array for problems 2 & 3
#define P4 8000   // Size of array for problem 4


// device function to initialize array - used in problems 1 & 2 
__global__ void initialize(int *array){
    array[threadIdx.x] = 0;
}

// device function will add values to array - used in problems 3 & 4
__global__ void add(int *array){
  array[threadIdx.x] += threadIdx.x;
}

// Main function 
int main(int argc, char * argv[]) {

    int *host_array;     // host copy of array 
    int *dev_array;      // device copy of array   
    int byte_size;       // size in bytes of an object 

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Problem 1 - initialize array of size 16 to all zeroes 
    byte_size = P1 * sizeof(int);                 // get size of 16 integers in bytes 
    dim3 blockd(P1);                            // Create dim3 type with value of 16 on the first dimension   
    cudaMalloc((void **) &dev_array, byte_size);  // Allocate memory on the device 
    initialize<<<1, blockd>>>(dev_array);       // Launch new kernel on device with 16 threads 
    host_array = (int *)malloc(byte_size);        // Allocate memory for the host
    cudaMemcpy(host_array, dev_array, byte_size, cudaMemcpyDeviceToHost); // Copy from device to host 

    // Verify that array was allocated and copied properly to the host, then cleanup 
    try {
      for(int c = 0; c < P1; c++){
        if(host_array[c] != 0) {throw "NON_ZERO_ELEM";}
      }
    } catch (...) {
      printf("Problem 1 - Elements not initialized properly!\n");
      cudaFree(dev_array);
      free(host_array);
      return 0; 
    }
    printf("Problem 1 - Successfully initialized array with %d elements\n", P1); 
    cudaFree(dev_array);
    free(host_array); 

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Problem 2 - initialize array of size 1024 to all zeroes
    byte_size = P2 * sizeof(int);                // get size of 1024 integers in bytes
    dim3 bd(P2);                                 // create dim3 object with 1024 as the first dimensoin 
    cudaMalloc((void**) &dev_array, byte_size);  // Allocate memory on device 
    initialize<<<1, bd>>>(dev_array);            // Launch kernel on device with 1024 threads 
    host_array = (int*)malloc(byte_size);        // Allocate memory on the host 
    cudaMemcpy(host_array, dev_array, byte_size, cudaMemcpyDeviceToHost); // Copy from device to host 

    // Verify that array was allocated and copied properly, then cleanup
    try {
      for(int c = 0; c < P2; c++){
        if(host_array[c] != 0) {throw "NON_ZERO_ELEM";}
      }
    } catch (...) {
      printf("Problem 2 - Elements not initialized properly!\n");
      cudaFree(dev_array);
      free(host_array);
      return 0; 
    }
    printf("Problem 2 - Successfully initialized array with %d elements\n", P2);
   
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Problem 3 - add i to array[i] 
    add<<<1, bd>>>(dev_array);          // Launch add kernel with array from the previous problem 
    cudaMemcpy(host_array, dev_array, byte_size, cudaMemcpyDeviceToHost); // Copy from modified vaues to host 

    // Verify values are correct
    try {
      for(int c = 0; c < P2; c++){
        if(host_array[c] != c) {throw "ADD_OP_MATCH";}
      }
    } catch (...) {
      printf("Problem 3 - Elements not added properly!\n");
      cudaFree(dev_array);
      free(host_array);
      return 0; 
    }
    printf("Problem 3 - Successfully added i to array[i] with %d elements\n", P2);
    cudaFree(dev_array);
    free(host_array); 

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Problem 4 - same as problem 3, but with 8000 elements 
    byte_size = P4 * sizeof(int);
    dim3 gd(P4);
    cudaMalloc((void**) &dev_array, byte_size);  
    initialize<<<1, gd>>>(dev_array);           // Initialize array 
    add<<<1, gd>>>(dev_array);                  // Add index to array           
    host_array = (int*)malloc(byte_size);       
    cudaMemcpy(host_array, dev_array, byte_size, cudaMemcpyDeviceToHost); 

    // Verify values are correct, 8000 threads might be too much for the device and the answer is incorrect
    try {
      for(int c = 0; c < P4; c++){
        if(host_array[c] != c) {throw "ADD_OP_MATCH";}
      }
    } catch (...) {
      printf("Problem 4 - Elements not added properly!\n");
      cudaFree(dev_array);
      free(host_array);
      return 0; 
    }
    printf("Problem 4 - Successfully added i to array[i] with %d elements\n", P4);
    cudaFree(dev_array);
    free(host_array);      
    return 0;
}