#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

int shared = 1;
int s = 1;

void wait(int *s) {
    while (*s == 0) {}
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void *fun1() {
    int x;
    wait(&s);
    x = shared;
    printf("Thread 1 reads the value of shared variable as %d\n", x);
    x++;
    printf("Local updation by thread 1: %d\n", x);
    sleep(1);
    shared = x;
    printf("Value of shared variable updated by thread 1 is %d\n", shared);
    signal(&s);
}

void *fun2() {
    int y;
    wait(&s);
    y = shared;
    printf("Thread 2 reads the value of shared variable as %d\n", y);
    y--;
    printf("Local updation by thread 2: %d\n", y);
    sleep(1);
    shared = y;
    printf("Value of shared variable updated by thread 2 is %d\n", shared);
    signal(&s);
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final value of shared variable is %d\n", shared);

    return 0;
}
