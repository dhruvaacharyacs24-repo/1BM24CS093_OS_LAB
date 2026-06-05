#include <stdio.h>

void firstFit(int block[], int b, int process[], int p) {
    int temp[b];
    for (int i = 0; i < b; i++) temp[i] = block[i];

    printf("\nFirst Fit:\n");
    for (int i = 0; i < p; i++) {
        int allocated = 0;
        for (int j = 0; j < b; j++) {
            if (temp[j] >= process[i]) {
                printf("P%d -> B%d\n", i + 1, j + 1);
                temp[j] -= process[i];
                allocated = 1;
                break;
            }
        }
        if (!allocated)
            printf("P%d -> Not Allocated\n", i + 1);
    }
}

void bestFit(int block[], int b, int process[], int p) {
    int temp[b];
    for (int i = 0; i < b; i++) temp[i] = block[i];

    printf("\nBest Fit:\n");
    for (int i = 0; i < p; i++) {
        int best = -1;
        for (int j = 0; j < b; j++) {
            if (temp[j] >= process[i]) {
                if (best == -1 || temp[j] < temp[best])
                    best = j;
            }
        }

        if (best != -1) {   
            printf("P%d -> B%d\n", i + 1, best + 1);
            temp[best] -= process[i];
        } else {
            printf("P%d -> Not Allocated\n", i + 1);
        }
    }
}

void worstFit(int block[], int b, int process[], int p) {
    int temp[b];
    for (int i = 0; i < b; i++) temp[i] = block[i];

    printf("\nWorst Fit:\n");
    for (int i = 0; i < p; i++) {
        int worst = -1;
        for (int j = 0; j < b; j++) {
            if (temp[j] >= process[i]) {
                if (worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            printf("P%d -> B%d\n", i + 1, worst + 1);
            temp[worst] -= process[i];
        } else {
            printf("P%d -> Not Allocated\n", i + 1);
        }
    }
}

int main() {
    int b, p;

    printf("Enter number of blocks: ");
    scanf("%d", &b);

    int block[b];
    for (int i = 0; i < b; i++) {
        printf("Enter block size %d: ", i + 1);
        scanf("%d", &block[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &p);

    int process[p];
    for (int i = 0; i < p; i++) {
        printf("Enter process size %d: ", i + 1);
        scanf("%d", &process[i]);
    }

    firstFit(block, b, process, p);
    bestFit(block, b, process, p);
    worstFit(block, b, process, p);

    return 0;
}
