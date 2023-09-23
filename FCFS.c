#include <stdio.h>
#include <stdlib.h>
struct queue
{
    int size;
    int frontInd;
    int backInd;
    int *arr;
};

void push(struct queue *buffer, int burst_time)
{
    if (buffer->backInd == buffer->size - 1)
        return;

    buffer->arr[++buffer->backInd] = burst_time;
}

int pop(struct queue *buffer)
{
    if (buffer->frontInd == buffer->backInd)
    {
        return -1;
    }
    int popped = buffer->arr[++buffer->frontInd];
    return popped;
}
int main()
{
    int n, burst_time;
    printf("Enter the number of processes:\n");
    scanf("%d", &n);
    struct queue *buffer = (struct queue *)malloc(sizeof(struct queue));
    buffer->arr = (int *)malloc(n * sizeof(int));
    int *wait = (int *)malloc(n * sizeof(int));
    int *turn_around = (int *)malloc(n * sizeof(int));
    buffer->size = n;
    buffer->frontInd = -1;
    buffer->backInd = -1;

    printf("Enter the burst time of each process in accordance of their arrival:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &burst_time);
        (buffer, burst_time);
    }
    int arr_time = 0;
    int wait_time = 0;
    float total_waiting_time = 0.0;
    float total_turnaround_time = 0.0;
    wait[0] = 0;
    turn_around[0] = buffer->arr[0];
    int j = 1;
    while (buffer->frontInd < buffer->backInd - 1)
    {
        int prev = pop(buffer);
        wait_time += prev;
        wait[j] = wait_time;
        turn_around[j] = wait[j] + buffer->arr[j];
        j++;
    }
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += wait[i];
        total_turnaround_time += turn_around[i];
    }
    printf("\nProcess\t  Burst Time\tWaiting Time\tTurnAround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("  %d\t   %d\t\t  %d\t\t  %d\n", i + 1, buffer->arr[i], wait[i], turn_around[i]);
    }

    float avg_wait_time = total_waiting_time / n;
    float avg_turn_time = total_turnaround_time / n;
    printf("\nAverage Waiting Time:%.2f\n", avg_wait_time);
    printf("Average TurnAround Time:%.2f\n", avg_turn_time);

    return 0;
}