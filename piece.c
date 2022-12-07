#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"

bool isWhite(int piece)
{
    return ((piece >> 3) == 1);
}

char numToPieceChar(int piece)
{
    char pieceChar;
    switch ((piece ^ BLACK) & (piece ^ WHITE))
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