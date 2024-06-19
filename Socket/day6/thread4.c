#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD 100

void * thread_inc(void * arg);
void * thread_des(void * arg);
long long num=0; 

int main(int argc, char *argv[])
{
		pthread_t thread_id[NUM_THREAD];
		int i;

		printf("sizeof long long: %d \n",sizeof(long long));
		for(i=0; i<NUM_THREAD; i++)
		{
				if(i%2)
					pthread_create(&(thread_id[i]),NULL, thread_inc, NULL):
				else
					pthread_create(&(thread_id[i]),NULL, thread_des, NULL):
		}

void * thread_summation(void * arg)
{
		int start=((int*)arg)[0];
		int end=((int*)arg)[1];

		while(start<=end)
		{
				sum+=start;
				start++;
		}
		return NULL;
}

