/* File:  
 *    pth_hello.c
 *
 * Purpose:
 *    Illustrate basic use of pthreads:  create some threads,
 *    each of which prints a message.
 *
 * Input:
 *    none
 * Output:
 *    message from each thread
 *
 * Compile:  gcc -g -Wall -o pth_hello pth_hello.c -lpthread
 * Usage:    ./pth_hello <thread_count>
 *
 * IPP:   Section 4.2 (p. 153 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

/* Global variable:  accessible to all threads */
int thread_count;
int sum_rank;
int flag1;
int data[100];
int flag[100];
void *rank_sum(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
   long thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
 	//thread_count = 10; 
   flag1=0;
   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          rank_sum, (void*) thread);  


   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

   printf("Sum = %d\n",sum_rank);

   free(thread_handles);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *rank_sum(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
   int i;
   int range = thread_count/2;
   int cnt = 1;
   data[my_rank] = my_rank;
   flag[my_rank] = 1;	
	while(range>0)
	{
		if(my_rank<range)
		{
			while(flag[my_rank+range]<cnt);
			data[my_rank] += data[my_rank+range];
			flag[my_rank] += 1;
		}
		range = range/2;
		cnt++;
	}
   return NULL;
}  /* Hello */

