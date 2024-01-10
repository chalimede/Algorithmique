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

typedef struct {
    int             elo;
    char            name[NAME_SIZE];
}                   Player;


unsigned int    elf_hash(const char* str, unsigned int length) {
    unsigned int hash   = 0;
    unsigned int x      = 0;

    for (unsigned int i = 0; i < length; ++str, ++i) {
        hash = (hash << 4) + (*str);
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }

    return hash;
}

void            get_data(char *filename, Player *players, int nb) {
    FILE        *file   = NULL;
    char        *token  = NULL;

    if ((file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error args.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb; i++) {
        char line[LINE_SIZE] = { 0 };
        fgets(line, LINE_SIZE, file);
        token = strtok(line, ",");
        strncpy(players[i].name, token, strlen(token));
        token = strtok(NULL, ",");
        players[i].elo = strtol(token, NULL, 10);
        token = NULL;
    }
}

void            insert(Player *ht, Player *player, unsigned int size, hash_f hash) {
    unsigned int    h1 = hash(player->name, strlen(player->name)) % size;
    unsigned int    h2 = 0;

    if (ht[h1].elo == 0) {
        ht[h1] = *player;
    } else {
        h2 = hash(player->name, strlen(player->name)) % size;
        for (int i = 0; i <= size; i++) {
            unsigned int index = (h1 + i * h2) % size;
            if (ht[index].elo == 0) {
                ht[index] = *player;
                break;
            }
        }
    }
}

int             search(Player *ht, unsigned int size, char *key, hash_f hash) {
    int             elo     = -1;
    unsigned int    h1      = hash(key, strlen(key)) % size;
    unsigned int    h2 = 0;

    if (strncmp(ht[h1].name, key, strlen(key)) == 0) {
        elo = ht[h1].elo;
    } else {
        h2 = hash(key, strlen(key)) % size;
        for (int i = 0; i <= size; i++) {
            unsigned int index = (h1 + i * h2) % size;
            if (strncmp(ht[h1].name, key, strlen(key)) == 0) {
                elo = ht[index].elo;
                break;
            }
        }
    }

    return elo;
}

void            display(Player *ht, unsigned int size) {
    for (int i = 0; i < size; i++) {
        printf("%s[[%-3d]]->%s(%s, %d)%s\n", R, i, B, ht[i].name, ht[i].elo, E);
    }
}

int             main(int argc, char *argv[]) {
    int         size                = strtoul(argv[1], NULL, 10);
    int         nb                  = strtoul(argv[2], NULL, 10);
    Player      players[NB_RECORDS] = { 0 };
    Player      *ht                 = calloc(size, sizeof(Player));

    get_data(argv[NB_ARGS], players, nb);
    display(ht, size);

    for (int i = 0; i < nb; i++) {
        insert(ht, &players[i], size, elf_hash);
    }

    printf("--------------------\n");
    display(ht, size);
    printf("--------------------\n");

    int elo = search(ht, size, "Carlsen", elf_hash);
    printf((elo != 0) ? "%-25s%d\n" : "Player not found", "Player found: Carlsen", elo);

    return 0;
}
