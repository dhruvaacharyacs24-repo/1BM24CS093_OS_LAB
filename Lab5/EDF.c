#include <stdio.h>

typedef struct {
    int id;
    int period;
    int burst;
    int remaining;
    int arrival;
    int deadline;
    int relDeadline;
} Task;

int chooseTask(Task t[], int n) {

    int best = -1;

    for (int i = 0; i < n; i++) {

        if (t[i].remaining > 0) {

            if (best == -1 || t[i].deadline < t[best].deadline)
                best = i;
        }
    }

    return best;
}

int main() {

    int n, simTime;

    printf("Earliest Deadline First Scheduling\n");

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task t[n];

    for (int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask T%d Period: ", i + 1);
        scanf("%d", &t[i].period);

        printf("Task T%d Execution Time: ", i + 1);
        scanf("%d", &t[i].burst);

        printf("Task T%d Relative Deadline: ", i + 1);
        scanf("%d", &t[i].relDeadline);

        t[i].remaining = 0;
        t[i].arrival = 0;
        t[i].deadline = t[i].relDeadline;
    }

    printf("\nEnter Simulation Time: ");
    scanf("%d", &simTime);

    printf("\nFrom\tTo\tTask\n");

    int current = -1;
    int start = 0;

    for (int time = 0; time < simTime; time++) {

        for (int i = 0; i < n; i++) {

            if (time == t[i].arrival) {

                t[i].remaining = t[i].burst;
                t[i].arrival += t[i].period;
                t[i].deadline = time + t[i].relDeadline;
            }
        }

        int selected = chooseTask(t, n);

        if (selected != -1)
            t[selected].remaining--;

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

    if (current == -1)
        printf("%4d\t%2d\tIDLE\n", start, simTime);
    else
        printf("%4d\t%2d\tT%d\n", start, simTime, current + 1);

    return 0;
}
