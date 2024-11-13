#ifndef BOARD
#define BOARD
using namespace std;
class Board
{
private:
protected:
public:
    short board[10][10];
    bool shots[10][10];
    Board();
    ~Board();
    void render(Board eBorad);
    void sep(int s);
};
#endif