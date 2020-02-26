Erick Juarez
CPSC 479 Sec. 1
HOMEWORK 4 - 3/4/20

Source code file: parallel-array.cpp

1. Compile the program: g++ parallel-array.cpp -o run -fopenmp
    

2. Run the program: ./run


Program has 3 parts
1. Initialize an array of 64 elements with values of 0 using 8 threads 
2. Add 2 * i to array[i] for i = 0 to i = 63
3. Calculate number of odd values in array[] in the following way: 
    1. Distribute iterations to threads in a cyclic manner (static / round-robin fashion)
    2. Each thread computes the number of odd values from its allocated iterations
    3. Master theread collects and adds the number of odd values and displays the result