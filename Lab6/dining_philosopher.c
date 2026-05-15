#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define PHILOSOPHERS 3
#define MEALS 2

sem_t forks[PHILOSOPHERS];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % PHILOSOPHERS;

    for (int i = 0; i < MEALS; ++i) {
        printf("P%d think\n", id);
        sleep(1);

        sem_wait(&room);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        printf("P%d eats meal %d\n", id, i + 1);
        sleep(1);

        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&room);
    }
    printf("P%d done\n", id);
    return NULL;
}
int main(void)
{
    pthread_t threads[PHILOSOPHERS];
    int ids[PHILOSOPHERS];

    sem_init(&room, 0, PHILOSOPHERS - 1);
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < PHILOSOPHERS; ++i) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&room);
    return 0;
}
