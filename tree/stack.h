#define MAXITEM 1000
#ifndef NULL
#define NULL 0
#endif
typedef struct stack {
    void *d[MAXITEM];
    int top;
};

struct stack * stack_init();
int stack_push(struct stack *s, void *d);
void* stack_pop(struct stack *s);
int stack_empty(struct stack *s);
