#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

int BasketX = 28;
int BasketY = 22;
bool GameOver = false;

void SaveScore(char Name[10], int Score);
void DisplayScore();

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Draw()
{
	system("cls");
	cout << "******************************** Catch the Egg ********************************" << endl;
	cout << "Your Score: " << endl << endl;
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&                                                      &" << endl;
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;

	gotoxy(BasketX, BasketY);
	cout << "|_____|";
}

void Eggs(int Arr[][10], int &Egg, int &Increase, bool &Generate, int &Score)
{
	const int Range1 = 38;
	const int Range2 = 12;

	if (Generate)
	{
		srand(time(NULL));
		Arr[0][Egg - 1] = rand() % Range1 + Range2;
		Generate = false;
	}

	for (int i = 0; i < Egg; i++)
	{
		if (Arr[1][i] <= BasketY && Arr[1][i] > 4)
		{
			gotoxy(Arr[0][i], Arr[1][i] - 1);
			cout << " ";
		}
		if (Arr[1][i] < BasketY)
		{
			gotoxy(Arr[0][i], Arr[1][i]);
			cout << "O";
		}
		if (!(Arr[0][i] > BasketX && Arr[0][i] < BasketX + 7) && Arr[1][i] == BasketY)
		{
			GameOver = true;
			break;
		}
		else if (Arr[1][i] == BasketY)
		{
			Score++;
		}
		if (Arr[1][i] <= BasketY)
			Arr[1][i]++;
	}

	if (Increase == 15)
	{
		Egg++;
		Generate = true;
		Increase = 0;
	}
	if (Egg == 10)
	{
		if (Arr[1][9] == BasketY+1)
		{

			Egg = 1;
			Generate = true;
			for (int i = 0; i < 10; i++)
			{
				Arr[1][i] = 4;
			}
		}
		Increase = 0;
	}

	gotoxy(13, 1);
	cout << Score;

	Increase++;
}

void Moving()
{
	char key;

	while (_kbhit() != 0)
	{
		key = _getch();
		if (key == 'a')
		{
			gotoxy(BasketX, BasketY);
			cout << "       ";
			BasketX--;
			gotoxy(BasketX, BasketY);
			cout << "|_____|";
		}
		else if (key == 'd')
		{
			gotoxy(BasketX, BasketY);
			cout << "       ";
			BasketX++;
			gotoxy(BasketX, BasketY);
			cout << "|_____|";
		}
		else if (key == 'q')
		{
			GameOver = true;
		}
	}
}


int main()
{
	char Name[10] = { '\0' };
	int Input = 0;
	int EggArr[2][10] = { { 0 }, { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 } };
	int Egg = 1;
	int Increase = 0;
	int Score = 0;
	bool Generate;
	int Speed = 0;

	Draw();
	while (!GameOver)
	{
		Moving();
		if (Speed == 10)
		{
			Eggs(EggArr, Egg, Increase, Generate, Score);
			Speed = 0;
		}
		Speed++;
		Sleep(10);
	}

	system("cls");
	cout << "Game Over !!!!...." << endl;
	cout << "Your Final Score: " << Score << endl;
	cout << "Enter your name: ";
	cin >> Name;
	SaveScore(Name, Score);
	cout << "Press 1 to see score board or 0 to quit: ";
	cin >> Input;

	if (Input == 1)
	{
		DisplayScore();
	}
	system("pause");
}

void SaveScore(char Name[10], int Score)
{
	ofstream fout("score.txt", ios::app);
	fout << Name << ' ' << Score << endl;
	fout.close();
}

void DisplayScore()
{
	char FileName[10] = { '\0' };
	int FileScore = 0;

	ifstream fin("score.txt", ios::in);
	system("cls");
	cout << "******************************** Score Board ***********************************" << endl << endl;
	while (1)
	{
		fin >> FileName >> FileScore;
		if (fin.eof())
			break;
		
		cout << FileName << " " << FileScore << endl;
	}
	fin.close();
}