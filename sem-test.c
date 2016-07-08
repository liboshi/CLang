#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>

sem_t g_sema;

void threadfunc()
{
        printf("Hello from threadfunc!\n");
        sleep(3);
        sem_post(&g_sema);
}

void threadfunc1()
{
        printf("Hello from threadfunc1\n");
        sleep(5);
        sem_post(&g_sema);
}

int
main()
{
        pthread_t *mythread;
        // Init semaphore
        if (sem_init(&g_sema, 0, 0) != 0) {
                printf("Semaphore init failed.\n");
        }
        mythread = (pthread_t *)malloc(sizeof(*mythread));
        pthread_create(mythread, NULL, (void*)threadfunc, NULL);
        pthread_create(mythread, NULL, (void*)threadfunc1, NULL);
        sem_wait(&g_sema);
        printf("Semaphore locked just now.\n");
        sem_wait(&g_sema);
        printf("Semaphore locaked again just now.\n");
        return 0;
}

