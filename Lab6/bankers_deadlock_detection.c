#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

bool isSafe(int avail[R], int max[P][R], int alloc[P][R])
{
    bool done[P] = {0};
    int work[R];
    for (int j = 0; j < R; ++j)
        work[j] = avail[j];

    for (int doneCount = 0; doneCount < P;) {
        bool progress = false;
        for (int i = 0; i < P; ++i) if (!done[i]) {
            int j;
            for (j = 0; j < R; ++j)
                if (max[i][j] - alloc[i][j] > work[j])
                    break;
            if (j == R) {
                for (int k = 0; k < R; ++k)
                    work[k] += alloc[i][k];
                done[i] = true;
                progress = true;
                doneCount++;
            }
        }
        if (!progress) return false;
    }
    return true;
}

int main(void)
{
    int avail[R] = {3, 3, 2};
    int alloc[P][R] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[P][R]   = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};

    puts(isSafe(avail, max, alloc)
         ? "Safe state 1: no deadlock"
         : "Unsafe state 1: deadlock possible");

    int avail2[R] = {0, 0, 0};
    puts(isSafe(avail2, max, alloc)
         ? "Safe state 2: no deadlock"
         : "Unsafe state 2: deadlock possible");
    return 0;
}
 
