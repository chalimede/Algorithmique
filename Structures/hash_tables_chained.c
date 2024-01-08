/*
 * Copyright(C) 2024, Charles Theetten, <chalimede@proton.me>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B           "\033[1;34m"
#define R           "\033[1;31m"
#define E           "\033[0m"

#define NAME_SIZE   30
#define LINE_SIZE   80
#define NB_ARGS     3
#define NB_RECORDS  100

typedef unsigned int (*hash_f) (const char *, unsigned int);

typedef struct      PA
{
    int             elo;
    char            name[NAME_SIZE];
}                   PA;

typedef struct      PL
{
    int             elo;
    char            name[NAME_SIZE];
    struct PL       *next;
}                   PL;

union               Player
{
    PA              *pa;
    PL              *pl;
};

typedef struct
{
    unsigned int    size;
    PL              **keys;
}                   HashTable;


void            get_data(char *filename, union Player *players, int nb)
{
    FILE        *file   = NULL;
    char        *token  = NULL;

    if ((file = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Error args.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nb; i++)
    {
        char line[LINE_SIZE] = { 0 };
        fgets(line, LINE_SIZE, file);
        token = strtok(line, ",");
        players[i].pl = calloc(1, sizeof(PL));
        strncpy(players[i].pl->name, token, strlen(token));
        token = strtok(NULL, ",");
        players[i].pl->elo = strtol(token, NULL, 10);
        token = NULL;
    }
}

unsigned int    elf_hash(const char* str, unsigned int length)
{
    unsigned int hash   = 0;
    unsigned int x      = 0;

    for (unsigned int i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

void            init(HashTable *ht, unsigned int size)
{
    ht->size = size;
    ht->keys = calloc(size, sizeof(PL *));
}

void            insert(HashTable *ht, PL *player, hash_f hash)
{
    PL          *tmp    = NULL;
    unsigned int code   = hash(player->name, strlen(player->name)) % ht->size;

    tmp = ht->keys[code];
    if (tmp == NULL)
    {
        ht->keys[code] = player;
    } else {
        player->next    = tmp;
        ht->keys[code]  = player;
    }
}

int             search(HashTable *ht, char *key, hash_f hash)
{
    int             elo     = -1;
    unsigned int    code    = hash(key, strlen(key)) % ht->size;
    PL              *player = ht->keys[code];

    while (player != NULL)
    {
        if (strncmp(player->name, key, strlen(key)) == 0)
        {
            elo = player->elo;
        }
        player = player->next;
    }
    return elo;
}

void            display(HashTable *ht, unsigned int size)
{
    PL          *player = NULL;

    for (int i = 0; i < size; i++)
    {
        player = ht->keys[i];
        printf("%s[[%-3d]]%s", R, i, E);
        while (player != NULL)
        {
            printf("%s->", B);
            printf("(%s, %d)%s", player->name, player->elo, E);
            player = player->next;
        }
        putchar('\n');
    }
}

int             main(int argc, char *argv[])
{
    int             size                = strtoul(argv[1], NULL, 10);
    int             nb                  = strtoul(argv[2], NULL, 10);
    union Player    players[NB_RECORDS] = { 0 };
    HashTable       ht_linked           = { 0 };

    get_data(argv[NB_ARGS], players, nb);
    init(&ht_linked, size);
    display(&ht_linked, size);

    for (int i = 0; i < nb; i++)
    {
        insert(&ht_linked, players[i].pl, elf_hash);
    }

    printf("--------------------\n");
    display(&ht_linked, size);
    printf("--------------------\n");

    int elo = search(&ht_linked, "Carlsen", elf_hash);
    printf((elo != 0) ? "%-25s%d\n" : "Player not found", "Player found: Carlsen", elo);
    return 0;
}
