//
// CS4900
// Project 05
// Steven Stillwell
// System = owens
// Compiler syntax = ./compile.bash proj05
// Job Control File = proj05.pbs
// Results file = NA
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>
#include <math.h>
#include <string.h>

int main(int argc, char** argv) {

  int rank, ncpu;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &ncpu);
  MPI_Barrier(MPI_COMM_WORLD);

  if (argc != 3 && rank==0){
    printf("Requires 3 arguments.\n");
    printf("Usage: proj05 -r n   A initialized as an nxn matrix with random numbers.\n");
    printf("Usage: proj05 -d n   A initialized as an nxn diagonal matrix where the diagonal elements are row number indices.\n");
    printf("Usage: proj05 -f filename   A read from file.\n");
    MPI_Abort(MPI_COMM_WORLD,1);
    exit(1);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  char *function = argv[1];
  int n = atoi(argv[2]);
  if (strcmp(function, "-n")==1) {
    srand(time(NULL)*rank);
    float matrix[n][n];
    for (int i = 0; i < n; i++) { //Generates random matrix
      for (int j = 0; j < n+1; j++) {
        matrix[i][j] = (float)rand();
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n+1; j++) {
        printf("%g ", matrix[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    for (int i = 0; i < n-1; i++) {     //Gaussian elimination to find upper
      for (int j = 0; j+i < n-1; j++) { //right triangle
        float numerator = matrix[j+1+i][i];
        for (int k = 0; k+i < n+1; k++) {
          matrix[j+1+i][k+i]-=((numerator/matrix[i][i])*matrix[i][k+i]);
        }
        for (int l = 0; l < n; l++){
          for (int m = 0; m < n+1; m++) {
			printf("%g ", matrix[l][m]);
          }
          printf("\n");
        }
        printf("\n");
      }
    }
    printf("\n\n");
    for (int i = 0; i < n; i++) { //Print upper diagonal matrix
      for (int j = 0; j < n+1; j++) {
        printf("%g ", matrix[i][j]);
      }
      printf("\n");
    }
  }
  MPI_Finalize();
  exit(0);
}