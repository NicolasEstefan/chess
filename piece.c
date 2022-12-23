#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"
#include "board.h"

bool isWhite(int piece)
{
    return ((piece >> 3) == 1);
}

int pieceType(int piece)
{
    return (piece ^ BLACK) & (piece ^ WHITE);
}

int pieceColor(int piece)
{
    return (piece >> 3) << 3;
}

bool areEnemies(int piece1, int piece2)
{
    if(piece1 == NONE || piece2 == NONE)
        return false;

    return (isWhite(piece1) && !isWhite(piece2) || !isWhite(piece1) && isWhite(piece2));
}

char numToPieceChar(int piece)
{
    char pieceChar;
    switch (pieceType(piece))
    {
        case KING:
            pieceChar = 'k';
            break;
        case PAWN:
            pieceChar = 'p';
            break;
        case KNIGHT:
            pieceChar = 'n';
            break;
        case BISHOP:
            pieceChar = 'b';
            break;
        case ROOK:
            pieceChar = 'r';
            break;
        case QUEEN:
            pieceChar = 'q';
            break;
        default:
            pieceChar = '0';
            break;
    }
    if(isWhite(piece))
        pieceChar = toupper(pieceChar);
    
    return pieceChar;
}

Position findKingPos(Board board)
{
    Position pos;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if(board.board[i][j] == KING + board.colorToMove)
            {
                pos.i = i;
                pos.j = j;
                return pos;
            }
        }
    }
    
}