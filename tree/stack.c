#include "stack.h"
struct stack * stack_init() {
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    memset(s->d, 0, sizeof(s->d));
    s->top = -1;
    return s;
}

int stack_push(struct stack *s, void *d)
{
    if (s->top >= (MAXITEM-1)) {
        return -1;
    }
    s->d[s->top+1] = d;
    s->top++;
    return 0;
}

void* stack_pop(struct stack *s)
{
    void *r = NULL;
    if (s->top < 0) 
        return NULL;

    r = s->d[s->top];
    s->top--;
    return r;
}

int stack_empty(struct stack *s)
{
    if (s->top < 0)
        return 1;
    else 
        return 0;
}
