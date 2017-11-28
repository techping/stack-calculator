#ifndef _STACK_H
#define _STACK_H

#define ELEMENT_TYPE int
#define NULL 0

struct node;
typedef struct node * ptr2node;
typedef ptr2node stack;

int is_empty(stack s);
void make_empty(stack s);
stack create_stack(void);
void delete_stack(stack s);
void push(ELEMENT_TYPE x, stack s);
void pop(stack s);
ELEMENT_TYPE top(stack s);

struct node {
	ELEMENT_TYPE element;
	ptr2node next;
};

#endif /* _STACK_H */
