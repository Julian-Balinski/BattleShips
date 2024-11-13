#ifndef PLAYER
#define PLAYER
#include "board.cc"
using namespace std;
class Player : public Board
{
private:
protected:
public:
    short ships[4], lives, score;
    Player();
    ~Player();
    bool shipPlaceCheck(short y, short x, short size, char dir, short board[10][10]);
    bool shipCheck(short board[10][10], short y, short x, short i, short j);
    bool hasShips();
    void reset();
    void cleanBoard(short eBoard[10][10],bool block);
    short countHits(short eBoard[10][10],short y,short x,short size);
    bool isSunk(short y,short x,short eBoard[10][10]);
};
#endif