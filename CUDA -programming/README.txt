Erick Juarez
CPSC 479 Sec. 1
HOMEWORK 5 - 3/25/20

This program uses NVIDIA's Compute Unified Device Architecture (CUDA) to show how a typical parallel 
program is written. It uses nvcc which is a compiler driver that invokes the correct tools and 
compilers to achieve communication between the host (Compute) and device (GPU) for general GPU processing 

Source code file: cuda-threads.cu

1. Compile the program: nvcc cuda-threads.cu -o execute
    

2. Run the program: ./execute


This program uses CUDA to run instructions on the GPU, it has 4 problems: 

1. Initialize an array of size 16 to all zeroes in peaarallel using parallel threads 

2. Change the value of the array size to 1024

3. Create another kernel that adds i to array[i] in parallel using parallel threads 

4. Change the size of the array to 8000 from problem 3