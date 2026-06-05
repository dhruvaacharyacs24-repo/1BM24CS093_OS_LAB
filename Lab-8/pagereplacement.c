#include <stdio.h>
#include <stdlib.h>

int findOptimal(int pages[], int n, int frame[], int fn, int index) {
    int farthest = index, pos = -1;
    for (int i = 0; i < fn; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (pos == -1) ? 0 : pos;
}

int findLRU(int time[], int fn) {
    int min = time[0], pos = 0;
    for (int i = 1; i < fn; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void FIFO(int pages[], int n, int fn) {
    int frame[fn], count = 0, index = 0;
    for (int i = 0; i < fn; i++) frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < fn; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            frame[index] = pages[i];
            index = (index + 1) % fn;
            count++;
        }
        for (int j = 0; j < fn; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Page Faults = %d\n", count);
}

void LRU(int pages[], int n, int fn) {
    int frame[fn], time[fn], count = 0, counter = 0;
    for (int i = 0; i < fn; i++) frame[i] = -1;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < fn; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                time[j] = ++counter;
                break;
            }
        }
        if (!flag) {
            int pos = -1;
            for (int j = 0; j < fn; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) pos = findLRU(time, fn);
            frame[pos] = pages[i];
            time[pos] = ++counter;
            count++;
        }
        for (int j = 0; j < fn; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Page Faults = %d\n", count);
}

void Optimal(int pages[], int n, int fn) {
    int frame[fn], count = 0;
    for (int i = 0; i < fn; i++) frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < fn; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            int pos = -1;
            for (int j = 0; j < fn; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) pos = findOptimal(pages, n, frame, fn, i + 1);
            frame[pos] = pages[i];
            count++;
        }
        for (int j = 0; j < fn; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Page Faults = %d\n", count);
}

int main() {
    int n, fn;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &fn);

    FIFO(pages, n, fn);
    LRU(pages, n, fn);
    Optimal(pages, n, fn);

    return 0;
}
