#include "board.h"
#include <iostream>
Board::Board()
{
    for (short i = 0; i < 10; i++)
    {
        for (short j = 0; j < 10; j++)
        {
            this->board[i][j] = 0;
            this->shots[i][j] = 0;
        }
    }
}

Board::~Board()
{
}

void Board::sep(int s)
{
    for (short i = 0; i < s; i++)
    {
        cout << " ";
    }
}
void Board::render(Board eBoard)
{
    system("cls");
    char notation = 65;
    sep(5);
    cout << "You";
    sep(13);
    cout << "Enemy\n";
    sep(2);
    for (short n = 0; n < 10; n++)
    {
        cout << notation++;
    }
    sep(7);
    notation = 65;
    for (short n = 0; n < 10; n++)
    {
        cout << notation++;
    }
    cout << "\n";
    for (short i = 0; i < 10; i++)
    {
        cout << (i + 1) / 10 << (i + 1) % 10;
        for (short j = 0; j < 10; j++)
        {
            cout << "\033[1;44m";
            if (board[i][j] > 0 && board[i][j] < 5)
                if (eBoard.shots[i][j] == 0)
                    cout << "#";
                else
                    cout << "\033[1;31mX";
            else if (eBoard.shots[i][j] == 0)
                cout << '~';
            else
                cout << "\033[1;32mO";
            cout << "\033[0m";
        }
        sep(5);
        cout << (i + 1) / 10 << (i + 1) % 10;
        for (short j = 0; j < 10; j++)
        {
            cout << "\033[1;44m";
            if (shots[i][j] == 0)
                cout << '~';
            else if (eBoard.board[i][j] == 0)
                cout << "\033[1;32mO";
            else
                cout << "\033[1;31mX";
            cout << "\033[0m";
        }
        cout << "\n";
    }
}