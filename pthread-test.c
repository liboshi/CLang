#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

typedef struct _thread_data {
        int thread_id;
        int sum;
        char *message;
} thread_data;

thread_data thread_data_array[NUM_THREADS];

void*
printHello(void *threadid) {
        long tid;
        tid = (long)threadid;
        printf("Hello world, I am thread - #%ld\n", tid);
        pthread_exit(NULL);
}

void*
sayHello(void *threadargs) {
        thread_data *my_data;
        my_data = (thread_data *)threadargs;
        int taskid = my_data->thread_id;
        int sum = my_data->thread_id;
        char *hello_msg = my_data->message;
        printf("Message: %s, I am thread %d, total number is %d\n",
               hello_msg, taskid, sum);
        pthread_exit(NULL);
}

int
main(int argc, char *argv[]) {
        pthread_t threads[NUM_THREADS];
        char *messages[NUM_THREADS] = {
                                       "Hello 1",
                                       "Hello 2",
                                       "Hello 3",
                                       "Hello 4",
                                       "Hello 5"};
        int rc;
        int sum = 0;
        long t;
        long *taskids[NUM_THREADS];
        for(t = 0; t < NUM_THREADS; t++) {
                taskids[t] = (long *)malloc(sizeof(long));
                *taskids[t] = t;
                sum += t;
                thread_data_array[t].thread_id = t;
                thread_data_array[t].sum = sum;
                thread_data_array[t].message = messages[t];
                printf("In main: creating thread %ld\n", t);
                /* How to pass argument to a thread */
                /* rc = pthread_create(&threads[t], NULL, printHello, (void *)taskids[t]); */
                /* How to pass arguments to a thread via sturcture */
                rc = pthread_create(&threads[t], NULL, sayHello, (void *)&thread_data_array[t]);
                if(rc) {
                        printf("ERROR: return code from pthread_create() is %d\n", rc);
                        exit(-1);
                }
        }
        pthread_exit(NULL);
}
