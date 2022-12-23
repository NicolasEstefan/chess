#include <stdio.h>
#include <stdlib.h>
#include "move.h"

#define MAX_STR_LENGTH 200
#define END_OF_STR '.'


char* readStr()
{
    char* str = (char*) malloc(sizeof(char)* MAX_STR_LENGTH);
    int i = 0;
    char c;

    while((c = getc(stdin)) != END_OF_STR && i < MAX_STR_LENGTH - 1)
    {
        str[i] = c;
        i++;
    }
    str[i] = '\0';

    return str;
}

Move readMove()
{
    Move move;
    scanf("%d,%d -> %d,%d", &move.from.i, &move.from.j, &move.to.i, &move.to.j);
    return move;
}