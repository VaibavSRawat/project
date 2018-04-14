#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
sem_t mutex,empty,full;
static int buff=10;
void *pro()
{
sem_wait(&empty);
sem_wait(&mutex);
buff++;
printf("Producer produce item and buffer size now is %d",buff);
sem_post(&mutex);
sem_post(&full);
}
void *con()
{
sem_wait(&full);
sem_wait(&mutex);
buff--;
printf("Consumer consumed item remaining item %d",buff);
sem_post(&mutex);
sem_post(&empty);

}
void main()
{
pthread_t p1,c2;
sem_init(&mutex,2,1);
sem_init(&empty,2,10);
sem_init(&full,2,0);
pthread_create(&p1,NULL,pro,NULL);
pthread_create(&c2,NULL,con,NULL);
}
