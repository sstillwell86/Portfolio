//Steven Stillwell

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>
#include <math.h>

float dot(float *V1, float *V2, int Nr1) {
  int i;
  float sum = 0.0;
  for (i = 0; i < Nr1; i++) {
    sum += V1[i]*V2[i];
  }
  return sum;
}

float* multiply(float V1element, float *V3, int L2) {
  float *Vresult = (float *)malloc(sizeof(float) * (L2));
  assert(Vresult != NULL);
  for (int i = 0; i < L2; i++) {
    Vresult[i] = V3[i]*V1element;
  }
  return Vresult;
}

int main(int argc, char** argv) {

  int rank, ncpu;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &ncpu);
  MPI_Barrier(MPI_COMM_WORLD);

  int A = atoi(argv[3]);
  int B = atoi(argv[4]);
  int L1 = atoi(argv[1]);
  int L2 = atoi(argv[2]);
  float local_sum;
  float global_sum;
  float matrix[L2][L1];
  float dx1, dx2, pi, norm1, norm2;
  int Nr1, R1;
  float xlast1;
  if (rank != 0) {  //leaves rank 0 free to recieve each part of vector multiplication
    pi = acos(-1.0);
    dx1 = 2.0*pi/L1;
    dx2 = 2.0*pi/L2;
    norm1 = sqrt(2.0/L1);
    norm2 = sqrt(2.0/L2);
    Nr1=(int)(L1/(ncpu-1));
    R1=(L1%(ncpu-1));

    if ((rank-1)<R1) {
      ++Nr1;
      xlast1=-dx1/2.0+(rank-1)*Nr1*dx1;
    }else{
      xlast1=-dx1/2.0+R1*(Nr1+1)*dx1+((rank-1)-R1)*Nr1*dx1;
    }
  }else{
    Nr1=(int)((L1/(ncpu-1))+1);
  }
  float *V1 = (float *)malloc(sizeof(float) * Nr1);
  assert(V1 != NULL);
  float *V2 = (float *)malloc(sizeof(float) * Nr1);
  assert(V2 != NULL);
  float *V3 = (float *)malloc(sizeof(float) * L2);
  assert(V3 != NULL);

  int i;
  float x1, x2;
  x1=xlast1;

  for (i = 0; i < Nr1; i++) {
    x1 = (dx1/2)+i*dx1;
    V1[i]=norm1*cos(A*x1);
    V2[i]=norm1*sin(B*x1);
  }
  for (i = 0; i < L2; i++) {
    x2 = (dx2/2)+i*dx2;
    V3[i]=norm2*cos(B*x2);
  }
  // local_sum = dot(V1, V2, Nr1);

  int sendCount = 0;
  int recvCount = 0;
  int sendingRank = 1;
  int column;
  int sentElementCount = 1;
  while (sendCount < Nr1) {
    float *Vresult = (float *)malloc(sizeof(float) * L2);
    if (rank != 0) {
      Vresult = multiply(V1[sendCount], V3, L2);
    }
    // For loop sends the first column of each rank's result
    for (int i=1; i < ncpu; i++) {
      if (rank == i) {
        MPI_Send(Vresult, L2, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        sendCount++;
        printf("sent element %d\n", sentElementCount);
        sentElementCount++;
      }
      else if (rank == 0) { // rank 0 stuck in for loop
        MPI_Recv(Vresult, L2, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);     //i value is rank 0's i value, not sender rank
        printf("element %d received\n", sentElementCount-1);
        recvCount++;
        sentElementCount++;
        sendCount++;
        printf("recieved %d columns\n", recvCount);
        if (i>R1){
          column = i * Nr1 + R1 - 1;       //i value is rank 0's i value, not value of sending rank
        }else{
          column = i * Nr1 - 1;
        }
        for (int j=0; j < L2; j++){
          matrix[j][column] = Vresult[j];
        }               //rank 0 i not increasing
      }
      if (i==R1 && sendCount==Nr1){
        i+=(ncpu-R1-1);
      }
    }
    free(Vresult);
    if (rank == 0 && recvCount == L2){
      printf("rank %d ended while loop\n", rank);
      sendCount = Nr1;
	}
  }
  free(V1);
  free(V2);
  free(V3);


  //  if(rank == 0){
    // local_sum = 0.0f;
  // }

  // MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  // if (rank == 0) {
    // printf("The dot product is %f\n", global_sum);
  // }





  if (rank == 0) {
    printf("printing matrix");
    for (int i=0; i < L1; i++) {
      for (int j=0; j < L2; j++) {
        printf("%f ", matrix[i][j]);
        if (j == (L2-1)) {
          printf("\n");
        }
      }
    }
  }
  printf("reached barrier\n");
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}