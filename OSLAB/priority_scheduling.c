#include <stdio.h>

struct Process {
    int id, burst, priority, arrival, completion, turnaround, waiting, finished;
};

void display(struct Process p[], int n, char* name) {
    printf("\n=== %s ===\n", name);
    printf("PID\tBurst\tPriority\tArrival\tCompletion\tTurnaround\tWaiting\n");
    float avgTat = 0, avgWt = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\t\t%d\t\t%d\n", 
               p[i].id, p[i].burst, p[i].priority, p[i].arrival, 
               p[i].completion, p[i].turnaround, p[i].waiting);
        avgTat += p[i].turnaround;
        avgWt += p[i].waiting;
    }
    printf("Avg Turnaround: %.2f, Avg Waiting: %.2f\n", avgTat/n, avgWt/n);
}

void schedule(struct Process p[], int n, int preempt) {
    struct Process temp[n];
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
        temp[i].finished = 0;
    }
    
    int time = 0, completed = 0, remaining[n];
    for (int i = 0; i < n; i++) remaining[i] = p[i].burst;
    
    while (completed < n) {
        int next = -1, priority = 999;
        for (int i = 0; i < n; i++) {
            if (!temp[i].finished && temp[i].arrival <= time && temp[i].priority < priority) {
                priority = temp[i].priority;
                next = i;
            }
        }
        
        if (next == -1) {
            int minArr = 999;
            for (int i = 0; i < n; i++)
                if (!temp[i].finished && temp[i].arrival < minArr) minArr = temp[i].arrival;
            time = minArr;
            continue;
        }
        
        if (preempt) {
            time++;
            remaining[next]--;
        } else {
            time += remaining[next];
            remaining[next] = 0;
        }
        
        if (remaining[next] == 0) {
            temp[next].completion = time;
            temp[next].turnaround = temp[next].completion - temp[next].arrival;
            temp[next].waiting = temp[next].turnaround - temp[next].burst;
            temp[next].finished = 1;
            completed++;
        }
    }
    
    display(temp, n, preempt ? "PREEMPTIVE PRIORITY" : "NON-PREEMPTIVE PRIORITY");
}

int main() {
    int n;
    printf("Priority Scheduling\nProcesses: ");
    scanf("%d", &n);
    
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].finished = 0;
        printf("\nP%d - Burst: ", i+1);
        scanf("%d", &p[i].burst);
        printf("Priority: ");
        scanf("%d", &p[i].priority);
        printf("Arrival: ");
        scanf("%d", &p[i].arrival);
    }
    
    int choice;
    printf("\n1. Preemptive  2. Non-Preemptive\nChoose: ");
    scanf("%d", &choice);
    
    schedule(p, n, choice == 1);
    return 0;
}
