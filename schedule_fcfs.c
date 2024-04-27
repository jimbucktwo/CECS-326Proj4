/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

//Your code and design here

//start of the linked list
struct node *head = NULL;

void add(char *name, int priority, int burst) {
    //dynamically allocate memory for the size of the task inserted
    Task *process = malloc(sizeof(Task));

    //assign task to appropriate values
    process->name = name;
    process->priority = priority;
    process->burst = burst;
    
    //insert into list
    insert(&head, process);
}

void schedule() {
    //reverse the list so that the first one in will be in index 0
    struct node *next = NULL;
    struct node *curr = head;
    struct node *prev = NULL;
    while  (curr != NULL) {

        //stores the next node
        next = curr->next;

        //reverse the pointer
        curr->next = prev;

        //update pointers to the next position
        prev = curr;
        curr = next;
    }

    curr = prev;

    //execute the processes in fcfs order
    while (curr != NULL) {
        run(curr->task, curr->task->burst);
        curr = curr->next;
    }
}
