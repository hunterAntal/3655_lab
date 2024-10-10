#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 100
// system process
struct Sys_process{
    int priority;
    float burstTime;
    char processName[50];
};

// user process 
struct User_process{
    int priority;
    float burstTime;
    char processName[50];
};

// queue struct for system process
struct QueueSysProcess{
    int queuePriority;
    int count; 
    struct Sys_process queue[QUEUE_SIZE];
};

struct QueueUserProcess{
    int queuePriority;
    int count; 
    struct User_process queue[QUEUE_SIZE];
};

// add system process to queue
void addSysToQueue(struct QueueSysProcess *queue, struct Sys_process process){
    if(queue->count < QUEUE_SIZE){
        queue->queue[queue->count] = process;
        queue->count++;
    }else{
        printf("Queue %d is full\n", queue->queuePriority);
    }
}
// add user process to queue
void addUserToQueue(struct QueueUserProcess *queue, struct User_process process){
    if(queue->count < QUEUE_SIZE){
        queue->queue[queue->count] = process;
        queue->count++;
    }else{
        printf("Queue %d is full\n", queue->queuePriority);
    }
}

// queue1 scheduler using first in first out (FIFO)
void queue1Scheduler(struct QueueSysProcess *queue1){
    // if queue is empty print message
    if(queue1->count == 0){
        printf("Queue %d is empty\n", queue1->queuePriority);
        return;
    }
    // sort first in first out
    for (int i = 0; i < queue1->count; i++){
        printf("Process %s is running\n", queue1->queue[0].processName);
        // remove process from queue
        for (int j = 0; j < queue1->count; j++){
            queue1->queue[j] = queue1->queue[j+1];
        }
    }
    // now that all processes have been run, reset the count to 0
    queue1->count = 0;
}

// queue2 scheduler using longest job first (LJF)
void queue2Scheduler(struct QueueUserProcess *queue2){
    // temp variable to hold process
    struct User_process temp = queue2->queue[0];

    // if queue is empty print message
    if(queue2->count == 0){
        printf("Queue %d is empty\n", queue2->queuePriority);
        return;
    }
    // sort longest job first
    for (int i = 0; i < queue2->count; i++){
        
        for (int j = 0; j < queue2->count; j++){
            // if current process burst time is less then the one next in line switch them
            if(queue2->queue[j].burstTime < queue2->queue[j+1].burstTime){
                temp = queue2->queue[j];
                queue2->queue[j] = queue2->queue[j+1];
                queue2->queue[j+1] = temp;
            }
        }
    }
    // print sorted process array larget to smallest burst time
    for (int i = 0; i < queue2->count; i++){
        printf("Process %s is running\n", queue2->queue[0].processName);
        // remove process from queue
        for (int j = 0; j < queue2->count; j++){
            queue2->queue[j] = queue2->queue[j+1];
        }
    }
    // now that all processes have been run, reset the count to 0
    queue2->count = 0;
}

// queue3 scheduler using shortest job first (SJF)
void queue3Scheduler(struct QueueUserProcess *queue3){
    // temp variable to hold process
    struct User_process temp = queue3->queue[0];

    // if queue is empty print message
    if(queue3->count == 0){
        printf("Queue %d is empty\n", queue3->queuePriority);
        return;
    }
    // sort shortest job first
    for (int i = 0; i < queue3->count; i++){
        
        for (int j = 0; j < queue3->count; j++){
            // if current process burst time is greater then the one next in line switch them
            if(queue3->queue[j].burstTime > queue3->queue[j+1].burstTime && (j+1) < queue3->count){
                temp = queue3->queue[j];
                queue3->queue[j] = queue3->queue[j+1];
                queue3->queue[j+1] = temp;
            }
        }
    }
    // print sorted process array smallest to largest burst time
    for (int i = 0; i < queue3->count; i++){
        printf("Process %s is running\n", queue3->queue[0].processName);
        // remove process from queue
        for (int j = 0; j < queue3->count; j++){
            queue3->queue[j] = queue3->queue[j+1];
        }
    }
    // now that all processes have been run, reset the count to 0
    queue3->count = 0;
}

