#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

int s;

void wait(int *s) {
    while (*s == 0) {}
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void *thread_function(void* arg){
    int thread_id= *(int *)arg;
    wait(&s);
    printf("Thread %d is in critical section\n",thread_id);
    sleep(1);
    printf("Thread %d is leaving critical section\n",thread_id);
    signal(&s);
}


int main(){
    int n;
    printf("Enter the number of processes to be synchronized: ");
    scanf("%d",&n);
    s=n;
    pthread_t threads[n];
    int thread_id[n];

    for(int i=0;i<n;i++)
    {
        thread_id[i]=i;
        pthread_create(&threads[i],NULL,thread_function,&thread_id[i]);
    }
    
    for(int i=0;i<n;i++)
    {
        pthread_join(threads[i],NULL);
    }
    return 0;
}