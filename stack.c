#include "stack.h"
#include <malloc.h>

int is_empty(stack s)
{
	return s->next == NULL;
}

void make_empty(stack s)
{
	if (s == NULL)
		return;
	else
		while (!is_empty(s))
			pop(s);
}

stack create_stack(void)
{
	stack s;
	s = malloc(sizeof(struct node));
	if (s == NULL)
		return NULL;
	make_empty(s);
	return s;
}

void delete_stack(stack s)
{
	make_empty(s);
	free(s);
}

void push(ELEMENT_TYPE x, stack s)
{
	ptr2node n = malloc(sizeof(ptr2node));
	if (n == NULL)
		return;
	n->element = x;
	n->next = s->next;
	s->next = n;
}

void pop(stack s)
{
	ptr2node tmp;
	if (is_empty(s))
		return;
	tmp = s->next;
	s->next = s->next->next;
	free(tmp);
	
}

ELEMENT_TYPE top(stack s)
{
	if (!is_empty(s))
		return s->next->element;
	else
		return NULL;
}
