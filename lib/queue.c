// queue.c
#include "queue.h"
#include <stdlib.h>


void init_queue(Queue *q){
    q->front = q->rear = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->cond, NULL);
}

void enqueue(Queue *q, int connfd)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->connfd = connfd;
    new_node->next = NULL;

    pthread_mutex_lock(&q->lock);

    if (q->rear == NULL)
    {
        q->front = q->rear = new_node;
    }
    else
    {
        q->rear->next = new_node;
        q->rear = new_node;
    }

    pthread_cond_signal(&q->cond); // Notificar a los hilos que hay una nueva conexión
    pthread_mutex_unlock(&q->lock);
}

int dequeue(Queue *q)
{
    pthread_mutex_lock(&q->lock);

    while (q->front == NULL)
    {
        pthread_cond_wait(&q->cond, &q->lock); // Esperar a que llegue una conexión
    }

    Node *temp = q->front;
    int connfd = temp->connfd;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
    pthread_mutex_unlock(&q->lock);

    return connfd;
}
