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

const int KNIGHT_OFFSETS[8][2] = 
{
    { -2, 1 },
    { -1, 2 },
    { 1, 2 },
    { 2, 1 },
    { 2, -1 },
    { 1, -2 },
    { -1, -2 },
    { -2, -1 }
};

bool moveCompare(Move move1, Move move2)
{
    return 
    (
        move1.from.i == move2.from.i &&
        move1.from.j == move2.from.j &&
        move1.to.j == move2.to.j &&
        move1.to.i == move2.to.i 
    );

}

bool isValidPosition(Position pos)
{
    return(pos.i >= 0 && pos.i < 8 && pos.j >= 0 && pos.j < 8);
}

void addMove(Move move, Move** moveList)
{
    Move* ptr = (Move*) malloc(sizeof(Move));
    *ptr = move;
    ptr->next = *moveList;
    *moveList = ptr;
}

bool containsMove(Move move, Move* moveList)
{
    while(moveList != 0)
    {
        if(moveCompare(move, *moveList))
            return true;
        moveList = moveList->next;
    }

    return false;
}

bool controlsSquare(Position pos, Move* moveList)
{
    while(moveList != 0)
    {
        if(moveList->to.i == pos.i && moveList->to.j == pos.j)
            return true;
        moveList = moveList->next;
    }

    return false;
}

void printMoves(Move* moveList)
{
    while(moveList != 0)
    {
        printf("%d %d -> %d %d \n", 
        moveList->from.i, moveList->from.j,
        moveList->to.i, moveList->to.j);
        moveList = moveList->next;
    }
}

void generateSlidingMoves(Position pos, int** board, Move** moveList)
{
    int piece = pieceType(board[pos.i][pos.j]);
    int startDirection = (piece == BISHOP || piece == QUEEN) ? 0 : 4;
    int endDirection = piece == QUEEN ? 8 : startDirection + 4;

    for (int k = startDirection; k < endDirection; k++)
    {
        Position endPos;
        endPos.i = pos.i + DIRECTIONS[k][0];
        endPos.j = pos.j + DIRECTIONS[k][1];
        
        while (isValidPosition(endPos))
        {
            Move move = { pos, endPos, NULL };

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


void generateKnightMoves(Position pos, int** board, Move** moveList)
{
    Position endPos;
    
    for (int i = 0; i < 8; i++)
    {
        endPos.i = pos.i + KNIGHT_OFFSETS[i][0];
        endPos.j = pos.j + KNIGHT_OFFSETS[i][1];

        if(!isValidPosition(endPos)) // if endpos is outside the board
            continue;
        
        if(!areEnemies(board[pos.i][pos.j], board[endPos.i][endPos.j])) // if an ally is on endPos
            continue;
        
        Move move = { pos, endPos };
        addMove(move, moveList);

    }
    
}

void generatePawnMoves(Position pos, int** board, Move** moveList) // no en passant yet
{
    int piece = board[pos.i][pos.j];
    int offset = isWhite(piece) ? -1 : 1;
    Position endPos = { pos.i + offset, pos.j };
    Move move = { pos, endPos };

    if(isValidPosition(endPos) && board[endPos.i][endPos.j] == NONE)
        addMove(move, moveList);

    if((isWhite(piece) && pos.i == 6 || !isWhite(piece) && pos.i == 1) && board[endPos.i][endPos.j] == NONE)
    {
        endPos.i = pos.i + 2 * offset;
        move.to = endPos;
        addMove(move, moveList);
    }

    endPos.i = pos.i + offset;
    endPos.j = pos.j + 1;
    move.to = endPos;

    if(isValidPosition(endPos) && areEnemies(board[endPos.i][endPos.j], piece))
        addMove(move, moveList);
    
    endPos.i = pos.i + offset;
    endPos.j = pos.j - 1;
    move.to = endPos;

    if(isValidPosition(endPos) && areEnemies(board[endPos.i][endPos.j], piece))
        addMove(move, moveList);
}
