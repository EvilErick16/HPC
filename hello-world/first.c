#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
	
    MPI_Init(NULL, NULL);

	// char name[20]; 
	// printf("What is your name? ");
	// scanf("%s", name); 
	printf("My name is Erick\n");

	MPI_Finalize();
}

