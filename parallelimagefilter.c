#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include <pthread.h>
#include <unistd.h>
#include "imagefunction.h"

#define INPUT_SIZE 50
#define THREAD_NUM 4
#define TASK_QUEUE_NUM 250


//////////////////////////////////

int main(int argc, char *argv[]) {
    Task taskQueue[TASK_QUEUE_NUM] = {0};
    pthread_mutex_t mutexQueue;
    pthread_cond_t condQueue;
    int taskCount = 0;
    int op;
    char input1[INPUT_SIZE] = "";
    char input2[INPUT_SIZE] = "";
    char input3[INPUT_SIZE] = "";

    if (argc != 7) {    
        printf("you should pass seven arguments\n");
        printf("\nfor example./a.out -i inputimage.p3.ppm -o outputimage.ppm -k 0,-1,0,-1,5,-1,0,-1,0\n");
        exit(EXIT_FAILURE);
    }

    while ((op = getopt(argc, argv, "i:o:k:")) != -1) {    
        switch (op) {
        case 'i':
            strcpy(input1, optarg);
            break;
        case 'o':
            strcpy(input2, optarg);
            break;
        case 'k':
            strcpy(input3, optarg);
            break;
        default:
            printf("error!!\n");
            break;
        }
    }

    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);
    int i = 0;

    Task t = {
        .taskFunction = &imagefilter,
        .arg1 = input1,
        .arg2 = input2,
        .arg3 = input3
    };
    submitTask(t, &taskCount, &taskQueue);
    
    tasks_info ti;
    ti.taskCount = &taskCount;    
    ti.taskQueue = &taskQueue;            
    
    for (i = 0; i < THREAD_NUM; i++) { // creating the threads
        if (pthread_create(&th[i], NULL, startThread, &ti) != 0) {
            perror("Failed to create the thread");
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) { // destroying the threads     
        if (pthread_join(th[i], NULL) != 0) perror("Failed to join the thread");        
    }

    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);

    return 0;
}


   
