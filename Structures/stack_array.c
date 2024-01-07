/*
 * Copyright(C) 2024, Charles Theetten, <chalimede@proton.me>
 *
 */

#include <stdbool.h>
#include <stdio.h>

#define SIZE 128

typedef struct
{
    int     size;
    void    *data[SIZE];
}           Stack;


void        init(Stack *stack)
{
    stack->size = 0;
}

bool        is_empty(Stack *stack)
{
    return stack->size == 0;
}

void        push(Stack *stack, void *elem)
{
    stack->data[stack->size++] = elem;
}

void        *pop(Stack *stack)
{
    stack->size--;
    return stack->data[stack->size];
}

void        display(Stack *stack)
{
    for (int i = stack->size - 1; i >= 0; i--)
    {
        printf("%s\n", (char *) stack->data[i]);
    }
    puts("\n ---------- \n");
}

int         main(int argc, char *argv[])
{
    Stack   stack;

    init(&stack);
    for (int i = 1; i < argc; i++)
    {
        push(&stack, argv[i]);
    }
    display(&stack);
    pop(&stack);
    pop(&stack);
    display(&stack);
    push(&stack, "D");
    push(&stack, "E");
    push(&stack, "F");
    display(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    display(&stack);
    pop(&stack);
    display(&stack);
    return 0;
}