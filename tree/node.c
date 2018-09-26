
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#if 0
#define dbg(...) printf(__VA_ARGS__)
#else 
#define dbg(...) 
#endif
typedef struct node{
    int data;
    struct node *l;
    struct node *r;
    struct node *p;
} _node;

int free_tree(struct node *n) {
    if (n != NULL) {
        if (n == n->p->l) {
            n->p->l = NULL;
        } else {
            n->p->r = NULL;
        }
        free_tree(n->l);
        free_tree(n->r);
        free(n);
    }
    return 0;
}

struct node *root = NULL;
int input_tree_from_file() {
    struct node *nodes[10240] = {0};
    char buf[1024] = {0};
    FILE *fp = fopen("t.gen", "r");
    int n = 0;
    int nth = 0;
    int i=0;

    memset(nodes, 0, sizeof(nodes));
    if (fp == NULL) {
        return -1;
    }
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        char *sep = " ";
        char *word;
        char *brk;
        n = strlen(buf);
        dbg("%s", buf);
        if (buf[n-1] == '\n') 
            buf[n-1] = 0;
        dbg("%s\n", buf);
        for (word=strtok_r(buf, sep, &brk); word; word=strtok_r(NULL, sep, &brk)) {
            dbg("word:%s\n", word?word:"NULL");
            struct node *now = NULL;
            int v = 0;
            if (strcmp(word, "N") != 0) {
                v = atoi(word);
                now = (struct node *)malloc(sizeof(struct node));
                now->l = NULL;
                now->r = NULL;
                now->data = v;
                now->p = NULL;
            }
#if 0
            if (nth == 7) {
                int ii;
                for (ii=0; ii<7; ii++) 
                    printf("%p\n", nodes[ii]);
            }
#endif
            if ((nth != 0) && (nodes[(nth-1)/2] != NULL)) { //not first node, parent node not null
                if ((nth%2) == 1) {
                    nodes[(nth-1)/2]->l = now;
                } else {
                    nodes[(nth-1)/2]->r = now;
                } 
            }
            if (now != NULL)
                now->p = nodes[(nth-1)/2];
            nodes[nth] = now;
            nth++;
        }
        dbg("______\n");
    }
    
    if (root != NULL) {
        free_tree(root);
        root = NULL;
    }
    
    root = nodes[0];
#if 1
    printf("natual seq:\n");
    for (i=0; i<100; i++) {
        struct node *p = nodes[i];
        if (p != NULL) 
            printf("%d\t", p->data);
    }
#endif
    return 0;
}

int pre_travel(struct node *r) 
{
    if (r != NULL) {
        printf("%d\t", r->data);
        pre_travel(r->l);
        pre_travel(r->r);
    }
    return 0;
}
int post_travel(struct node *r) 
{
    if (r != NULL) {
        post_travel(r->l);
        post_travel(r->r);
        printf("%d\t", r->data);
    }
    return 0;
}
int mid_travel(struct node *r) 
{
    if (r != NULL) {
        mid_travel(r->l);
        printf("%d\t", r->data);
        mid_travel(r->r);
    }
    return 0;
}

int pre_travel_s(struct node *r)
{
    struct node *n = r;
    struct stack *s = stack_init();
    struct node *tmp = NULL;

    while (n != NULL || !stack_empty(s)) {
        while (n != NULL) {
            printf("%d\t", n->data);
            stack_push(s, n);
            n = n->l;
        }

        tmp = stack_pop(s);
        if (tmp != NULL) {
            if (tmp->r != NULL) 
                n = tmp->r;
        }
    }

    return 0;
}


int mid_travel_s(struct node *r)
{
    struct node *n = r;
    struct stack *s = stack_init();
    struct node *tmp = NULL;

    while (n != NULL || !stack_empty(s)) {
        while (n != NULL) {
            stack_push(s, n);
            n = n->l;
        }

        tmp = stack_pop(s);
        if (tmp != NULL) {
            printf("%d\t", tmp->data);
            if (tmp->r != NULL) 
                n = tmp->r;
        }
    }

    return 0;
}

