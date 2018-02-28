#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

//compute a*b mod p safely
unsigned int modprod(unsigned int a, unsigned int b, unsigned int p) {
  /* Q1.2: Complete this function */
unsigned int za, ab;
za = a %p ;//remainder za
b = b%p;//remainder b
ab = 0;//set ab to be 0
while(b){//while b 
if(b%2 != 0){//remainder can't be 0
ab = (ab + za)%p;//modular addition
}
za = (za*2)%p;//multiply by 2
b /= 2;//set b
}
return ab;
}

//compute a^b mod p safely
unsigned int modExp(unsigned int a, unsigned int b, unsigned int p) {
  /* Q1.3: Complete this function */
unsigned int z, aExpb;//initiallize variables
z=a;//set z to be a
aExpb = 1;//set aExpb to be 1
while(aExpb >0){//do while aExpb is greater than 0
if(b%2 ==1){//if remainder is 1
 aExpb = (aExpb *z)% p;//modprod
}
z=(z*z)%p;//modprod
b = b /2;//modprod
}
return aExpb % p;
}

//returns either 0 or 1 randomly
unsigned int randomBit() {
  return rand()%2;
}

//returns a random integer which is between 2^{n-1} and 2^{n}
unsigned int randXbitInt(unsigned int n) {
  unsigned int r = 1;
  for (unsigned int i=0; i<n-1; i++) {
    r = r*2 + randomBit();
  }
  return r;
}

//tests for primality and return 1 if N is probably prime and 0 if N is composite
unsigned int isProbablyPrime(unsigned int N) {

  if (N%2==0) return 0; //not interested in even numbers (including 2)

  unsigned int NsmallPrimes = 168;
  unsigned int smallPrimeList[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
                                37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 
                                79, 83, 89, 97, 101, 103, 107, 109, 113, 
                                127, 131, 137, 139, 149, 151, 157, 163, 
                                167, 173, 179, 181, 191, 193, 197, 199, 
                                211, 223, 227, 229, 233, 239, 241, 251, 
                                257, 263, 269, 271, 277, 281, 283, 293, 
                                307, 311, 313, 317, 331, 337, 347, 349, 
                                353, 359, 367, 373, 379, 383, 389, 397, 
                                401, 409, 419, 421, 431, 433, 439, 443, 
                                449, 457, 461, 463, 467, 479, 487, 491, 
                                499, 503, 509, 521, 523, 541, 547, 557, 
                                563, 569, 571, 577, 587, 593, 599, 601, 
                                607, 613, 617, 619, 631, 641, 643, 647, 
                                653, 659, 661, 673, 677, 683, 691, 701, 
                                709, 719, 727, 733, 739, 743, 751, 757, 
                                761, 769, 773, 787, 797, 809, 811, 821, 
                                823, 827, 829, 839, 853, 857, 859, 863, 
                                877, 881, 883, 887, 907, 911, 919, 929, 
                                937, 941, 947, 953, 967, 971, 977, 983, 
                                991, 997};

  //before using a probablistic primality check, check directly using the small primes list
  for (unsigned int n=1;n<NsmallPrimes;n++) {
    if (N==smallPrimeList[n])   return 1; //true
    if (N%smallPrimeList[n]==0) return 0; //false
  }

  //if we're testing a large number switch to Miller-Rabin primality test
  /* Q2.1: Complete this part of the isProbablyPrime function using the Miller-Rabin pseudo-code */
  unsigned int r,d;//initiallize variables
  r=0;//set r to be 0 
  d = r-1;//set d to be r-1
  while(d%2 ==0)//find d and r
{
	r = r+1;
	d /=2;
}
  for (unsigned int n=0;n<NsmallPrimes;n++) {//n to the size of the list
unsigned int k = rand()%(N-1) +1;	//k is a random number
unsigned int x = modExp(k,d,N);//modulo exponential
	if(x==1||x==N-1) continue;// if x meets conditions continue loop
	for(unsigned int i=0;i<r-1;i++)//i til r-1
{	x = modprod(x,x,N);//modulo multiplication
	if(x==1) return 0; // return 0 for false
	if(x==N-1) continue;//if x meets condition continue loop
	
  }
return 0;//false
}
  return 1; //true
}

//Finds a generator of Z_p using the assumption that p=2*q+1
unsigned int findGenerator(unsigned int p) {
  /* Q3.3: complete this function and use the fact that p=2*q+1 to quickly find a generator */
unsigned int val1,val2,val3,val4,val5, gen,q;//initiallize variables
q=(p-1)/2;//q
for(unsigned int i=1;i<p-1;i++)//generator can be from 1 to p-1
{
  val1 = pow(i,q);//calculate parameters
  val2 = fmod(val1,p);
  val3 = pow(i,2);
  val4 = fmod(val3,p);
  val5 = fmod(i,p);
if(val2 !=1 && val4 !=1 && val5 !=0) 
{
	gen=i;//set generator to be i if above conditions are met
	
}
}
return gen;


}
