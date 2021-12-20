//
// CS4900
// Project 03
// Steven Stillwell
// System = owens
// Compiler syntax = ./compile.sh proj03
// Job Control File = proj03.pbs
// Additional Files = NA
// Results file = proj03.tex
//

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <assert.h>
#include <time.h>

unsigned long* calculateMandP(int N) {
  unsigned long *MandP = (unsigned long *)malloc(sizeof(unsigned long) * 2);
  double rsq2=0.70710678118654752440;
  unsigned long M=0, P=0;
  float x, y, rs;
  int randomPoints;

  for(randomPoints = 0; randomPoints < N; ++randomPoints) {
    x=(rand() / (float)RAND_MAX);
    y=(rand() / (float)RAND_MAX);
    rs=x*x+y*y;
    if (rs<1) {     //point is inside circle
      ++M;
      if (x<rsq2 && y<rsq2) {     //point is inside inner square
        ++P;
      }
    }
  }

  MandP[0]=M;
  MandP[1]=P;
  return MandP;
}

int main (int argc, char** argv[]) {

  const double targetEpsilon = 0.0000001;
  double epsilonM = 1.0;
  float estimateM = 0.f;
  float estimateP = 0.f;
  float nextEstimateM = 0.f;
  float nextEstimateP = 0.f;
  double epsilonP = 1.0;
  int N = atoi(argv[1]);
  float points = (float)N;

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  srand(time(NULL));
  
  unsigned long *MandP = NULL;
  MandP = calculateMandP(N);

  unsigned long totalM;
  MPI_Allreduce(&MandP[0], &totalM, 1, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);
  unsigned long totalP;
  MPI_Allreduce(&MandP[1], &totalP, 1, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);
  if(world_rank == 0) {
    estimateM = 4.f*((float)totalM/((float)points*28.f));
    estimateP = 2*((float)totalM/(float)totalP);
    nextEstimateM = 0;
    nextEstimateP = 0;
  }

  while(epsilonM>=targetEpsilon && epsilonP>=targetEpsilon){
    MandP = calculateMandP(N);
    MPI_Allreduce(&MandP[0], &totalM, 1, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&MandP[1], &totalP, 1, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);
    if(world_rank == 0) {
      nextEstimateM = 4.f*((float)totalM/((float)points*28.f));
      nextEstimateP = 2*((float)totalM/(float)totalP);
      epsilonM = fabs(estimateM-nextEstimateM);
      epsilonP = fabs(estimateP-nextEstimateP);
      estimateM = nextEstimateM;
      estimateP = nextEstimateP;
      nextEstimateM = 0;
      nextEstimateP = 0;
    }
    MPI_Bcast(&epsilonM, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&epsilonP, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
  }
  if(world_rank == 0) {
    printf("Value of Pi using 4*(M/N) = %f \n", estimateM);
    printf("Value of Pi using 2*(M/P) = %f \n", estimateP);
    printf("M=%llu P=%llu\n", totalM, totalP);
  }


  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  exit(0);
}