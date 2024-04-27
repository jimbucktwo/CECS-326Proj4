/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"


/*
 * Your code and design here:
 */

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
    struct node *current = head;
    struct node *prev = NULL;
    while  (current != NULL) {

        //stores the next node
        next = current->next;

        //reverse the pointer
        current->next = prev;

        //update pointers to the next position
        prev = current;
        current = next;
    }

    head = prev;
    
    int quantum = 10;
    struct node* temp = head;

    //loops around the linked list until all processes are done
    while (temp != NULL) {
        struct node *curr = temp;
        Task *process = curr->task;

        //if quantum is less then burst time, the process is not finished yet
        if (process->burst > quantum) {
            run(process, quantum);
            process->burst -= quantum;
        } else {
            run(process, process->burst);
            process->burst = 0;
        }

        //if process is done being executed, move onto the next process
        if (process->burst == 0) {
            temp = temp->next;
            head = temp;
            free(process->name);
            free(process);
            free(curr);
        } else { //this means the process has not finished and must loop if all processes are not finished
            temp = temp->next;
            if (temp == NULL) {
                temp = head;
            }
        };
    }
}
