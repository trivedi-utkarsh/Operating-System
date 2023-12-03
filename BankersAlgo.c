#include <stdio.h>
int main()
{
    int n, m, i, j, k;
    n = 5;                         // Number of processes
    m = 3;                         // Number of resources
    int alloc[5][3] = {{0, 1, 0},  // P0    // Allocation Matrix
                       {2, 0, 0},  // P1
                       {3, 0, 2},  // P2
                       {2, 1, 1},  // P3
                       {0, 0, 2}}; // P4

    int max[5][3] = {{7, 5, 3},  // P0    // MAX Matrix
                     {3, 2, 2},  // P1
                     {9, 0, 2},  // P2
                     {2, 2, 2},  // P3
                     {4, 3, 3}}; // P4

    int avail[3] = {3, 3, 2}; // Available Resources

    int finish[n], seq[n];
    int need[n][m];

    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
        for (int j = 0; j < n; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    int idx = 0;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag=0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    finish[i] = 1;
                    seq[idx++] = i;
                    for (int y = 0; y < m; y++)
                    {
                        avail[y] += alloc[i][y];
                    }
                }
            }
        }
    }

    int flag = 0;
    for (i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        for (int x = 0; x < n; x++)
        {
            printf("%d", seq[x]);
        }
    }
    else
    {
        printf("Safe sequence is not present");
    }
    return 0;
}