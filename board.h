#ifndef BOARD_H    
#define BOARD_H
#include "move.h"

#define BOARD_SIZE 8
#define INITIAL_BOARD "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

typedef struct Board 
{
    int** board;
    int checkState, colorToMove; // these use the black and white constants, 0 if no one is in check
} Board;


int** allocateBoard();
void printBoard(Board board);
void initializeBoard(Board* board);
void parseFenString(char* fenString, int** board);
char* readStr();
void printBoardAndMoves(int** board, Move* movesList);

#endif