#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 100
// system process
struct Sys_process{
    int priority;
};

// user process 
struct User_process{
    int priority;
};

// queue struct for system and user process
struct Queue{
    int queuePriority;
    int queue[QUEUE_SIZE];
};

int main(void){
    //create priority 1 queue
    struct Queue queue1 = {1};
    //create priority 2 queue
    struct Queue queue2 = {2};
    //create priority 3 queue
    struct Queue queue3 = {3};

    //create system process
    struct Sys_process sys_process = {1};




    return 0;
}