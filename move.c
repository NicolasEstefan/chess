#include <stdbool.h>
#include "move.h"
#include <stdlib.h>
#include <stdio.h>
#include "piece.h"

const int DIRECTIONS[8][2] =
{
    { -1, -1 },// bishop directions 
    { -1, 1 },
    { 1, 1 },
    { 1, -1 }, 
    { 0, -1 }, // rook directions
    { -1, 0 },
    { 0, 1 },
    { 1, 0 }
};

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

bool isValidPosition(struct Position pos)
{
    return(pos.i >= 0 && pos.i < 8 && pos.j >= 0 && pos.j < 8);
}

void addMove(struct Move move, struct Move** moveList)
{
    struct Move* ptr = (struct Move*) malloc(sizeof(struct Move));
    *ptr = move;
    ptr->next = *moveList;
    *moveList = ptr;
}

bool containsMove(struct Move move, struct Move* moveList)
{
    while(moveList != 0)
    {
        if(moveCompare(move, *moveList))
            return true;
        moveList = moveList->next;
    }

    return false;
}

bool controlsSquare(struct Position pos, struct Move* moveList)
{
    while(moveList != 0)
    {
        if(moveList->to.i == pos.i && moveList->to.j == pos.j)
            return true;
        moveList = moveList->next;
    }

    return false;
}

void printMoves(struct Move* moveList)
{
    while(moveList != 0)
    {
        printf("%d %d -> %d %d \n", 
        moveList->from.i, moveList->from.j,
        moveList->to.i, moveList->to.j);
        moveList = moveList->next;
    }
}

void generateSlidingMoves(struct Position pos, int** board, struct Move** moveList)
{
    int piece = pieceType(board[pos.i][pos.j]);
    int startDirection = (piece == BISHOP || piece == QUEEN) ? 0 : 4;
    int endDirection = piece == QUEEN ? 8 : startDirection + 4;

    for (int k = startDirection; k < endDirection; k++)
    {
        struct Position endPos;
        endPos.i = pos.i + DIRECTIONS[k][0];
        endPos.j = pos.j + DIRECTIONS[k][1];
        
        while (isValidPosition(endPos))
        {
            struct Move move = { pos, endPos, NULL };

            if(board[endPos.i][endPos.j] == 0)
            {
                addMove(move, moveList);
                endPos.i = endPos.i + DIRECTIONS[k][0];
                endPos.j = endPos.j + DIRECTIONS[k][1];
                continue;
            }

            if(areEnemies(board[pos.i][pos.j], board[endPos.i][endPos.j]))
                addMove(move, moveList);

            break;
        }
        
    }
    
}
