#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[64];

typedef struct {
    int task_id;
    int priority;
    int deadline;
    String task_name;
} Task;

typedef struct {
    Task tasks[100];
    int last;
} TaskHeap;

int isMoreUrgent(Task a, Task b) {
    if(a.priority > b.priority) return 1;
    if(a.priority < b.priority) return 0;
    if(a.deadline < b.deadline) return 1;
    return 0;
}

void insertTask(TaskHeap *h, Task t) {
    if(h->last == 99) return;
    
    h->tasks[++h->last] = t;
    
    for(int i = h->last; i > 0;) {
        int parent = (i - 1) / 2;
        
        if(isMoreUrgent(h->tasks[i], h->tasks[parent])) {
            Task temp = h->tasks[i];
            h->tasks[i] = h->tasks[parent];
            h->tasks[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

Task peekTop(TaskHeap *h) {
    Task dummy = {-1, 0, 0, ""};
    if(h->last < 0) {
        return dummy;
    }
    return h->tasks[0];
}

Task removeTop(TaskHeap *h) {
    Task dummy = {-1, 0, 0, ""};
    if(h->last < 0) {
        return dummy;
    }
    
    Task removed = h->tasks[0];
    h->tasks[0] = h->tasks[h->last--];
    
    for(int i = 0; 1;) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int mostUrgent = i;
        
        if(left <= h->last && isMoreUrgent(h->tasks[left], h->tasks[mostUrgent])) {
            mostUrgent = left;
        }
        if(right <= h->last && isMoreUrgent(h->tasks[right], h->tasks[mostUrgent])) {
            mostUrgent = right;
        }
        
        if(mostUrgent == i) {
            break;
        } else {
            Task temp = h->tasks[i];
            h->tasks[i] = h->tasks[mostUrgent];
            h->tasks[mostUrgent] = temp;
            i = mostUrgent;
        }
    }
    
    return removed;
}

int countHighPriority(TaskHeap *h, int threshold) {
    int count = 0;
    for(int i = 0; i <= h->last; i++) {
        if(h->tasks[i].priority >= threshold) {
            count++;
        }
    }
    return count;
}

int main(void) {
    TaskHeap h;
    h.last = -1;
    
    Task t1 = {1, 8, 24, "Fix critical bug"};
    Task t2 = {2, 8, 12, "Deploy hotfix"};
    Task t3 = {3, 5, 48, "Write documentation"};
    Task t4 = {4, 9, 6, "Emergency meeting"};
    
    insertTask(&h, t1);
    insertTask(&h, t2);
    insertTask(&h, t3);
    insertTask(&h, t4);
    
    Task top = peekTop(&h);
    printf("Top task: %s (priority: %d, deadline: %d)\n", 
           top.task_name, top.priority, top.deadline);
    
    Task removed1 = removeTop(&h);
    printf("Removed: %s\n", removed1.task_name);
    
    Task removed2 = removeTop(&h);
    printf("Removed: %s\n", removed2.task_name);
    
    int count = countHighPriority(&h, 5);
    printf("High priority tasks (>=5): %d\n", count);
    
    return 0;
}

