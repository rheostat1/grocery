#include "stack.h"
#include <stdio.h>

int main()
{
    const char* strs[100] = {0};
    strs[0] = "11111";
    strs[1] = "22222";
    strs[2] = "33333";
    struct stack *root = stack_init();
    struct stack *item;
    
    printf("stack inited\n");
    printf("stack top:%d\n", root->top);
    stack_push(root, (void *)strs[0]);
    printf("push %s\n", strs[0]);
    stack_push(root, (void *)strs[1]);
    printf("push %s\n", strs[1]);
    stack_push(root, (void *)strs[2]);
    printf("push %s\n", strs[2]);
    item = stack_pop(root);
    printf("1: %s\n", (char *)item->d);
    item = stack_pop(root);
    printf("2: %s\n", (char *)item->d);
    item = stack_pop(root);
    printf("3: %s\n", (char *)item->d);
    return 0;
}
