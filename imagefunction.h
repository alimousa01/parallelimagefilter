#ifndef _imagefunction_
#define _imagefunction_


#define n 250

typedef struct Task
{
    void* (*taskFunction)(char*, char*, char*);
    char *arg1, *arg2, *arg3;

} Task;

Task taskQueue[n]={0};


typedef struct
{
	double r;
	double g;
	double b;

} pixel_RGB;

void* imagefilter(char *, char *, char *);
void executeTask(Task* );
void submitTask(Task ,void *);
void* startThread(void *);

#endif
