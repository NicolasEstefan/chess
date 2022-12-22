#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "piece.h"
#include "colors.h"
#include "board.h"
#include "move.h"


const int BOARD_SIZE = 8;

int** allocateBoard()
{
    int** board = (int**) malloc(BOARD_SIZE * sizeof(int*));

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board[i] = (int*) malloc(BOARD_SIZE * sizeof(int));
    }

    return board;    
}

void printBoard(int** board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            char c = numToPieceChar(board[i][j]);
            
            if(board[i][j] == 0)
            {
                printf(BLU "%c " reset, c);
                continue;
            }

            if(isWhite(board[i][j]))
                printf(BCYN "%c " reset, c);
            else
                printf(BMAG "%c " reset, c);
        }   
        printf("\n");
    }
}

void printBoardAndMoves(int** board, Move* movesList)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Position pos = { i, j };
            char c = numToPieceChar(board[i][j]);

            if(controlsSquare(pos, movesList))
            {
                printf(RED "%c " reset, c);
                continue;
            }

            if(board[i][j] == 0)
            {
                printf(BLU "%c " reset, c);
                continue;
            }

            if(isWhite(board[i][j]))
                printf(BCYN "%c " reset, c);
            else
                printf(BMAG "%c " reset, c);
        }   
        printf("\n");
    }
}

void initializeBoard(Board* board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            (*board).board[i][j] = 1;
        }
    }
}

void parseFenString(char* fenString, int** board)
{
    int currentRow = 0;
    int currentCol = 0;

    while(*fenString != '\0')
    {

        if(*fenString == '/')
        {
            currentRow++;
            currentCol = 0;
            fenString++;
            continue;
        }

        if(isdigit(*fenString))
        {
            currentCol += *fenString - '0';
            fenString++;
            continue;
        }

        int piece = islower(*fenString) ? BLACK : WHITE;
        int pieceType = tolower(*fenString);

        switch (pieceType)
        {
            case 'k':
                piece += KING;
                break;
            case 'p':
                piece += PAWN;
                break;
            case 'n':
                piece += KNIGHT;
                break;
            case 'b':
                piece += BISHOP;
                break;
            case 'r':
                piece += ROOK;
                break;
            case 'q':
                piece += QUEEN;
                break;
            default:
                break;
        }

        board[currentRow][currentCol] = piece;

        fenString++;
        currentCol++;
    }
}

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