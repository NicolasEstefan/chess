#include <stdio.h>
#include "board.h"
#include "piece.h"
#include "move.h"
#include "userInput.h"

int main() // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
{
    Board board;
    board.board = allocateBoard();
    parseFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", board.board);
    printBoard(board.board);
    printf("\n");

    Move* moveList = 0;
    generateAvailMoves(board.board, &moveList, WHITE);
    printMoves(moveList);

    return 0;
}