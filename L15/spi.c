#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
int main(int argc, char **argv) {

  //seed random number generator
  // Q2b: get the number of threads to run with from agrv and 
  // add OpenMP API code to set number of threads here
  int Nthreads;
Nthreads =  atoi(argv);
omp_set_num_threads(Nthreads);  
  struct drand48_data *drandData; 
  drandData = (struct drand48_data*) malloc(Nthreads*sizeof(struct drand48_data));

  // Q2c: add an OpenMP parallel region here, wherein each thread initializes 
  //      one entry in drandData using srand48_r and seed based on thread number 
//#pragma omp parallel 
long int seed = Nthreads;
 #pragma omp parallel reduction(+:seed)

 srand48_r(seed,drandData+0);
double starttime =  omp_get_wtime();

  long long int Ntrials = 10000000;


  //need running tallies
  long long int Ntotal=0;
  long long int Ncircle=0;
#pragma omp parallel for
  for (long long int n=0; n<Ntrials; n++) {
    double rand1;
    double rand2;

    //gererate two random numbers (use the thread id to offset drandData)
    drand48_r(drandData+0, &rand1);
    drand48_r(drandData+0, &rand2);
    
    double x = -1 + 2*rand1; //shift to [-1,1]
    double y = -1 + 2*rand2;

    //check if its in the circle
    if (sqrt(x*x+y*y)<=1) Ncircle++;
    Ntotal++;

    if (n%100 ==0) {
      double pi = 4.0*Ncircle/ (double) (n);
      printf("Our estimate of pi is %g \n", pi);
//#pragma omp barrier
	
}
  }
double endtime = omp_get_wtime();
double time = endtime-starttime;
  double pi = 4.0*Ncircle/ (double) (Ntotal);
  printf("Our final estimate of pi is %g and time is %g \n", pi, time);
#pragma omp barrier 
  free(drandData);
  
  return 0;
}
