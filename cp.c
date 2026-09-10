#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

struct Task {
    int id;
    char name[50];
};

struct Queue {
    struct Task items[MAX];
    int front, rear;
};

void initialize(struct Queue* q){
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct Queue* q){
    return q->front == -1;
}

int isFull(struct Queue* q){
    return q->rear == MAX - 1;
}

void enqueue(struct Queue* q, struct Task task){
    if(isFull(q)){
        printf("Queue is full. Cannot add task %d.\n", task.id);
        return;
    }
    if(isEmpty(q)) q->front = 0;
    q->items[++q->rear] = task;
    printf("Task arrived  ->  Doc ID: %d  |  Name: %s\n", task.id, task.name);
}

struct Task dequeue(struct Queue* q){
    struct Task task = q->items[q->front];
    if(q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return task;
}

void print_job(struct Task task){
    printf("Printing      ->  Doc ID: %d  |  Name: %s\n", task.id, task.name);
}

int main(){
    srand(time(NULL));

    char docs[][50] = {"Report", "Resume", "Invoice", "Essay", "Thesis",
                       "Slides", "Contract", "Notes", "Memo", "Agenda"};
    int n;
    printf("Enter number of print tasks: ");
    scanf("%d", &n);

    struct Queue q;
    initialize(&q);

    printf("\n--- Tasks arriving ---\n");
    for(int i=1;i<=n;i++){
        struct Task t;
        t.id = rand() % 900 + 100;
        strcpy(t.name, docs[rand() % 10]);
        enqueue(&q, t);
    }

    printf("\n--- Processing in FIFO order ---\n");
    while(!isEmpty(&q)){
        print_job(dequeue(&q));
    }

    printf("\nAll tasks printed.\n");
    return 0;
}