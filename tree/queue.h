#ifndef __QUEUE_M__
#define __QUEUE_M__

typedef struct queue_node {
    void* data;
    struct queue_node *next;
    struct queue_node *prev;
} _queue_node;

typedef struct queue {
    struct queue_node *head;
    int sz;
} _queue;

struct queue *queue_init(); 

int is_queue_empty(struct queue *q); 

struct queue_node * new_queue_node(void* data);

int enqueue(struct queue *q, struct queue_node *n);

struct queue_node *dequeue(struct queue *q);

#endif
