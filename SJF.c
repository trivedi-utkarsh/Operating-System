#include <stdio.h>
#include <stdlib.h>

// Define a structure for a process
struct process
{
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};

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
    for (int i = 0; i < n; i++)
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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process *p = (struct process *)malloc(n * sizeof(struct process));
    struct process *temp = (struct process *)malloc(n * sizeof(struct process));

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d:", i + 1);
        scanf("%d", &p[i].arrival_time);
        scanf("%d", &p[i].burst_time);
        p[i].id = i + 1;
    }

    float total_waiting_time = 0.0;
    float total_turnaround_time = 0.0;
    int remaining_process = n;
    int current_time = 0;
    int *completed = (int *)malloc(n * sizeof(int));
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }
    sort(p, n);
    while (remaining_process > 0)
    {
        for (int i = 0; i < n; i++)
        {
            // if the process is completed or it has not arrived at the current then continue
            if (completed[i] == 1 || p[i].arrival_time > current_time)
                continue;

            int execute_time = p[i].burst_time;
            current_time += execute_time;
            completed[i] = 1;
            p[i].turnaround_time = current_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
            remaining_process--;
            temp[idx++] = p[i];
            i = -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    printf("\nProcess\t  Arrival Time\tBurst_time\tWaiting Time\tTurnAround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("  P%d\t   %d\t\t  %d\t\t  %d\t\t  %d\n", temp[i].id, temp[i].arrival_time, temp[i].burst_time, temp[i].waiting_time, temp[i].turnaround_time);
    }

    float avg_wait_time = total_waiting_time / n;
    float avg_turn_time = total_turnaround_time / n;
    printf("\nAverage Waiting Time:%.2f\n", avg_wait_time);
    printf("Average TurnAround Time:%.2f\n", avg_turn_time);

    return 0;
}
