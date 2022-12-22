#include <stdio.h>
#include "board.h"
#include "piece.h"
#include "move.h"

int main() // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
{
    Board board;
    board.board = allocateBoard();
    char* str = readStr();
    parseFenString(str, board.board);
    printBoard(board.board);
    printf("\n");

    Move* moveList = 0;
    Position pos = {3,5};
    generateKingMoves(pos, board.board, &moveList);
    printBoardAndMoves(board.board, moveList);

    return 0;
}