#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
int main(int argc, int **argv){
//need running tallies
int rank,size;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
long long int Ntotal;
long long int Ncircle;

//seed random number generator
double seed = 1.0; 
srand48(seed);



for( rank=0;rank<size;rank++)
{
	printf("Rank:%d Size:%d",rank,size);
	double rand1 = drand48();//drand48 returns a number between 0 and 1
	double rand2 = drand48();
	double x = -1 +2*rand1;//shift to [-1,1]
	double y = -1 +2*rand2;
MPI_Allreduce(&x,&y,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	if(sqrt(x*x+y*y)<=1) Ncircle++;
	Ntotal++;

}


double pi = 4.0*Ncircle/ (double) Ntotal;
if(rank==0){
printf("Our estimate of pi is %f \n",pi);
}

MPI_Finalize();
return 0;
}
