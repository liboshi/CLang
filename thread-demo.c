// C Threading demo

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4

void *print_hello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Hello world! This is thread #%ld\n", tid);
    pthread_exit(NULL);
}

void *busy_work(void *t)
{
    int i;
    long tid;
    double result = 0.0;
    tid = (long)t;
    printf("Thread %ld starting...\n", tid);
    for (i = 0; i < 10000000; i++)
    {
        result = result + sin(i) * tan(i);
    }
    printf("Thread %ld done. | Result = %e\n", tid, result);
    pthread_exit((void *) t);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], &attr, busy_work, (void *)t);
        if (rc)
        {
            printf("Error; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        printf("Main: Completed join with thread %ld having a status of %ld\n", t, (long)status);
    }
    /*
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("In main: creating thread #%ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
        if (rc)
        {
            printf("Error; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    */
    printf("Main: program finished.... exiting.\n");
    pthread_exit(NULL);
}
