#include <stdio.h>
#include <stdlib.h>

// structure to define a process
struct process
{
    int id;
    int burst_time;
    int arrival_time;
    int remaining_time;
};

int main()
{
    int n, time_quantum;
    printf("Enter the time quantum\n");
    scanf("%d", &time_quantum);
    printf("Enter the number of processes:\n");
    scanf("%d", &n);
    struct process *p = (struct process *)malloc(n * sizeof(struct process));
    int *wait = (int *)malloc(n * sizeof(int));
    int *turn_around = (int *)malloc(n * sizeof(int));

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d:", i + 1);
        scanf("%d", &p[i].arrival_time);
        scanf("%d", &p[i].burst_time);
        p[i].id = i + 1;
        p[i].remaining_time = p[i].burst_time;
    }

    float total_waiting_time = 0.0;
    float total_turnaround_time = 0.0;
    int remaining_process = n;
    int current_time = 0;
    int *completed = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }

    while (remaining_process > 0)
    {
        for (int i = 0; i < n; i++)
        {
            //if the process is completed or it has not arrived at the current then continue
            if (completed[i] == 1 || p[i].arrival_time > current_time)
                continue;
         
            int execute_time = (p[i].remaining_time <= time_quantum) ? p[i].remaining_time : time_quantum;
            p[i].remaining_time -= execute_time;

            current_time += execute_time;

            if (p[i].remaining_time <= 0)
            {
                completed[i] = 1;
                turn_around[i] = current_time - p[i].arrival_time;
                remaining_process--;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        wait[i] = turn_around[i] - p[i].burst_time;
        total_waiting_time += wait[i];
        total_turnaround_time += turn_around[i];
    }

    printf("\nProcess\t  Arrival Time\tBurst_time\tWaiting Time\tTurnAround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("  P%d\t   %d\t\t  %d\t\t  %d\t\t  %d\n", p[i].id, p[i].arrival_time, p[i].burst_time, wait[i], turn_around[i]);
    }

    float avg_wait_time = total_waiting_time / n;
    float avg_turn_time = total_turnaround_time / n;
    printf("\nAverage Waiting Time:%.2f\n", avg_wait_time);
    printf("Average TurnAround Time:%.2f\n", avg_turn_time);

    free(p);
    free(wait);
    free(turn_around);
    free(completed);

    return 0;
}
