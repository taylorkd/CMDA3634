#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed;
  
  seed = clock(); //this will make your program run differently everytime
  //seed = 0; //uncomment this and you program will behave the same everytime it's run
  
  srand48(seed);


  //begin by getting user's input
	unsigned int n;

  printf("Enter a number of bits: ");
  scanf("%u",&n);

  //make sure the input makes sense
  if ((n<2)||(n>30)) {
  	printf("Unsupported bit size.\n");
		return 0;  	
  }

 int p;
p = randXbitInt(n);//set p to be a random number
while(isProbablyPrime(p)==0)//while p is not prime
{
  /* Q2.2: Use isProbablyPrime and randomXbitInt to find a random n-bit prime number */
 p = randXbitInt(n);//generate a new number
}

printf("p = %u is probably prime.\n",p);

  /* Q3.2: Use isProbablyPrime and randomXbitInt to find a new random n-bit prime number 
     which satisfies p=2*q+1 where q is also prime */
  int q;
q = randXbitInt(n);//set q to be a random number
while(isProbablyPrime(2*q+1)==0 && isProbablyPrime((p-1)/2)==0)//while the conditions are not met
{
  q = randXbitInt(n);//generate new q

}
p=2*q+1;//find p
	printf("p = %u is probably prime and equals 2*q + 1. q= %u and is also probably prime.\n", p, q);  

	/* Q3.3: use the fact that p=2*q+1 to quickly find a generator */
	unsigned int g = findGenerator(p);

	printf("g = %u is a generator of Z_%u \n", g, p);
//bonus
unsigned int x,h,t,val1; 
x = randXbitInt(n);
while(x>p-1 && x < 0)
{
 x = randXbitInt(n);
}
h = pow(g,x);
for(int i=0;i<p-1;i++)
{
  val1 = pow(g,i);
 if( h == val1)
 x =i;
 break;


} 
printf("x= %u is the secret key of Z_%u and generator %u \n",x,p,g);
return 0;
}
