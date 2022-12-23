#include <stdio.h>
#include "board.h"
#include "piece.h"
#include "move.h"
#include "userInput.h"

int main() // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
{
    Board board;
    board.board = allocateBoard();
    parseFenString("rnbqkb1r/ppp2ppp/4pn2/3p4/3PP1K1/8/PPP2PPP/RNBQ1BNR", board.board);
    board.colorToMove = WHITE;
    board.checkState = NONE;
    Position kingPos = findKingPos(board);
    printf("%d %d", kingPos.i, kingPos.j);
    isInCheck(kingPos, board.board);
    printBoard(board);

    return 0;
}