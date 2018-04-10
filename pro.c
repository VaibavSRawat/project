#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
static int buff;
void *producer();
void *consumer();
int main()
{
int a;
pthread_mutex_t m1;
char ch;
pthread_mutex_init(&m1,NULL);
pthread_t pro,con;
do
{
printf("\nEnter one of the following");
printf("\nEnter 1 for producer");
printf("\nEnter 2 for consumer");
scanf("%d",&a);
if(a==1)
{
pthread_create(&pro,NULL,producer,NULL);
  pthread_join(pro,NULL);
}
else if(a==2)
{
pthread_create(&con,NULL,consumer,NULL);
  
 
pthread_join(con,NULL);
}
else
{
printf("\nwrong choice try again");

printf("\nPress y to enter more");
scanf("%c",&ch);
}
}
while(ch=='y'|ch=='Y');

}
void *producer()
{
pthread_mutex_lock(&m1);
//sleep(1);
printf("\nlock aquired by the producer and now producing");
buff++;
printf("Producer produced item and buffer size is: %d",buff);
printf("\n now releasing lock");
pthread_mutex_unlock(&m1);
}
void *consumer()
{
pthread_mutex_lock(&m1);
//sleep(1);
printf("\nlock aquired by the consumer and now consuming");
buff--;
printf("Consumer consumed an item and remainng buffer size is: %d",buff);
printf("\n now releasing lock");
pthread_mutex_unlock(&m1);
}
