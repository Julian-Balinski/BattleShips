#ifndef SHIP
#define SHIP
#include "player.cc"
using namespace std;
class Ship : public Player
{
private:
protected:
public:
    Ship(short y, short x, short size, char dir, Player &player);
    ~Ship();
};
#endif