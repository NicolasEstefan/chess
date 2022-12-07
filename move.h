#ifndef MOVE_H    
#define MOVE_H

struct Position
{
    int i, j;
};

struct Move
{
    struct Position from, to;
    struct Move* next;
};

bool moveCompare(struct Move move1, struct Move move2);
void addMove(struct Move move, struct Move** moveList);
bool containsMove(struct Move move, struct Move* listMove);
void printMoves(struct Move* listMove);

#endif