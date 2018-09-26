#include <stdlib.h>
#include "queue.h"

struct queue *queue_init() 
{
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->sz = 0;
    q->head = NULL;
    return q;
}

int is_queue_empty(struct queue *q) 
{
    return q->sz == 0;
}

struct queue_node * new_queue_node(void* data)
{
    struct queue_node* n = (struct queue_node*)malloc(sizeof(struct queue_node));
    n->data = data;
    n->next = n;
    n->prev = n;
    return n;
}

int enqueue(struct queue *q, struct queue_node *n)
{
   if (q->head == NULL) {
       q->head = n;
       q->sz = 1;
   } else {
       q->head->prev->next = n;
       n->next = q->head;
       n->prev = q->head->prev;
       q->head->prev = n;
       q->sz++;
   }
   return 0;
}

struct queue_node *dequeue(struct queue *q)
{
    struct queue_node *h = q->head;
    if (h->next != h) {
        h->next->prev = h->prev;
        h->prev->next = h->next;
        q->head = h->next;
        q->sz--;
    } else {
        q->head = NULL;
        q->sz = 0;
    }
    return h;
}
