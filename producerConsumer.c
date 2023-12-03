#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 5

sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int in=0;
int out=0;
int buffer[BUFFER_SIZE];

void *producer(){
    int item=1;
    for(int i=0;i<MAX_ITEMS;i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        printf("Produced item %d at buffer index %d\n",item,in);
        item++;
        in=(in+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void* consumer(){
for(int i=0;i<MAX_ITEMS;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item=buffer[out];
        printf("Consumer item %d from buffer index %d\n",item,out);
        out=(out+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}
int main()
{
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_t producerThread,consumerThread;
    pthread_create(&producerThread,NULL,producer,NULL);
    pthread_create(&consumerThread,NULL,consumer,NULL);

    pthread_join(producerThread,NULL);
    pthread_join(consumerThread,NULL);
}
