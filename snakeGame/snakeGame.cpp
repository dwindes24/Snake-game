#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;
bool gameOver;
const int boardWidth = 20;
const int boardHeight = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = boardWidth / 2;
	y = boardHeight / 2;
	srand(time(0));
	fruitX = rand() % boardWidth;
	fruitY = rand() % boardHeight;
	score = 0;
}
void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < boardWidth + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == boardWidth - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < boardWidth + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > boardWidth || x < 0 || y > boardHeight || y < 0)
		gameOver = true;

	//below can be used if you want to go through the wall and come out the other side
	//if (x >= boardWidth) x = 0; else if (x < 0) x = boardWidth - 1;
	//if (y >= boardHeight) y = 0; else if (y < 0) y = boardHeight - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % boardWidth;
		fruitY = rand() % boardHeight;
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100); //sleep(10);
	}
	return 0;
}
