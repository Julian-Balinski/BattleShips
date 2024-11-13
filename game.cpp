#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "ship.cc"
using namespace std;
string getL;
void slowRead(string text, short wait)
{
	for (short i = 0; i < text.length(); i++)
	{
		cout << text[i];
		Sleep(wait);
	}
}
void waitForPlayer(short player, short phase, bool say)
{
	string Phases[] = {"Phase 1: setup", "Phase 2: fight"};
	slowRead(Phases[phase], 50);
	Sleep(1000);
	if (!say)
	{
		slowRead("\nMake sure that the other player isn't peeking on you Player ", 35);
		cout << player;
		Sleep(1000);
		slowRead("\nPress any key to continue...", 25);
		cin.get();
	}
}
bool shoot(short y, short x, bool &sinkShip, bool &canShoot, Player players[2], short p, bool say)
{
	bool sunk;
	if (players[p].shots[y][x])
	{
		if (say)
		{
			cout << "You can't shoot in the same place twice";
			Sleep(1000);
		}
		return 1;
	}
	else
	{
		players[p].shots[y][x] = 1;
		if (!players[(p + 1) % 2].board[y][x])
		{
			if (say)
			{
				players[p].render(players[(p + 1) % 2]);
				slowRead("Miss!", 25);
				Sleep(1000);
				if (cin.peek() != EOF)
					getline(cin, getL);
			}
			canShoot = 0;
			return 1;
		}
		else
		{
			if (!say)
				sinkShip = 1;
			sunk = players[p].isSunk(y, x, players[(p + 1) % 2].board);
			players[(p + 1) % 2].lives--;
			if (say)
			{
				players[p].render(players[(p + 1) % 2]);
				if (sunk)
					slowRead("You sunk an enemy ship! You get another shot\n", 25);
				else
					slowRead("Hit! You get another shot\n", 25);
				Sleep(250);
			}
			if (!say && sunk)
				sinkShip = 0;
			canShoot = 1;
			return 0;
		}
	}
}
void tutorial()
{
	system("cls");
	slowRead("Okay so for the start the rules are pretty simple\nAt the start you and your enemy place your ships in a 10 by 10 grid\nAfter which you two take turns guessing where the enemy placed there ships and shooting where you think they are\nAnd the first player to destroy all the ships of the other player wins\nAfter which you can decide do continue or stop playing\nGot it?", 25);
	slowRead("\nPress any key to continue...", 25);
	getline(cin, getL);
	system("cls");
	slowRead("Good ... right... ehh...\nOh Yeah right lets go over some examples of how to place ships and so on\nSo to place a ship you have to type something like this\nA6 2>\nWhich will result in the ship being placed like this:\n", 25);
	cout << "  ABCDEFGHIJ\n01\033[1;44m~~~~~~~~~~\033[0m\n02\033[1;44m~~~~~~~~~~\033[0m\n03\033[1;44m~~~~~~~~~~\033[0m\n04\033[1;44m~~~~~~~~~~\033[0m\n05\033[1;44m~~~~~~~~~~\033[0m\n06\033[1;44m#~~~~~~~~~\033[0m\n07\033[1;44m#~~~~~~~~~\033[0m\n08\033[1;44m~~~~~~~~~~\033[0m\n09\033[1;44m~~~~~~~~~~\033[0m\n10\033[1;44m~~~~~~~~~~\033[0m\n";
	slowRead("And to quickly explain the first letter 'A' represents the column from which the ship will originate\nThe 6 after that shows which row the ship will originate from\nThen you HAVE to type a spacebar after which you type the ships lenght here its 2 and at the end you type the diraction in which you want to place the ship using either 'v','>','^' or '<'\nAnd thats it for placing ships and to fire a shot you type the column and then the row example 'G2'\nJust some extra notes here\n1: When you type in a row it HAS to be in UPPER CASE so 'B' or 'J'\n2: You only have 1 ship of length 4, 2 ships of length 3, 3 ships of length 2 and finally 4 ships of length 1", 25);
	slowRead("\nPress any key to continue...", 25);
	getline(cin, getL);
	system("cls");
	slowRead("Here you go I hope you payed attention to what I said and that I didn't forget to tell you any thing... bye", 25);
	slowRead("\nPress any key to continue...", 25);
	getline(cin, getL);
	system("cls");
}
void game(string mode)
{
	system("cls");
	Player Players[2];
	short size = 0, y, aiY, aiX, yd = 0, xd = 0;
	char dirs[] = {'v', '>', '^', '<'}, dir = 0, x, Y_N;
	bool rend = 1, play = 1, canShoot, sinkShip, pastRoundOne = 0;
	while (play)
	{
		Players[0].reset();
		Players[1].reset();
		for (short p = 0; p < 2; p++)
		{
			if (p != 1 || mode[2] != 'E')
			{
				waitForPlayer(p + 1, 0, mode[2] % 2);
				while (Players[p].hasShips())
				{
					if (rend)
						Players[p].render(Players[(p + 1) % 2]);
					rend = 1;
					do
					{
						cin >> x;
						if (x < 'A' || x > 'J')
						{
							cout << "You can only input Letters form A to J as cordanit x\n";
							if (cin.peek() != EOF)
								getline(cin, getL);
						}
					} while (x < 'A' || x > 'J');
					do
					{
						cin >> y;
						if (y < 1 || y > 10)
						{
							cout << "You can only input numbers form 1 to 10 as cordanit y\n";
							if (cin.peek() != EOF || cin.fail())
							{
								cin.clear();
								cin.ignore(1000, '\n');
							}
							cout << x;
						}
					} while (y < 1 || y > 10);
					do
					{
						cin >> size;
						if (size < 1 || size > 4)
						{
							cout << "You can only input numbers from 1 to 4 as size\n";
							if (cin.peek() != EOF || cin.fail())
							{
								cin.clear();
								cin.ignore(1000, '\n');
							}
							cout << x << y << ' ';
						}
					} while (size < 1 || size > 4);
					do
					{
						cin >> dir;
						if (dir != 'v' && dir != '>' && dir != '^' && dir != '<')
						{
							cout << "You can only input v, >, ^ or < as direction\n";
							if (cin.peek() != EOF)
								getline(cin, getL);
							cout << x << y << ' ' << size;
						}
					} while (dir != 'v' && dir != '>' && dir != '^' && dir != '<');
					x -= 65;
					y--;
					if (Players[p].ships[size - 1] > 0 && Players[p].shipPlaceCheck(y, x, size, dir, Players[p].board))
						Ship(y, x, size, dir, Players[p]);
					else
					{
						if (Players[p].shipPlaceCheck(y, x, size, dir, Players[p].board) == 0)
						{
							cout << "You can't place a ship there\n";
							rend = 0;
						}
						if (Players[p].ships[size - 1] <= 0)
						{
							cout << "You don't have more of that ship type\n";
							rend = 0;
						}
					}
				}
				if (cin.peek() != EOF)
					getline(cin, getL);
				system("cls");
			}
			else
			{
				while (Players[1].hasShips())
				{
					y = rand() % 10;
					x = rand() % 10;
					for (short i = 0; i < 4; i++)
						if (Players[1].ships[i] != 0)
							size = i + 1;
					dir = dirs[rand() % 4];
					if (Players[1].shipPlaceCheck(y, x, size, dir, Players[1].board))
						Ship(y, x, size, dir, Players[1]);
				}
			}
		}
		while (Players[0].lives > 0 && Players[1].lives > 0)
		{
			for (short p = 0; p < 2 && Players[0].lives > 0 && Players[1].lives > 0; p++)
			{
				if (p != 1 || mode[2] != 'E')
				{
					system("cls");
					if ((!pastRoundOne && mode[2] == 'E') || mode[2] == 'P')
						waitForPlayer(p + 1, 1, mode[2] % 2);
					canShoot = 1;
					while (canShoot)
					{
						if (rend)
						{
							Players[p].render(Players[(p + 1) % 2]);
							if (mode[2] == 'E')
								cout << "Your Turn:\n";
						}
						rend = 1;
						do
						{
							cin >> x;
							if (x < 'A' || x > 'J')
							{
								cout << "You can only input Letters form A to J as cordanit x\n";
								if (cin.peek() != EOF)
									getline(cin, getL);
							}
						} while (x < 'A' || x > 'J');
						do
						{
							cin >> y;
							if (y < 1 || y > 10)
							{
								cout << "You can only input numbers form 1 to 10 as cordanit y\n";
								if (cin.peek() != EOF || cin.fail())
								{
									cin.clear();
									cin.ignore(1000, '\n');
								}
								cout << x;
							}
						} while (y < 1 || y > 10);
						rend = shoot(y - 1, x - 65, sinkShip, canShoot, Players, p, 1);
						if (Players[0].lives <= 0 || Players[1].lives <= 0)
							canShoot = 0;
					}
				}
				else
				{
					canShoot = 1;
					while (canShoot)
					{
						if (!sinkShip)
						{
							yd = 0;
							xd = 0;
							do
							{
								aiY = rand() % 10;
								aiX = rand() % 10;
							} while (Players[1].shots[aiY][aiX]);
							shoot(aiY, aiX, sinkShip, canShoot, Players, p, 0);
							Players[0].render(Players[1]);
							cout << "Ais Turn:\n";
							Sleep(1000);
							if (Players[0].lives <= 0 || Players[1].lives <= 0)
								canShoot = 0;
						}
						else
						{
							if (yd == 0 && xd == 0)
							{
								do
								{
									dir = rand() % 4;
									yd = ((dir + 1) % 2) + (-dir * ((dir + 1) % 2));
									xd = (dir % 2) * (-1 + (dir - 1) % 3);
								} while (Players[1].shots[aiY + yd][aiX + xd] || aiY + yd < 0 || aiY + yd >= 10 || aiX + xd < 0 || aiX + xd >= 10);
							}
							else
							{
								if (!Players[1].shots[aiY + yd][aiX + xd])
								{
									for (short i = 1; !shoot(aiY + yd * i, aiX + xd * i, sinkShip, canShoot, Players, p, 0) && aiY + yd * i >= 0 && aiY + yd * i < 10 && aiX + xd * i >= 0 && aiX + xd * i < 10; i++)
									{
										Players[0].render(Players[1]);
										cout << "Ais Turn:\n";
										Sleep(1000);
									}
									yd *= -1;
									xd *= -1;
								}
								else
								{
									yd = 0;
									xd = 0;
								}
							}
						}
					}
				}
			}
			pastRoundOne += 1;
		}
		if (Players[0].lives > 0)
		{
			slowRead("Player 1 Won!", 50);
			Players[0].score++;
		}
		else
		{
			slowRead("Player 2 Won!", 50);
			Players[1].score++;
		}
		Sleep(1500);
		system("cls");
		slowRead("Do you want to play again? [Y/N]\n", 50);
		play = 0;
		cin >> Y_N;
		if (Y_N == 'Y' || Y_N == 'y')
		{
			play = 1;
		}
		for (short p = 0; p < 2; p++)
		{
			slowRead("\nscore Player ", 25);
			cout << p + 1 << ':' << Players[p].score << endl;
		}
		Sleep(1500);
		system("cls");
	}
}
int main()
{
	srand(time(0));
	string input;
	slowRead("Welcome Player/Players would you like to get a tutorial or do you want to get straight to the game?\n", 25);
	do
	{
		slowRead("tutorial : Takes you to the tutorial of the game\nPvP : Play the game against an another player\nPvE : Play the game against an AI opponent\nstop : Stops the program\n", 25);
		cin >> input;
		if (cin.peek() != EOF)
			getline(cin, getL);
		if (input == "tutorial")
		{
			tutorial();
			cout << "tutorial : Takes you to the tutorial of the game\nPvP : Play the game against a another player\n";
		}
		else if (input == "PvP" || input == "PvE")
			game(input);
		else if (input != "stop")
			cout << "Unknown command\n";
	} while (input != "stop");
}