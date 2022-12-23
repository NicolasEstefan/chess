#ifndef MOVE_H    
#define MOVE_H

#include <stdbool.h>

typedef struct Position
{
    int i, j;
} Position;

typedef struct Move
{
    struct Position from, to;
    struct Move* next;
} Move;

bool moveCompare(Move move1, Move move2);
void addMove(Move move, Move** moveList);
bool containsMove(Move move, Move* listMove);
void printMoves(Move* moveList);
void generateSlidingMoves(Position pos, int** board, Move** moveList);
bool controlsSquare(Position pos, Move* moveList);
void generateKnightMoves(Position pos, int** board, Move** moveList);
void generatePawnMoves(Position pos, int** board, Move** moveList);
void generateKingMoves(Position pos, int** board, Move** moveList);
void generateAvailMoves(int** board, Move** moveList, int colorToMove);
void makeMove(int** board, Move move);
void clearMoveList(Move** moveList);
bool isInCheck(Position kingPos, int** board);

#endif