#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"

__global__ void findX(unsigned int p, unsigned int g, unsigned int h, unsigned int *x)
{
unsigned int block = blockIdx.x;
unsigned int blocksize = blockDim.x;
unsigned int thread = threadIdx.x;
unsigned int id=thread + block*blocksize;
if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }


}

int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */

  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */




  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */


unsigned int *a = (unsigned int *) malloc(Nints*sizeof(unsigned int));
unsigned int *Zmessage = (unsigned int *) malloc(Nints*sizeof(unsigned int));
FILE *pub_key = fopen("public_key.txt","r");
FILE *cyperT = fopen("message.txt","r");
fscanf(pub_key,"%u\n%u\n%u\n%u",&n,&p,&g,&h);
fclose(pub_key);
fscanf(cyperT,"%u\n",&Nints);
for(unsigned int i=0;i<Nints;i++)
{ 
 fscanf(cyperT,"%u %u\n",&Zmessage[i],&a[i]);
 
}
fclose(cyperT); 
  // find the secret key
unsigned int Nthreads = Nints;
unsigned int Nblocks = (n+Nthreads-1)/Nthreads

findx<<< Nthreads,Nblocks >>>(p,g,h,x);
cudaDeviceSynchronize();

  /* Q3 After finding the secret key, decrypt the message */
cudaMalloc(&x,Nints*sizeof(unsigned int));
cudaMemcpy(x,x,Nints*sizeof(unsigned int),cudaMemcpyHostToDevice);
ElGamalDecrypt(Zmessage,a,Nints,p,x);
int bufferSize = 1024;
unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
unsigned int charsPerInt = (n-1)/8;
printf("%u\n",charsPerInt);
unsigned int Nchars = Nints*charsPerInt;
convertZToString(Zmessage,Nints,message,Nchars);
printf("Decrypted Message = \"%s\"\n",message);

free(x);
cudaFree(x);
  return 0;

 
}
