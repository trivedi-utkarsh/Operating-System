#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

int shared=1;
sem_t s;

void *fun1(){
    int x;
    sem_wait(&s);
    x=shared;
    printf("Thread 1 reads the value of shared variable as %d\n",x);
    x++;
    printf("Local updation by thread1: %d\n",x);
    sleep(1);
    shared=x;
    printf("Value of shared variable updated by thread 1 is %d\n",shared);
    sem_post(&s);
}
void *fun2(){
    int y;
    sem_wait(&s);
    y=shared;
    printf("Thread 2 reads the value of shared variable as %d\n",y);
    y--;
    printf("Local updation by thread2: %d\n",y);
    sleep(1);
    shared=y;
    printf("Value of shared variable updated by thread 2 is %d\n",shared);
    sem_post(&s);
}

int main(){
    sem_init(&s,0,1);
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,fun1,NULL);
    pthread_create(&thread2,NULL,fun2,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("Final value of shared variable is %d",shared);
}