int post_travel_s(struct node *r)
{
    struct node *n = r;
    struct stack *s = stack_init();
    struct node *tmp = NULL;
    struct node *last_pop = NULL;

    while (n != NULL || !stack_empty(s)) {
        while (n != NULL) {
            stack_push(s, n);
            n = n->l;
        }

        tmp = stack_pop(s);
        if (tmp != NULL) {
            if (tmp->r != NULL) {
                if (tmp->r != last_pop) {
                    n = tmp->r;
                    stack_push(s, tmp);
                } else {
                    printf("%d\t", tmp->data);
                }
            } else 
                printf("%d\t", tmp->data);
            last_pop = tmp;
        }
    }

    return 0;
}

int layer_travel_q(struct node *r)
{
    struct queue *q = queue_init();
    struct queue_node *n = new_queue_node(r);
    enqueue(q, n);
    int cur_layer_num = 1;
    while (!is_queue_empty(q)) {
        cur_layer_num = q->sz;
        while(cur_layer_num--) {
            struct queue_node *tmp = dequeue(q);
            struct node *tmp_tree_node = (struct node *)(tmp->data);
            printf("%d\t", tmp_tree_node->data);
            if (tmp_tree_node->l != NULL) {
                struct queue_node *qn = new_queue_node(tmp_tree_node->l);
                enqueue(q, qn);
            }
            if (tmp_tree_node->r != NULL) {
                struct queue_node *qn = new_queue_node(tmp_tree_node->r);
                enqueue(q, qn);
            } 
        }
        printf("\n");
    }
    return 0;
}


struct node * insert_to_tree(struct node *root, int val)
{
    struct node *n = NULL;
    n = (struct node *)malloc(sizeof(struct node));
    n->l = NULL;
    n->r = NULL;
    n->p = NULL;
    n->data = val;
 
    if (root == NULL) 
        return n;
    else {
        struct node *p = root;
        struct node *pre = NULL;
        int left = 0;
        while (p != NULL) {
            if (val < p->data) {
                pre = p;
                p = p->l;
                left = 1;
            } else {
                pre = p;
                p = p->r;
                left = 0;
            }
        }
        if (pre != NULL) {
            if (left) {
                pre->l = n;
            } else {
                pre->r = n;
            }
            n->p = pre;
        }
        return root;
    }
}

struct node * scan_create_tree()
{
    struct node * root = NULL;
    char buf[1024];
    int n=0;
    char *sep = " ";
    char *word;
    char *brk;
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if (buf[0] == 'Q')
            break;
        n = strlen(buf);
        dbg("%s", buf);
        if (buf[n-1] == '\n') 
            buf[n-1] = 0;
        dbg("%s\n", buf);
        for (word=strtok_r(buf, sep, &brk); word; word=strtok_r(NULL, sep, &brk)) {
            dbg("word:%s\n", word?word:"NULL");
            struct node *now = NULL;
            int v = 0;
            v = atoi(word);
            root = insert_to_tree(root, v);
        }
#if 1
        printf("----------------------\n");
        layer_travel_q(root);
        printf("----------------------\n");
#endif
    }
    return root;
}


int main()
{
    int i=0;
    input_tree_from_file();
    dbg("xxxx");

    printf("root:%d\n", root->data);
    printf("\npre order:\n");
    pre_travel(root);

    printf("\nmid order:\n");
    mid_travel(root);

    printf("\npost order:\n");
    post_travel(root);

    printf("\npre_s order:\n");
    pre_travel_s(root);

    printf("\nmid_s order:\n");
    mid_travel_s(root);

    printf("\npost_s order:\n");
    post_travel_s(root);

    printf("\n");

    printf("--------------------------------------\n");

    printf("Layer to layer travel:\n");
    layer_travel_q(root);
    printf("\n");

    printf("--------------------------------------\n");
    scan_create_tree();
    
    return 0;
}
