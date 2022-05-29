#include <malloc.h>
#include <stdio.h>
#include "stack.h"
void reverseArray(int arr[], int n);

struct stack
{
    int maxsize;
    int top;
    int *items;
};

struct stack* newStack()
{
    struct stack *pt = (struct stack*) malloc(sizeof(struct stack));

    pt->maxsize = 32768;
    pt->top = -1;
    pt->items = (int*) malloc(sizeof(int) * 32768);

    return pt;
}

int size(struct stack *pt) {
    return pt->top + 1;
}

int isEmpty(struct stack *pt) {
    return size(pt) == 0;
}

int isFull(struct stack *pt) {
    return size(pt) == pt->maxsize;
}
void reverse(struct stack *pt) {
    int n = size(pt);
    reverseArray(pt->items, n);
}

void push(struct stack *pt, int x)
{
    if (isFull(pt))
    {
        printf("Stack Overflow\n");
        exit(1);
    }

    pt->items[++pt->top] = x;
}

int peek(struct stack *pt)
{
    // check for an empty stack
    if (!isEmpty(pt)) {
        return pt->items[pt->top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

int pop(struct stack *pt)
{
    // check for stack underflow
    if (isEmpty(pt))
    {
        printf("Stack Underflow\n");
        exit(1);
    }

    // decrement stack size by 1 and return the popped element
    return pt->items[pt->top--];
}

//helper func
void reverseArray(int arr[], int n)
{
    int aux[n];

    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = aux[i];
    }
}