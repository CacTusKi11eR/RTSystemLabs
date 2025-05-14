#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_t thread_id1;
pthread_t thread_id2;

void * long_thread1 (void *notused)
{
    int n;
    for (n = 0; n < 5; n++) {
        printf("Thread 1 (RR), TID %lu, iteration %d\n", pthread_self(), n);
        sleep(2);
    }
    pthread_exit(NULL);
}

void * long_thread2 (void *notused)
{
    int m;
    for (m = 0; m < 5; m++) {
        printf("Thread 2 (FIFO), TID %lu, iteration %d\n", pthread_self(), m);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(void)
{
    printf("Threads programm, PID %d by Denis Trukhin I914B\n", getpid());

    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;
    int policy1, policy2;
    int ret;

    // Inicializaciya attributov potoka 1 (RR)
    pthread_attr_init(&attr1);
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);

    policy1 = SCHED_RR;
    param1.sched_priority = 3;

    // Sozdanie potoka 1
    if ((ret = pthread_create(&thread_id1, &attr1, long_thread1, NULL)) != 0) {
        perror("pthread_create (RR)");
        return 1;
    }

    // Ustanovka parametrov potoka 1
    if ((ret = pthread_setschedparam(thread_id1, policy1, &param1)) != 0) {
       perror("pthread_setschedparam (RR)");
       return 1;
    }

    // Inicializaciya attributov potoka 2 (FIFO)
    pthread_attr_init(&attr2);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    policy2 = SCHED_FIFO;
    param2.sched_priority = 18;

    // Sozdanie potoka 2
    if ((ret = pthread_create(&thread_id2, &attr2, long_thread2, NULL)) != 0) {
        perror("pthread_create (FIFO)");
        return 1;
    }

    // Ustanovka parametrov potoka 2
    if ((ret = pthread_setschedparam(thread_id2, policy2, &param2)) != 0) {
        perror("pthread_setschedparam (FIFO)");
        return 1;
    }

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    sleep(10);

    printf("End\n");

    return 0;
}