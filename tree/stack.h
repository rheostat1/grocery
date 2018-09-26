#ifndef __M_STACK_H_
#define __M_STACK_H_

#ifndef MAXSITEM
#define MAXSITEM 1000
#endif

#ifndef NULL
#define NULL 0
#endif

struct stack {
    void *d[MAXSITEM];
    int top;
};

struct stack * stack_init();
int stack_push(struct stack *s, void *data);
void* stack_pop(struct stack *s);
int stack_empty(struct stack *s);


#endif
