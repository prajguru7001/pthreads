#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

/* Global variable:  accessible to all threads */
int thread_count = 2;  
double total;
int flag, j;
double PI;
void *rank_sum(void* rank);  /* Thread function */
int n = 10000000;

void *pi(void* rank);

/*--------------------------------------------------------------------*/
int main() {
   long thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
  // thread_count = 10; 
 
 int chunk;
 double step, result = 0.0;
int flag =0;
 step = 1.0/(double)n;

   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for(thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          pi, (void*) thread);  
	


   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 


	
//printf("total = %f, step = %f\n",total, step);
   printf("PI = %f\n",PI);

   free(thread_handles);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *pi(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 

	double step;
        int i, chunk = n/thread_count;
        double x, pi, sum = 0.0;
        step = 1.0/(double)n;

        for(i=my_rank*chunk; i<(my_rank*chunk)+chunk; i++){
                x = (i)*step;
                sum = sum + 4.0/(1.0+x*x);

        }
	sum = sum*step;
	
	while(flag != my_rank){};
	PI = PI+sum;
	flag++;
		
   return NULL;
}  /* Hello */
