#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
sem_t mutex,empty,full;
static int buff=0;
void *pro()
	{
	while(1)
		{
		sem_wait(&empty);
		sem_wait(&mutex);
		if(buff<10)
			{
			buff++;
			printf("\nProducer produce item and buffer size now is %d",buff);
			}
		else if(buff>=10)
		printf("\nBuffer is already full no space left to produce");
		sem_post(&mutex);
		sem_post(&full);
		sleep(1 + rand()%2);
		}
	}
void *con()
	{
	while(1)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		if(buff!=0)
			{
			buff--;
			printf("\nConsumer consumed item remaining item %d",buff);
			}
		else if(buff==0)
			printf("\nbuffer is empty nothing to consume");
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1 + rand()%6);
	}
}
void main()
{
pthread_t p1,c2;
sem_init(&mutex,2,1);
sem_init(&empty,2,10);
sem_init(&full,2,0);
for(int i=0;;)
	{
	pthread_create(&p1,NULL,pro,NULL);
	pthread_create(&c2,NULL,con,NULL);
	pthread_join(p1,NULL);
	pthread_join(c2,NULL);
	}
}
