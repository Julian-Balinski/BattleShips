#include "ship.h"

Ship::Ship(short y, short x, short size, char dir, Player &player)
{
	--player.ships[size - 1];
	for (short i = 0; i < size; i++)
	{
		switch (dir)
		{
		case ('v'):
			player.board[y + i][x] = size;
			break;
		case ('>'):
			player.board[y][x + i] = size;
			break;
		case ('^'):
			player.board[y - i][x] = size;
			break;
		case ('<'):
			player.board[y][x - i] = size;
			break;
		}
	}
}

Ship::~Ship()
{
}