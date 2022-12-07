#include <stdbool.h>
#include "move.h"
#include <stdlib.h>
#include <stdio.h>

bool moveCompare(struct Move move1, struct Move move2)
{
    return 
    (
        move1.from.i == move2.from.i &&
        move1.from.j == move2.from.j &&
        move1.to.j == move2.to.j &&
        move1.to.i == move2.to.i 
    );

}

void addMove(struct Move move, struct Move** moveList)
{
    struct Move* ptr = (struct Move*) malloc(sizeof(struct Move));
    *ptr = move;
    ptr->next = *moveList;
    *moveList = ptr;
}

bool containsMove(struct Move move, struct Move* listMove)
{
    while(listMove != 0)
    {
        if(moveCompare(move, *listMove))
            return true;
        listMove = listMove->next;
    }

    return false;
}

void printMoves(struct Move* listMove)
{
    while(listMove != 0)
    {
        printf("%d %d -> %d %d \n", 
        listMove->from.i, listMove->from.j,
        listMove->to.i, listMove->to.j);
        listMove = listMove->next;
    }
}

