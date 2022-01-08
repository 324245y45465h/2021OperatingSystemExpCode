#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>

//打印 1~1000
void* A(void* args) {
    for (int i = 1; i <= 1000; ++i, sleep(1)) printf("A: %d\n", i);
    return (void*)1;
}

//打印1000~1
void* B(void* args) {
    for (int i = 1000; i > 0; --i, sleep(1)) printf("B: %d\n", i);
    return (void*)1;
}

int main() {
    pthread_t threadA;
    pthread_t threadB;
    pthread_create(&threadA, NULL, A, NULL);
    pthread_create(&threadB, NULL, B, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    return 0;
}