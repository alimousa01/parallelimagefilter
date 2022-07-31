#ifndef _imagefunction_
#define _imagefunction_

#define TASK_QUEUE_NUM 250

typedef struct {
    void *(*taskFunction)(char *, char *, char *);
    char *arg1, *arg2, *arg3;

} Task;

typedef struct {
    double r;
    double g;
    double b;

} pixel_RGB;

typedef struct {
    int* taskCount;
    Task (*taskQueue)[TASK_QUEUE_NUM];
} tasks_info;

void *imagefilter(char *, char *, char *);
void executeTask(Task *);
void submitTask(Task, void *, Task (*taskQueue)[TASK_QUEUE_NUM]);
void *startThread(void *);


#endif
