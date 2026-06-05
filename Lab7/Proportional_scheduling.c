#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, t = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], tk[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Enter Tickets for P%d: ", i + 1);
        scanf("%d", &tk[i]);

        rt[i] = bt[i];
        t += tk[i];
    }

    srand(time(0));

    printf("\nProcess Execution Order:\n");

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;
                break;
            }
        }

        if (done)
            break;

        int r = rand() % t;
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += tk[i];

            if (r < sum && rt[i] > 0) {
                printf("P%d\n", i + 1);
                rt[i]--;
                break;
            }
        }
    }

    return 0;
}
