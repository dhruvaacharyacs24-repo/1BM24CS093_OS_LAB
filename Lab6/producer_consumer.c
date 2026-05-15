#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t lock;

void *producer(void *arg)
{
    for (int i = 1; i <= ITEMS; ++i) {
        sem_wait(&empty);
        pthread_mutex_lock(&lock);
        buffer[in] = i;
        printf("Produced %d at position %d\n", buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 1; i <= ITEMS; ++i) {
        sem_wait(&full);
        pthread_mutex_lock(&lock);
        int item = buffer[out];
        printf("Consumed %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&empty);
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t p, c;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);
    
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);
    return 0;
}
