/* 
Erick Juarez
CPSC 479 Sec 1
HOMEWORK 6 - 4/20/20
tested using nvcc - CUDA compiler driver release 9.0, V9.0.176
*/

#include <stdio.h>
#include <cuda.h>

// device function: perform calculations to square a matrix 
__global__ void square(int *matrix, int *result, int matrix_size){
    // solves 1 row per thread 
    int row_id = threadIdx.x; 
    for (int col_ix = 0; col_ix < matrix_size; col_ix++){
        for (int row_ix = 0; row_ix < matrix_size; row_ix++){
            result[row_id * matrix_size + col_ix] += matrix[row_id * matrix_size + row_ix] * matrix[row_ix * matrix_size + col_ix];
        }
    }
}

// device function is used to initalize both matrices in parallel 
__global__ void init(int * matrix, int * result){
    result[threadIdx.x] = 0; 
    matrix[threadIdx.x] = threadIdx.x +1; 
}

// Main program: initialization 
int main(int argc, char* argv[]){  
    const int RLEN = 32;            // matrix of size RLEN x RLEN (matrix has to be a sqaure) 
    const int MSIZE = RLEN * RLEN;  // total number of elements in the matrix 

    // Allocate memory on host for inpaut and output 
    int *h_matrix, *h_result;

    // allocate memory on device for copy of input and output 
    int *d_matrix, *d_result;
    int byte_size = MSIZE * sizeof(int);
    dim3 b_dim(MSIZE);
    cudaMalloc((void**) &d_matrix, byte_size);
    cudaMalloc((void**) &d_result, byte_size);

    // initialize device matrix and result matrix. Then square original matrix and place result in result matrix
    init<<<1, b_dim>>>(d_matrix, d_result);
    square<<<1, b_dim>>>(d_matrix, d_result, RLEN);

    // copy device ouput to host and cleanup 
    h_matrix = (int *) malloc(byte_size);
    h_result = (int *) malloc(byte_size);
    cudaMemcpy(h_matrix, d_matrix, byte_size, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_result, d_result, byte_size, cudaMemcpyDeviceToHost);
    cudaFree(d_matrix);
    cudaFree(d_result);

    // Print results
    printf("==========Original Matrix==========\n");
    for (int i = 0; i < RLEN; i++){
        for (int k = 0; k < RLEN; k++){
            printf("[%d] ", h_matrix[RLEN * i + k]);
        }
        printf("\n");
    }
    printf("==========Squared Matrix==========\n");
    for (int i = 0; i < RLEN; i++){
        for (int k = 0; k < RLEN; k++){
            printf("[%d] ", h_result[RLEN * i + k]);
        }
        printf("\n");
    }
    free(h_matrix);
    free(h_result);
    return 0; 
}