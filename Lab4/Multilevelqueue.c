#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int type; // 1 = system, 2 = user
} Process;

void sortByArrival(Process queue[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (queue[i].arrival > queue[j].arrival) {
                Process temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }
}

void runFCFS(Process queue[], int count, int *time) {
    for (int i = 0; i < count; i++) {
        if (*time < queue[i].arrival) {
            *time = queue[i].arrival;
        }
        queue[i].completion = *time + queue[i].burst;
        queue[i].turnaround = queue[i].completion - queue[i].arrival;
        queue[i].waiting = *time - queue[i].arrival;
        *time += queue[i].burst;
    }
}

int main() {
    Process systemQueue[MAX_PROCESSES];
    Process userQueue[MAX_PROCESSES];
    int systemCount = 0;
    int userCount = 0;
    int n;
    int currentTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Process p;
        p.pid = i + 1;
        printf("\nProcess %d:\n", p.pid);
        printf("Arrival time: ");
        scanf("%d", &p.arrival);
        printf("Burst time: ");
        scanf("%d", &p.burst);
        printf("Type (1 = system, 2 = user): ");
        scanf("%d", &p.type);

        if (p.type == 1) {
            systemQueue[systemCount++] = p;
        } else {
            p.type = 2;
            userQueue[userCount++] = p;
        }
    }

    sortByArrival(systemQueue, systemCount);
    sortByArrival(userQueue, userCount);

    runFCFS(systemQueue, systemCount, &currentTime);
    runFCFS(userQueue, userCount, &currentTime);

    printf("\nMulti-Level Queue Scheduling Results:\n");
    printf("PID\tType\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    double totalWaiting = 0;
    double totalTurnaround = 0;

    for (int i = 0; i < systemCount; i++) {
        printf("%d\tSystem\t%d\t%d\t%d\t%d\t%d\n",
               systemQueue[i].pid,
               systemQueue[i].arrival,
               systemQueue[i].burst,
               systemQueue[i].completion,
               systemQueue[i].turnaround,
               systemQueue[i].waiting);
        totalWaiting += systemQueue[i].waiting;
        totalTurnaround += systemQueue[i].turnaround;
    }

    for (int i = 0; i < userCount; i++) {
        printf("%d\tUser\t%d\t%d\t%d\t%d\t%d\n",
               userQueue[i].pid,
               userQueue[i].arrival,
               userQueue[i].burst,
               userQueue[i].completion,
               userQueue[i].turnaround,
               userQueue[i].waiting);
        totalWaiting += userQueue[i].waiting;
        totalTurnaround += userQueue[i].turnaround;
    }

    printf("\nAverage waiting time: %.2f\n", totalWaiting / n);
    printf("Average turnaround time: %.2f\n", totalTurnaround / n);

    return 0;
}
