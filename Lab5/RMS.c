#include <stdio.h>
#include <math.h>

typedef struct {
    int id, period, burst;
    int remaining, arrival, deadline;
} Task;

int chooseTask(Task t[], int n) {
    int best = -1;

    for (int i = 0; i < n; i++) {
        if (t[i].remaining > 0) {

            // Smaller period = higher priority
            if (best == -1 || t[i].period < t[best].period)
                best = i;
        }
    }

    return best;
}

int main() {

    int n, simTime;

    printf("Rate Monotonic Scheduling\n");

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task t[n];
    double utilization = 0.0;

    // Input
    for (int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask T%d Period: ", i + 1);
        scanf("%d", &t[i].period);

        printf("Task T%d Execution Time: ", i + 1);
        scanf("%d", &t[i].burst);

        t[i].remaining = 0;
        t[i].arrival = 0;
        t[i].deadline = t[i].period;
        utilization += (double)t[i].burst / t[i].period;
    }

    printf("\nEnter Simulation Time: ");
    scanf("%d", &simTime);

    double bound = n * (pow(2.0, 1.0 / n) - 1.0);
    printf("\nCPU utilization = %.3f\n", utilization);
    printf("RMS schedulable = %s\n", utilization <= bound ? "Yes" : "No");

    if (utilization > bound) {
        return 0;
    }

    printf("\nFrom\tTo\tTask\n");
    int current = -1;
    int start = 0;

    for (int time = 0; time < simTime; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {

            if (time == t[i].arrival) {

                t[i].remaining = t[i].burst;
                t[i].arrival += t[i].period;
                t[i].deadline = time + t[i].period;
            }
        }

        // Select highest priority task
        int selected = chooseTask(t, n);

        // Execute
        if (selected != -1)
            t[selected].remaining--;

        // Print only when task changes
        if (selected != current) {

            if (time != 0) {

                if (current == -1)
                    printf("%4d\t%2d\tIDLE\n", start, time);
                else
                    printf("%4d\t%2d\tT%d\n", start, time, current + 1);
            }

            start = time;
            current = selected;
        }
    }

    // Last interval
    if (current == -1)
        printf("%4d\t%2d\tIDLE\n", start, simTime);
    else
        printf("%4d\t%2d\tT%d\n", start, simTime, current + 1);

    return 0;
}
