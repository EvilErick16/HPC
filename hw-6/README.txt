Erick Juarez
CPSC 479 Sec. 1
HOMEWORK 6 - 4/20/20

This assignment contains 2 separate programs: 

1. A CUDA program that computes the square of a N dimensoinal matrix (Program has a default value of N = 32)

    i) Compile the program: nvcc matrix_square.cu 

    ii) Run the program: ./a.out >> out.txt

    iii) View out.txt with text editor of your choce (ex: nano out.txt)

        When running the program, it is useful to redirect output to a separate file when dealing with large values of N since it's hard to read from standard output.
        To test with different values of N, simply change value of RLEN on line 30 of matrix_square.cu to the value of choice. Recompile, and run!  
        
        Here is a sample output of the program with a 4 dimensional matrix (tested on aries.ecs.fullerton.edu)
        ==========Original Matrix==========
        [1]  [2]  [3]  [4] 
        [5]  [6]  [7]  [8] 
        [9]  [10] [11] [12] 
        [13] [14] [15] [16] 
        ==========Squared Matrix==========
        [90]  [100] [110] [120] 
        [202] [228] [254] [280] 
        [314] [356] [398] [440] 
        [426] [484] [542] [600] 


2. A Fortran 90 program that does the following: 

    a) Declare a 4 x 4 matrix A with all values of 4. 
    b) Declare a 4 x 4 matrix B with values B(i,j) = i + j + 1
    c) Compute C = A + B
    d) In C, replace the elements with value of 8 with the value 16
    e) Display A, B, and C 

    i) Compile the program: gfortran fortran_matrix.f90
    
    ii) Run the program: ./a.out 
        
    Program was tested on titanv.ecs.fullerton.edu 
