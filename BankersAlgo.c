#include <stdio.h>

int n, m;

void findSafeSequences(int alloc[n][m], int max[n][m], int avail[m], int finish[n], int need[n][m], int seq[], int idx) {
    if (idx == n) {
        // All processes are included in the sequence, print it
        for (int i = 0; i < n; i++) {
            printf("%d ", seq[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            int flag = 0;
            for (int j = 0; j < m; j++) {
                if (need[i][j] > avail[j]) {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0) {
                finish[i] = 1;
                seq[idx] = i;

                // Update available resources
                int temp_avail[m];
                for (int k = 0; k < m; k++) {
                    temp_avail[k] = avail[k];
                    avail[k] += alloc[i][k];
                }

                // Recur for the next process
                findSafeSequences(alloc, max, avail, finish, need, seq, idx + 1);

                // Backtrack and restore the previous state
                finish[i] = 0;
                for (int k = 0; k < m; k++) {
                    avail[k] = temp_avail[k];
                }
            }
        }
    }
}

int main() {
    n = 5;  // Number of processes
    m = 3;  // Number of resources
    int alloc[5][3] = {{0, 1, 0},
                       {2, 0, 0},
                       {3, 0, 2},
                       {2, 1, 1},
                       {0, 0, 2}};

    int max[5][3] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    int avail[3] = {3, 3, 2};  // Available Resources

    int finish[n], seq[n];
    int need[n][m];

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int found = 0; 

    printf("All possible safe sequences:\n");
    findSafeSequences(alloc, max, avail, finish, need, seq, 0);

    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No safe sequence is possible.\n");
    }

    return 0;
}
