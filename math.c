#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void arithmatic(struct stack *pt, char cc) {
    int y = pop(pt);
    int x = pop(pt);

    switch (cc) {
        case '+':
            return push(pt, x + y);
        case '-':
            return push(pt, x - y);
        case '*':
            return push(pt, x * y);
        case '/':
            if(x == 0 || y == 0) {
                fprintf(stderr, "Cannot divide by 0!\n");
                exit(1);
            }
            return push(pt, x / y);
        case '%':
            return push(pt, x % y);
    }
}