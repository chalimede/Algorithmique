/*
 * Copyright(C) 2024, Charles Theetten, <chalimede@proton.me>
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct      s_stack
{
    void            *data;
    struct s_stack  *next;
}                   Stack;


bool        is_empty(Stack *stack)
{
    return stack == NULL;
}

void        push(Stack **stack, Stack *elem)
{
    elem->next  = *stack;
    *stack      = elem;
}

Stack       *pop(Stack **stack)
{
    Stack   *elem = *stack;

    *stack = elem->next;
    return elem;
}

void        display(Stack *stack)
{
    Stack   *tmp = stack;

    while (tmp != NULL)
    {
        printf("%s\n", (char *) tmp->data);
        tmp = tmp->next;
    }
    puts("\n ---------- \n");
}

int         main(int argc, char *argv[])
{
    Stack   *stack = NULL;

    for (int i = 1; i < argc; i++)
    {
        Stack *elem = calloc(1, sizeof(Stack));
        elem->data = argv[i];
        elem->next = NULL;
        push(&stack, elem);
    }
    display(stack);
    pop(&stack);
    pop(&stack);
    display(stack);
    Stack *e1 = calloc(1, sizeof(Stack));
    e1->data = "E";
    e1->next = NULL;
    push(&stack, e1);
    Stack *e2 = calloc(1, sizeof(Stack));
    e2->data = "F";
    e2->next = NULL;
    push(&stack, e2);
    Stack *e3 = calloc(1, sizeof(Stack));
    e3->data = "G";
    e3->next = NULL;
    push(&stack, e3);
    display(stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    display(stack);
    return 0;
}
