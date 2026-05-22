#include <stdio.h>
#include <string.h>

#define P 4
#define R 3

int alloc[P][R], req[P][R], avail[R];
int vis[P], stack[P];

int cycle(int p) {
    vis[p] = stack[p] = 1;
    for (int r = 0; r < R; r++) {
        if (req[p][r] > avail[r]) {
            for (int p2 = 0; p2 < P; p2++) {
                if (alloc[p2][r] > 0 && (!vis[p2] ? cycle(p2) : stack[p2]))
                    return 1;
            }
        }
    }
    return stack[p] = 0;
}

int detect() {
    memset(vis, 0, sizeof(vis));
    for (int p = 0; p < P; p++) {
        if (!vis[p]) {
            memset(stack, 0, sizeof(stack));
            if (cycle(p)) return 1;
        }
    }
    return 0;
}

void print(char *label, int arr[P][R]) {
    printf("%s:\n", label);
    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < R; j++) printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main() {
    int av[] = {0, 1, 0};
    int al[] = {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0};
    int r[] = {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0};
    
    for (int i = 0; i < R; i++) avail[i] = av[i];
    for (int i = 0; i < P*R; i++) {
        alloc[i/R][i%R] = al[i];
        req[i/R][i%R] = r[i];
    }

    printf("=== Deadlock Detection ===\n");
    printf("Available: ");
    for (int i = 0; i < R; i++) printf("%d ", avail[i]);
    printf("\n\n");
    
    print("Allocated", alloc);
    printf("\n");
    print("Requested", req);

    printf("\n%s\n", detect() ? "*** DEADLOCK DETECTED ***" : "No deadlock");
    return 0;
}
