#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

typedef struct node {
    int connfd;
    struct node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Queue;

void init_queue(Queue *q);
void enqueue(Queue *q, int connfd);
int dequeue(Queue *q);

#endif