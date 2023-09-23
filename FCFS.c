#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int size;
    int frontInd;
    int backInd;
    int *arr;
};

// Function to push an element into the queue
void push(struct queue *buffer, int burst_time)
{
    if (buffer->backInd == buffer->size - 1)
        return; // Queue is full, cannot push more elements.

    buffer->arr[++buffer->backInd] = burst_time;
}

// Function to pop an element from the queue
int pop(struct queue *buffer)
{
    if (buffer->frontInd == buffer->backInd)
    {
        return -1; // Queue is empty, cannot pop.
    }
    int popped = buffer->arr[++buffer->frontInd];
    return popped;
}

int main()
{
    int n, burst_time;
    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    // Initialize the queue structure
    struct queue *buffer = (struct queue *)malloc(sizeof(struct queue));
    buffer->arr = (int *)malloc(n * sizeof(int));
    int *wait = (int *)malloc(n * sizeof(int));
    int *turn_around = (int *)malloc(n * sizeof(int));
    buffer->size = n;
    buffer->frontInd = -1;
    buffer->backInd = -1;

    printf("Enter the burst time of each process in accordance with their arrival:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &burst_time);
        push(buffer, burst_time);
    }

    int arr_time = 0;
    int wait_time = 0;
    float total_waiting_time = 0.0;
    float total_turnaround_time = 0.0;
    wait[0] = 0;
    turn_around[0] = buffer->arr[0];
    int j = 1;

    // Process elements from the queue
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

    // Print the results
    printf("\nProcess\t  Burst Time\tWaiting Time\tTurnAround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("  %d\t   %d\t\t  %d\t\t  %d\n", i + 1, buffer->arr[i], wait[i], turn_around[i]);
    }

    float avg_wait_time = total_waiting_time / n;
    float avg_turn_time = total_turnaround_time / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wait_time);
    printf("Average TurnAround Time: %.2f\n", avg_turn_time);

    // Clean up allocated memory
    free(buffer->arr);
    free(buffer);
    free(wait);
    free(turn_around);

    return 0;
}
