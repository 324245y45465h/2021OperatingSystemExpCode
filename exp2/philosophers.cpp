#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

const int MAX_CHOPSTICKS = 5;
const int MAX_PHILOSOPHERS = MAX_CHOPSTICKS;
pthread_mutex_t chopsticks[MAX_CHOPSTICKS];

void* takeChopsticks(void* arg) {
    char name = *(char*)arg;
    printf("name %c\n", name);
    int left = name - 'A';
    int right = (left + MAX_CHOPSTICKS - 1) % MAX_CHOPSTICKS;

    while (1) {
        pthread_mutex_lock(&chopsticks[left]);
        printf("%c take left chopstick %d\n", name, left);
        sleep(1);

        // pthread_mutex_lock(&chopsticks[right]);
        // printf("%c take right chopstick %d\n", name, right);

        int ret = pthread_mutex_trylock(&chopsticks[right]);
        if (ret) {
            pthread_mutex_unlock(&chopsticks[left]);
            printf(
                "%c put down left chopstick %d, \
                because the right one is occupied\n",
                name, left);
            continue;
        }

        double time_qukuai = (0.1) + rand() / double(RAND_MAX / (0.5 - 0.1));
        sleep(time_qukuai);

        printf("EATING ... EATING ... EATING ...\n");
        double time_chifan = (0.1) + rand() / double(RAND_MAX / (0.5 - 0.1));
        sleep(time_chifan);

        pthread_mutex_unlock(&chopsticks[left]);
        printf("%c put down left chopstick %d\n", name, left);

        pthread_mutex_unlock(&chopsticks[right]);
        printf("%c put down right chopstick %d\n", name, right);

        double time_fangkuai = (0.1) + rand() / double(RAND_MAX / (0.5 - 0.1));
        sleep(time_fangkuai);

        double time_sikao = (0.1) + rand() / double(RAND_MAX / (0.5 - 0.1));
        sleep(time_fangkuai);
    }
}

int main() {
    pthread_t philosopher_threads[MAX_PHILOSOPHERS];

    for (int i = 0; i < 5; ++i) pthread_mutex_init(&chopsticks[i], nullptr);

    char name[6] = "ABCDE";
    for (int i = 0; i < 5; ++i) {
        pthread_create(&(philosopher_threads[i]), nullptr, takeChopsticks,
                       name + i);
    }

    for (int i = 0; i < 5; ++i) pthread_join(philosopher_threads[i], nullptr);
    return 0;
}