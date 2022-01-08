#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

const int MAX_QUEUE_LENGTH = 3;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t full;
sem_t empty;
queue<int> product_queue;

void* producer1_func(void* args) {
    for (int i = 0; i < MAX_QUEUE_LENGTH << 2; ++i) {
        sem_wait(&empty);

        double preparing_time = (0.1) + rand() / double(RAND_MAX / (1 - 0.1));
        sleep(preparing_time);

        pthread_mutex_lock(&mutex);
        int s = 1000, e = 1999;
        int rand_num = (rand() % (e - s + 1)) + s;
        printf("Produce: %d\n", rand_num);
        product_queue.push(rand_num);
        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }
    return (void*)1;
}

void* producer2_func(void* args) {
    for (int i = 0; i < MAX_QUEUE_LENGTH << 2; ++i) {
        sem_wait(&empty);

        double preparing_time = (0.1) + rand() / double(RAND_MAX / (1 - 0.1));
        sleep(preparing_time);

        pthread_mutex_lock(&mutex);
        int s = 2000, e = 2999;
        int rand_num = (rand() % (e - s + 1)) + s;
        printf("Produce: %d\n", rand_num);
        product_queue.push(rand_num);
        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }
    return (void*)1;
}

void* comsumer_func(void* args) {
    for (int i = 0; i < MAX_QUEUE_LENGTH << 1; ++i) {
        sem_wait(&full);

        double preparing_time = (0.1) + rand() / double(RAND_MAX / (1 - 0.1));
        sleep(preparing_time);

        pthread_mutex_lock(&mutex);
        int get_num = product_queue.front();
        product_queue.pop();
        printf("Consume: %d\n", get_num, product_queue.size());
        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
    }
    return (void*)2;
}

int main() {
    srand(time(0));
    pthread_t producer_threads[2];
    pthread_t consumer_threads[4];

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX_QUEUE_LENGTH);

    pthread_create(&(producer_threads[0]), NULL, producer1_func, NULL);
    pthread_create(&(producer_threads[1]), NULL, producer2_func, NULL);

    pthread_create(&(consumer_threads[0]), NULL, comsumer_func, NULL);
    pthread_create(&(consumer_threads[1]), NULL, comsumer_func, NULL);
    pthread_create(&(consumer_threads[2]), NULL, comsumer_func, NULL);
    pthread_create(&(consumer_threads[3]), NULL, comsumer_func, NULL);

    pthread_join(producer_threads[0], nullptr);
    pthread_join(producer_threads[1], nullptr);

    pthread_join(consumer_threads[0], nullptr);
    pthread_join(consumer_threads[1], nullptr);
    pthread_join(consumer_threads[2], nullptr);
    pthread_join(consumer_threads[3], nullptr);
    return 0;
}