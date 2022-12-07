#ifndef BOARD_H    
#define BOARD_H


#define MAX_STR_LENGTH 200
#define END_OF_STR '.'

struct Board 
{
    int** board;
    int checkState, colorToMove; // these use the black and white constants, 0 if no one is in check
};


int** allocateBoard();
void printBoard(int** board);
void initializeBoard(struct Board* board);
void parseFenString(char* fenString, int** board);
char* readStr();

#endif