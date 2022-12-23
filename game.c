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
    parseFenString(INITIAL_BOARD, board.board);

    Move* availMoves = NULL;

    while(1)
    {
        Position kingPos = findKingPos(board);
        board.checkState = isInCheck(kingPos, board.board) ? board.colorToMove : NONE;
        printBoard(board);
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