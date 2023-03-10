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

void clearMoveList(Move** moveList)
{
    Move* ptr;

    while (*moveList != NULL)
    {
        ptr = *moveList;
        *moveList = ptr->next;
        free(ptr);
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
        
        if(board[endPos.i][endPos.j] == NONE || areEnemies(board[pos.i][pos.j], board[endPos.i][endPos.j]))
        {
            Move move = { pos, endPos };
            addMove(move, moveList);
        }
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

void generateKingMoves(Position pos, int** board, Move** moveList)
{
    for (int k = 0; k < 8; k++)
    {
        Position endPos;
        endPos.i = pos.i + DIRECTIONS[k][0];
        endPos.j = pos.j + DIRECTIONS[k][1];
        
        if (isValidPosition(endPos))
        {
            Move move = { pos, endPos };

            if(board[endPos.i][endPos.j] == 0)
            {
                addMove(move, moveList);
                continue;
            }

            if(areEnemies(board[pos.i][pos.j], board[endPos.i][endPos.j]))
                addMove(move, moveList);
        }
    }
}

void generateAvailMoves(int** board, Move** moveList, int colorToMove)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int piece = board[i][j];

            if(pieceColor(piece) != colorToMove)
                continue;

            int type = pieceType(piece);
            Position pos = { i, j };

            if(type == QUEEN || type == ROOK || type == BISHOP)
            {
                generateSlidingMoves(pos, board, moveList);
                continue;
            }
            
            switch (type)
            {
                case KNIGHT:
                    generateKnightMoves(pos, board, moveList);
                    break;
                case KING:
                    generateKingMoves(pos, board, moveList);
                    break;
                case PAWN:
                    generatePawnMoves(pos, board, moveList);
                    break;
                default:
                    break;
            }
        }
    }
    
}

void makeMove(int** board, Move move)
{
    board[move.to.i][move.to.j] = board[move.from.i][move.from.j];
    board[move.from.i][move.from.j] = NONE;
}

bool isInCheck(Position kingPos, int** board)
{
    for (int i = 0; i < 8; i++) // check if sliding pieces are attacking king
    {
        Position pos = { kingPos.i + DIRECTIONS[i][0], kingPos.j + DIRECTIONS[i][1] };

        while(isValidPosition(pos))
        {
            int piece = board[pos.i][pos.j];

            if(piece == NONE)
            {
                pos.i = pos.i + DIRECTIONS[i][0];
                pos.j = pos.j + DIRECTIONS[i][1];
                continue;
            }

            if(!areEnemies(board[kingPos.i][kingPos.j], piece))
                break;

            if((i < 4 && pieceType(piece) == BISHOP) || pieceType(piece) == QUEEN)
                return true;
            
            if(i >= 4 && pieceType(piece) == ROOK)
                return true;
            
            if(i < 4 && pieceType(piece) == PAWN && pieceColor(piece) == BLACK && pos.i == kingPos.i - 1)
                return true;
            
            if(i < 4 && pieceType(piece) == PAWN && pieceColor(piece) == WHITE && pos.i == kingPos.i + 1)
                return true;

            break;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        Position pos;
        pos.i = kingPos.i + KNIGHT_OFFSETS[i][0];
        pos.j = kingPos.j + KNIGHT_OFFSETS[i][1];

        if(isValidPosition(pos) && areEnemies(board[kingPos.i][kingPos.j], board[pos.i][pos.j]) && pieceType(board[pos.i][pos.j]) == KNIGHT)
            return true;        
    }

    return false;
}