// multiQueueScheduler priority 1, 2, 3
void multiQueueScheduler(struct QueueSysProcess *queue1, struct QueueUserProcess *queue2, struct QueueUserProcess *queue3){
    // run queue1 scheduler
    queue1Scheduler(queue1);

    // only run queue2 scheduler if queue1 is empty
    if (queue1->count == 0){
        // run queue2 scheduler
        queue2Scheduler(queue2);
    }

    // only run queue3 scheduler if queue1 and queue2 are empty
    if (queue1->count == 0 && queue2->count == 0){
        // run queue3 scheduler
        queue3Scheduler(queue3);
    }
}


int main(void){
    // create a queue to hold waiting user processes before they get sorted into the priority queues
    struct QueueUserProcess waitingUserQueue;
    // create a queue to hold waiting system processes before they get sorted into the priority queues
    struct QueueSysProcess waitingSysQueue;

    //create priority 1 queue
    struct QueueSysProcess queue1 = {1, 0};
    //create priority 2 queue
    struct QueueUserProcess queue2 = {2, 0};
    //create priority 3 queue
    struct QueueUserProcess queue3 = {3, 0};

    //create system process
    struct Sys_process fileManager = {1, 1.0, "File Manager"};
    struct Sys_process memoryManager = {1, 2.0, "Memory Manager"};
    struct Sys_process processManager = {1, 2.5, "Process Manager"};
    struct Sys_process securityManager = {1, 0.5, "Security Manager"};
    struct Sys_process networkManager = {1, 1.25, "Network Manager"};

    // add system processes to waiting queue
    addSysToQueue(&waitingSysQueue, fileManager);
    addSysToQueue(&waitingSysQueue, memoryManager);
    addSysToQueue(&waitingSysQueue, processManager);
    addSysToQueue(&waitingSysQueue, securityManager);
    addSysToQueue(&waitingSysQueue, networkManager);


    //create user process
    struct User_process chrome = {2, 1.5, "Chrome"};
    struct User_process firefox = {2, 1.75, "Firefox"};
    struct User_process edge = {2, 1.25, "Edge"};
    struct User_process opera = {2, 1.0, "Opera"};
    struct User_process brave = {2, 1.0, "Brave"};
    struct User_process word = {3, 1.5, "Word"};
    struct User_process excel = {3, 1.75, "Excel"};
    struct User_process powerpoint = {3, 1.25, "Powerpoint"};
    struct User_process outlook = {3, 1.0, "Outlook"};
    struct User_process onenote = {3, 1.0, "OneNote"};

    // add user processes to waiting queue
    addUserToQueue(&waitingUserQueue, chrome);
    addUserToQueue(&waitingUserQueue, firefox);
    addUserToQueue(&waitingUserQueue, edge);
    addUserToQueue(&waitingUserQueue, opera);
    addUserToQueue(&waitingUserQueue, brave);
    addUserToQueue(&waitingUserQueue, word);
    addUserToQueue(&waitingUserQueue, excel);
    addUserToQueue(&waitingUserQueue, powerpoint);
    addUserToQueue(&waitingUserQueue, outlook);
    addUserToQueue(&waitingUserQueue, onenote);

    // add system processes to queue 1
    for (int i = 0; i < waitingSysQueue.count; i++){
        addSysToQueue(&queue1, waitingSysQueue.queue[i]);
    }

    // add user processes to queue 2
    for (int i = 0; i < waitingUserQueue.count; i++){
        if (waitingUserQueue.queue[i].priority == 2){
            addUserToQueue(&queue2, waitingUserQueue.queue[i]);
        }
    }

    // add user processes to queue 3
    for (int i = 0; i < waitingUserQueue.count; i++){
        if (waitingUserQueue.queue[i].priority == 3){
            addUserToQueue(&queue3, waitingUserQueue.queue[i]);
        }
    }

    // run multiQueueScheduler to run all queues in order of priority 1, 2, 3
    // multiQueueScheduler(&queue1, &queue2, &queue3);

    queue3Scheduler(&queue3);




    return 0;
}