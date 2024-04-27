/*
 * Priority scheduling
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
    struct node *curr = head;
    int swapped, i;
    struct node *p1;
    struct node *lp = NULL;
    Task *temp;

    //bubblesort algorithm to sort the processes based on priority
    if (curr == NULL) return;

    do {
        swapped = 0;
        p1 = curr;

        while (p1->next != lp) {
            if (p1->task->priority > p1->next->task->priority) {
                //swaps nodes if priority is greater
                temp = p1->task;
                p1->task = p1->next->task;
                p1->next->task = temp;
                swapped = 1;
            }
            p1 = p1->next;
        }
        lp = p1;
    } while(swapped);

    //traverses the sorted list and executes the processes
    curr = head;
    while (curr != NULL) {
        run(curr->task, curr->task->burst);
        curr = curr->next;
    }
    
}
