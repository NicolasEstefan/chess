#ifndef PIECE_H    
#define PIECE_H

#include <stdbool.h>
#include "board.h"

#define NONE 0
#define KING 1
#define PAWN 2
#define KNIGHT 3
#define BISHOP 4
#define ROOK 5
#define QUEEN 6

#define WHITE 8
#define BLACK 16

bool isWhite(int piece);
char numToPieceChar(int piece);
int pieceType(int piece);
bool areEnemies(int piece1, int piece2);

#endif
