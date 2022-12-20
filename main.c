#include <stdio.h>
#include "board.h"
#include "piece.h"
#include "move.h"

int main() // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
{
    struct Board board;
    board.board = allocateBoard();
    char* str = readStr();
    parseFenString(str, board.board);
    printBoard(board.board);

    struct Move* moveList = 0;
    struct Position pos = {3,7};
    generateSlidingMoves(pos, board.board, &moveList);
    printBoardAndMoves(board.board, moveList);

    return 0;
}