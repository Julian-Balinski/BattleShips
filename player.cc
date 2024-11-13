#include "player.h"

Player::Player()
{
	this->lives = 20;
	for (short i = 0; i < 4; i++)
	{
		this->ships[3 - i] = i + 1;
	}
}

bool Player::hasShips()
{
	for (short i = 0; i < 4; i++)
		if (ships[i] != 0)
			return 1;
	return 0;
}

void Player::reset()
{
	lives = 20;
	for (short i = 0; i < 4; i++)
	{
		ships[3 - i] = i + 1;
	}
	for (short i = 0; i < 10; i++)
	{
		for (short j = 0; j < 10; j++)
		{
			board[i][j] = 0;
			shots[i][j] = 0;
		}
	}
}

bool Player::shipPlaceCheck(short y, short x, short size, char dir, short board[10][10])
{
	for (short i = -1; i <= size; i++)
	{
		for (short j = -1; j < 2; j++)
		{
			switch (dir)
			{
			case ('v'):
				if (shipCheck(board, y, x, i, j) || (j == 0 && i >= 1 && i <= size - 1 && (y + i > 9)))
					return 0;
				break;
			case ('>'):
				if (shipCheck(board, y, x, -j, i) || (j == 0 && i >= 1 && i <= size - 1 && (x + i > 9)))
					return 0;
				break;
			case ('^'):
				if (shipCheck(board, y, x, -i, -j) || (j == 0 && i <= -1 && i >= -(size - 1) && (y + i < 0)))
					return 0;
				break;
			case ('<'):
				if (shipCheck(board, y, x, j, -i) || (j == 0 && i <= -1 && i >= -(size - 1) && (x + i < 0)))
					return 0;
				break;
			}
		}
	}
	return 1;
}

bool Player::shipCheck(short board[10][10], short y, short x, short i, short j)
{
	if ((board[y + i][x + j] >= 1 && board[y + i][x + j] <= 4 && y + i >= 0 && y + i <= 10 && x + j >= 0 && x + j <= 10))
		return 1;
	return 0;
}

short Player::countHits(short eBoard[10][10], short y, short x, short size)
{
	short hits = 0;
	if (eBoard[y][x] == size)
	{
		if (shots[y][x])
			hits++;
		eBoard[y][x] = -size;
		if (y + 1 < 10)
			hits += countHits(eBoard, y + 1, x, size);
		if (x + 1 < 10)
			hits += countHits(eBoard, y, x + 1, size);
		if (y - 1 >= 0)
			hits += countHits(eBoard, y - 1, x, size);
		if (x - 1 >= 0)
			hits += countHits(eBoard, y, x - 1, size);
	}
	return hits;
}

bool Player::isSunk(short y, short x, short eBoard[10][10])
{
	short size = eBoard[y][x];
	if (countHits(eBoard, y, x, eBoard[y][x]) == size)
	{
		cleanBoard(eBoard, 1);
		return 1;
	}
	else
	{
		cleanBoard(eBoard, 0);
		return 0;
	}
}

void Player::cleanBoard(short eBoard[10][10], bool block)
{
	for (short i = 0; i < 10; i++)
	{
		for (short j = 0; j < 10; j++)
		{
			if (eBoard[i][j] < 0)
			{
				eBoard[i][j] *= -1;
				if (block)
				{
					for (short y = -1; y < 2; y++)
					{
						for (short x = -1; x < 2; x++)
						{
							if (i + y >= 0 && i + y < 10 && j + x >= 0 && j + x < 10)
								shots[i + y][j + x] = 1;
						}
					}
				}
			}
		}
	}
}

Player::~Player()
{
}