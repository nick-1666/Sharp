#ifndef SHARP_STACK_H
#define SHARP_STACK_H

struct stack;
struct stack* newStack();

int size(struct stack *pt);
int isEmpty(struct stack *pt);
int isFull(struct stack *pt);

void reverse(struct stack *pt);
void push(struct stack *pt, int x);
int peek(struct stack *pt);
int pop(struct stack *pt);

#endif