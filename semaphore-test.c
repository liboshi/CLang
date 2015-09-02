#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#endif

#ifdef __APPLE__
        dispatch_semaphore_t sem;
#else
        sem_t sem;
#endif

void threadfunc() {
        while (1) {
#ifdef __APPLE__
                dispatch_semaphore_wait(sem, DISPATCH_TIME_FOREVER);
#else
                sem_wait(&sem);
#endif
                printf("Hello from da thread!\n");
#ifdef __APPLE__
                dispatch_release(sem);
#else
                sem_post(&sem);
#endif
                sleep(1);
        }
}

int main(void) {
        // initialize semaphore, only to be used with threads in this process, set value to 1
#ifdef __APPLE__
        sem = dispatch_semaphore_create(1);
#else
        sem_init(&sem, 0, 1);
#endif
        pthread_t *mythread;

        mythread = (pthread_t *)malloc(sizeof(*mythread));
        // start the thread
        printf("Starting thread, semaphore is unlocked.\n");
        pthread_create(mythread, NULL, (void*)threadfunc, NULL);
        getchar();
#ifdef __APPLE__
        dispatch_semaphore_wait(sem, DISPATCH_TIME_FOREVER);
#else
        sem_wait(&sem);
#endif
        printf("Semaphore locked.\n");
        // do stuff with whatever is shared between threads
        getchar();
        printf("Semaphore unlocked.\n");
#ifdef __APPLE__
        dispatch_release(sem);
#else
        sem_post(&sem);
#endif
        getchar();
        return 0;
}
