/*
 * Copyright(C) 2024, Charles Theetten, <chalimede@proton.me>
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define BLUE            "\033[1;34m"
#define RED             "\033[91m"
#define EMPTY           "\033[0m"

#define SIZE_BUFFER     4

typedef struct
{
    int     head;
    int     tail;
    int     size;
    void    *data[SIZE_BUFFER];
}           Queue;


void        init(Queue *buffer)
{
    buffer->head = 0;
    buffer->tail = 0;
    buffer->size = 0;
}

void        push(Queue *buffer, void *elem)
{
    if (buffer->size < SIZE_BUFFER)
    {
        buffer->data[buffer->head++] = elem;
        buffer->size++;
    }
    if (buffer->head >= SIZE_BUFFER) buffer->head = 0;
}

void       *pop(Queue *buffer)
{
    void    *elem = NULL;

    if (buffer->size > 0)
    {
        elem = buffer->data[buffer->tail++];
        buffer->data[buffer->tail - 1] = NULL;
        buffer->size--;
    }
    if (buffer->tail >= SIZE_BUFFER) buffer->tail = 0;

    return elem;
}

void        display(Queue *buffer)
{
    for (int i = 0; i < SIZE_BUFFER; i++)
    {
        if (buffer->data[i] == NULL)
        {
            printf("%sX %s", RED, EMPTY);
        } else
        {
            printf("%s ", (char *) buffer->data[i]);
        }
    }
    printf(" %d %d", buffer->tail, buffer->head);
}

int         main(int argc, char *argv[])
{
    Queue   buffer;

    init(&buffer);
    for (int i = 1; i < argc; i++)
    {
        push(&buffer, argv[i]);
    }

    display(&buffer);
    printf("\t <--- %s ADD A B C D E %s\n", BLUE, EMPTY);

    pop(&buffer);
    display(&buffer);
    printf("\t <--- %s DEL 1 ELEMENT %s\n", BLUE, EMPTY);

    push(&buffer, "F");
    push(&buffer, "G");
    display(&buffer);
    printf("\t <--- %s ADD F G %s\n", BLUE, EMPTY);

    pop(&buffer);
    pop(&buffer);
    display(&buffer);
    printf("\t <--- %s DEL 2 ELEMENTS %s\n", BLUE, EMPTY);

    push(&buffer, "H");
    push(&buffer, "I");
    push(&buffer, "J");
    display(&buffer);
    printf("\t <--- %s ADD H I J %s\n", BLUE, EMPTY);

    pop(&buffer);
    pop(&buffer);
    pop(&buffer);
    pop(&buffer);
    display(&buffer);
    printf("\t <--- %s DEL 4 ELEMENTS %s\n", BLUE, EMPTY);

    push(&buffer, "K");
    display(&buffer);
    printf("\t <--- %s ADD K %s\n", BLUE, EMPTY);

    push(&buffer, "L");
    push(&buffer, "M");
    display(&buffer);
    printf("\t <--- %s ADD L M %s\n", BLUE, EMPTY);

    pop(&buffer);
    pop(&buffer);
    display(&buffer);
    printf("\t <--- %s DEL 2 ELEMENTS %s\n", BLUE, EMPTY);

    push(&buffer, "N");
    push(&buffer, "O");
    push(&buffer, "P");
    display(&buffer);
    printf("\t <--- %s ADD N O P %s\n", BLUE, EMPTY);

    return 0;
}
