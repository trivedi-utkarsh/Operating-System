#include <stdio.h>
#include <stdlib.h>

// Define a structure for a process
struct process
{
    int id;
    int burst_time;
};

// Define a structure for a queue
struct queue
{
    int size;
    int frontInd;
    int backInd;
    struct process *arr;
};

// Function to push an element into the queue
void push(struct queue *buffer, int burst_time)
{
    if (buffer->backInd == buffer->size - 1)
        return; // Queue is full, cannot push more elements.

    buffer->arr[++buffer->backInd].burst_time = burst_time;
}

// Function to pop an element from the queue
int pop(struct queue *buffer)
{
    if (buffer->frontInd == buffer->backInd)
    {
        return -1; // Queue is empty, cannot pop.
    }
    int popped = buffer->arr[++buffer->frontInd].burst_time;
    return popped;
}

// Function to swap two process elements
void swap(struct process *a, struct process *b)
{
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort an array of processes by burst time
void sort(struct process arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].burst_time > arr[j + 1].burst_time)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main()
{
    int n, burst_time;
    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    // Initialize the queue structure
    struct queue *buffer = (struct queue *)malloc(sizeof(struct queue));
    buffer->arr = (struct process *)malloc(n * sizeof(struct process));
    int *wait = (int *)malloc(n * sizeof(int));
    int *turn_around = (int *)malloc(n * sizeof(int));
    buffer->size = n;
    buffer->frontInd = -1;
    buffer->backInd = -1;

    printf("Enter the burst time of each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d:", i + 1);
        scanf("%d", &burst_time);
        buffer->arr[i].id = i + 1;
        push(buffer, burst_time);
    }

    sort(buffer->arr, n);
    int wait_time = 0;
    float total_waiting_time = 0.0;
    float total_turnaround_time = 0.0;
    wait[0] = 0;
    turn_around[0] = buffer->arr[0].burst_time;
    int j = 1;

    // Process elements from the queue
    while (buffer->frontInd < buffer->backInd - 1)
    {
        int prev = pop(buffer);
        wait_time += prev;
        wait[j] = wait_time;
        turn_around[j] = wait[j] + buffer->arr[j].burst_time;
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
        printf("  P%d\t   %d\t\t  %d\t\t  %d\n", buffer->arr[i].id, buffer->arr[i].burst_time, wait[i], turn_around[i]);
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
