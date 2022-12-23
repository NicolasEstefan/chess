#include <stdio.h>
#include "board.h"
#include "piece.h"
#include "move.h"
#include <stdlib.h>
#include "userInput.h"

int main()
{
    Board board;
    board.checkState = NONE;
    board.colorToMove = WHITE;
    board.board = allocateBoard();
    parseFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", board.board);

    Move* availMoves = NULL;

    while(1)
    {
        printBoard(board.board);
        generateAvailMoves(board.board, &availMoves, board.colorToMove);
        Move move = readMove();
        if(containsMove(move, availMoves))
        {
            makeMove(board.board, move);
            board.colorToMove = board.colorToMove == WHITE ? BLACK : WHITE;
            clearMoveList(&availMoves);
        }
    }
}