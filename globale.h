#ifndef _globale_
#define _globale_
#include <pthread.h>

#define n 250

typedef struct Task
{
    void* (*taskFunction)(char*, char*, char*);
    char *arg1, *arg2, *arg3;

} Task;


Task taskQueue[n]={0};
int taskCount = 0;
pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;
pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

typedef struct 
{
	double r;
	double g;
	double b;

} pixel_RGB;

#endif
