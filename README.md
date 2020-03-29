# About 

This repository contains C++ snippets that use Message Passing Interface (MPI) libraries and OpenMP to implement parallel programs.

Developed for CPSC 479 - High Performance Computing 

# Requirements 

[Docker](https://docs.docker.com/install/) is used to maintain compatibility across differernt systems


[Alpine-MPICH](https://hub.docker.com/r/nlknguyen/alpine-mpich/) is the custom Docker image of Alpine Linux
that contains a portable implementation of MPI standard.

[MPICH](https://www.mpich.org/documentation/guides/) also works if you have a Linux machine.  

# Running the Docker Image  

1. Clone this repository 

`git clone https://github.com/EvilErick16/HPC.git`

2. Navigate to project directory 

`cd HPC/`

3. Run the Docker container 

`./run`

4. Now that image is running you should see the following as your terminal prompt

`/project $` 

## Running C++ programs 

Navigate to a sub-directory for the project you want to run  

Compile C++ source code with the following command 

`mpic++ [source.cpp] -o [executable]`

then run the executable file with the following command 

`mpirun -n 2 ./[executable]`

the above command will run on 2 processors, replace the 2 for the number of processors you want the program to run on 
