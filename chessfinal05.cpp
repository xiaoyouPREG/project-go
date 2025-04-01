#define _CRT_SECURE_NO_WARINNGS
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;
int plate[23][23];
typedef struct pairint {
	int x;
	int y;
}pairint;
int first_player = 1;
int win = 0;
int lose = 0;
void infgame(void);
void black_white(void);
void draw_line();
int pn(int t);
void draw_point(int x, int y, int player);
bool input(int player);
pairint searchp(void);
bool nextcheck(int x, int y, int p[23][23]);
bool searchp6(int a, int b, int c, int d, int e, int f, int p[23][23], int i, int j);
int searchpl6tot(int a, int b, int c, int d, int e, int f, int p[23][23]);
bool valid_input(int a, int b, int player);
bool searchpl(int a, int b, int c, int d, int e, int p[23][23], int i, int j);
bool searchpl2(int a, int b, int c, int d, int e, int p[23][23], int i, int j);
bool searchcet(int a, int b, int c, int d, int e, int p[23][23], int i, int j);
int search(int a, int b, int c, int d, int e, int p[23][23]);
pairint searchp(void);
int aiinput(void);
void you_win(void);
void you_lose(void);
int endcheck(void);
void inigame(void);
bool quit_game(void);
bool plate_file_exist(void);
bool read_select(void);
void clear_file();
void read_save();
void judg(void);
void saved(void);
void infgame(void)
{
	outtextxy(95, 175, _T("INSTRUCTIONS:     "));
	outtextxy(95, 205, _T(" press mousewheel for more information "));
	outtextxy(95, 235, _T(" press right mouse button to exit / save "));
	Sleep(5000);
	cleardevice();
}
void black_white(void)
{
	outtextxy(115, 175, _T("NOW CHOOSE BLACK OR WHITE"));
	outtextxy(135, 205, _T(" press right button for white "));
	outtextxy(135, 235, _T(" press left button for black "));
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		int a, b;
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			first_player = 1;
			cleardevice();
			return;
		}
		if (m.uMsg == WM_RBUTTONDOWN)
		{
			first_player = 2;
			cleardevice();
			return;
		}
	}
}
void draw_line()
{
	setlinecolor(WHITE);
	for (int x = 15; x < 450; x += 30)
		line(x, 15, x, 435);
	for (int y = 15; y < 450; y += 30)
		line(15, y, 435, y);
}
int pn(int t)
{
	return t / 30 + 4;
}
void draw_point(int x, int y, int player)
{
	plate[x][y] = player;
	x -= 4;
	y -= 4;
	setfillcolor(WHITE);
	fillcircle(x * 30 + 15, y * 30 + 15, 13);
	if (player == 2 && first_player == 1)
		setfillcolor(WHITE);
	if (player == 1 && first_player == 1)
		setfillcolor(BLACK);
	if (player == 1 && first_player == 2)
		setfillcolor(WHITE);
	if (player == 2 && first_player == 2)
		setfillcolor(BLACK);
	fillcircle(x * 30 + 15, y * 30 + 15, 12);
}
pairint searchp(void)
{
	pairint d;
	d.x = 11;
	d.y = 11;
	bool a = true;
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (plate[i][j] != 0)
			{
				a = false;
			}
		}
	}
	if (a)
		return d;
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl(0, 2, 2, 2, 2, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchcet(2, 2, 0, 2, 2, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl2(2, 0, 2, 2, 2, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl(0, 1, 1, 1, 1, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl2(1, 0, 1, 1, 1, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchcet(1, 1, 0, 1, 1, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl(0, 1, 1, 1, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl(0, 2, 2, 2, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl2(1, 0, 1, 1, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchcet(1, 1, 0, 1, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl(0, 2, 2, 2, 1, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl(0, 1, 1, 1, 2, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchcet(0, 2, 0, 2, 2, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchcet(0, 1, 0, 1, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchcet(0, 2, 0, 2, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl2(0, 0, 2, 2, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl2(0, 0, 1, 1, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl2(0, 0, 2, 2, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				if (searchpl2(0, 0, 2, 0, 0, plate, i, j))
				{
					d.x = i;
					d.y = j;
					return d;
				}
			}
		}
	}
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (nextcheck(i, j, plate) && plate[i][j] == 0 && valid_input(i, j, 2))
			{
				d.x = i;
				d.y = j;
				return d;
			}
		}
	}
}
bool nextcheck(int x, int y, int p[23][23])
{
	if (first_player == 2)
		return (p[x + 1][y + 1] + p[x + 1][y] + p[x + 1][y - 1] + p[x][y + 1] + p[x][y - 1] + p[x - 1][y + 1] + p[x - 1][y] + p[x - 1][y - 1]) && valid_input(x, y, 2);
	else
		return (p[x + 1][y + 1] + p[x + 1][y] + p[x + 1][y - 1] + p[x][y + 1] + p[x][y - 1] + p[x - 1][y + 1] + p[x - 1][y] + p[x - 1][y - 1]);
}
bool searchp6(int a, int b, int c, int d, int e, int f, int p[23][23], int i, int j)
{
	if (p[i][j] == a && p[i][j + 1] == b && p[i][j + 2] == c && p[i][j + 3] == d && p[i][j + 4] == e && p[i][j + 5] == f)
		return true;
	if (p[i][j] == a && p[i + 1][j] == b && p[i + 2][j] == c && p[i + 3][j] == d && p[i + 4][j] == e && p[i + 5][j] == f)
		return true;
	if (p[i][j] == a && p[i + 1][j + 1] == b && p[i + 2][j + 2] == c && p[i + 3][j + 3] == d && p[i + 4][j + 4] == e && p[i + 5][j + 5] == f)
		return true;
	if (p[i][j] == a && p[i + 1][j - 1] == b && p[i + 2][j - 2] == c && p[i + 3][j - 3] == d && p[i + 4][j - 4] == e && p[i + 5][j - 5] == f)
		return true;
	if (p[i][j] == a && p[i][j - 1] == b && p[i][j - 2] == c && p[i][j - 3] == d && p[i][j - 4] == e && p[i][j - 5] == f)
		return true;
	if (p[i][j] == a && p[i - 1][j] == b && p[i - 2][j] == c && p[i - 3][j] == d && p[i - 4][j] == e && p[i - 5][j] == f)
		return true;
	if (p[i][j] == a && p[i - 1][j - 1] == b && p[i - 2][j - 2] == c && p[i - 3][j - 3] == d && p[i - 4][j - 4] == e && p[i - 5][j - 5] == f)
		return true;
	if (p[i][j] == a && p[i - 1][j + 1] == b && p[i - 2][j + 2] == c && p[i - 3][j + 3] == d && p[i - 4][j + 4] == e && p[i - 5][j + 5] == f)
		return true;
	return false;
}
int search(int a, int b, int c, int d, int e, int p[23][23])
{
	int times = 0;
	for (int i = 4; i < 19; ++i)
	{
		for (int j = 4; j < 19; ++j)
		{
			if (p[i][j] == a && p[i][j + 1] == b && p[i][j + 2] == c && p[i][j + 3] == d && p[i][j + 4] == e)
				++times;
			if (p[i][j] == a && p[i + 1][j] == b && p[i + 2][j] == c && p[i + 3][j] == d && p[i + 4][j] == e)
				++times;
			if (p[i][j] == a && p[i + 1][j + 1] == b && p[i + 2][j + 2] == c && p[i + 3][j + 3] == d && p[i + 4][j + 4] == e)
				++times;
			if (p[i][j] == a && p[i + 1][j - 1] == b && p[i + 2][j - 2] == c && p[i + 3][j - 3] == d && p[i + 4][j - 4] == e)
				++times;
			if (p[i][j] == a && p[i][j - 1] == b && p[i][j - 2] == c && p[i][j - 3] == d && p[i][j - 4] == e)
				++times;
			if (p[i][j] == a && p[i - 1][j] == b && p[i - 2][j] == c && p[i - 3][j] == d && p[i - 4][j] == e)
				++times;
			if (p[i][j] == a && p[i - 1][j - 1] == b && p[i - 2][j - 2] == c && p[i - 3][j - 3] == d && p[i - 4][j - 4] == e)
				++times;
			if (p[i][j] == a && p[i - 1][j + 1] == b && p[i - 2][j + 2] == c && p[i - 3][j + 3] == d && p[i - 4][j + 4] == e)
				++times;
		}
	}
	return times;
}
bool searchpl(int a, int b, int c, int d, int e, int p[23][23], int i, int j)
{
	if (p[i][j] == a && p[i][j + 1] == b && p[i][j + 2] == c && p[i][j + 3] == d && p[i][j + 4] == e)
		return true;
	if (p[i][j] == a && p[i + 1][j] == b && p[i + 2][j] == c && p[i + 3][j] == d && p[i + 4][j] == e)
		return true;
	if (p[i][j] == a && p[i + 1][j + 1] == b && p[i + 2][j + 2] == c && p[i + 3][j + 3] == d && p[i + 4][j + 4] == e)
		return true;
	if (p[i][j] == a && p[i + 1][j - 1] == b && p[i + 2][j - 2] == c && p[i + 3][j - 3] == d && p[i + 4][j - 4] == e)
		return true;
	if (p[i][j] == a && p[i][j - 1] == b && p[i][j - 2] == c && p[i][j - 3] == d && p[i][j - 4] == e)
		return true;
	if (p[i][j] == a && p[i - 1][j] == b && p[i - 2][j] == c && p[i - 3][j] == d && p[i - 4][j] == e)
		return true;
	if (p[i][j] == a && p[i - 1][j - 1] == b && p[i - 2][j - 2] == c && p[i - 3][j - 3] == d && p[i - 4][j - 4] == e)
		return true;
	if (p[i][j] == a && p[i - 1][j + 1] == b && p[i - 2][j + 2] == c && p[i - 3][j + 3] == d && p[i - 4][j + 4] == e)
		return true;
	return false;
}
bool searchpl2(int a, int b, int c, int d, int e, int p[23][23], int i, int j)
{
	if (p[i][j] == b && p[i][j + 1] == c && p[i][j + 2] == d && p[i][j + 3] == e && p[i][j - 1] == a)
		return true;
	if (p[i][j] == b && p[i + 1][j] == c && p[i + 2][j] == d && p[i + 3][j] == e && p[i - 1][j] == a)
		return true;
	if (p[i][j] == b && p[i + 1][j + 1] == c && p[i + 2][j + 2] == d && p[i + 3][j + 3] == e && p[i - 1][j - 1] == a)
		return true;
	if (p[i][j] == b && p[i + 1][j - 1] == c && p[i + 2][j - 2] == d && p[i + 3][j - 3] == e && p[i - 1][j + 1] == a)
		return true;
	if (p[i][j] == b && p[i][j - 1] == c && p[i][j - 2] == d && p[i][j - 3] == e && p[i][j + 1] == a)
		return true;
	if (p[i][j] == b && p[i - 1][j] == c && p[i - 2][j] == d && p[i - 3][j] == e && p[i + 1][j] == a)
		return true;
	if (p[i][j] == b && p[i - 1][j - 1] == c && p[i - 2][j - 2] == d && p[i - 3][j - 3] == e && p[i + 1][j + 1] == e)
		return true;
	if (p[i][j] == b && p[i - 1][j + 1] == c && p[i - 2][j + 2] == d && p[i - 3][j + 3] == e && p[i + 1][j - 1] == e)
		return true;
	return false;
}
bool searchcet(int a, int b, int c, int d, int e, int p[23][23], int i, int j)
{

	if (p[i][j - 2] == a && p[i][j - 1] == b && p[i][j] == c && p[i][j + 1] == d && p[i][j + 2] == e)
		return true;
	if (p[i - 2][j] == a && p[i - 1][j] == b && p[i][j] == c && p[i + 1][j] == d && p[i + 2][j] == e)
		return true;
	if (p[i - 2][j - 2] == a && p[i - 1][j - 1] == b && p[i][j] == c && p[i + 1][j + 1] == d && p[i + 2][j + 2] == e)
		return true;
	if (p[i - 2][j + 2] == a && p[i - 1][j + 1] == b && p[i][j] == c && p[i + 1][j - 1] == d && p[i + 2][j - 2] == e)
		return true;
	return false;
}
int searchpl6tot(int a, int b, int c, int d, int e, int f, int p[23][23])
{
	int t = 0;
	for (int i = 5; i < 18; ++i)
	{
		for (int j = 5; j < 18; ++j)
		{
			if (searchp6(a, b, c, d, e, f, p, i, j))
				++t;
		}
	}
	return t;
}
bool valid_input(int a, int b, int player)
{
	int m = player;
	int n = m == 1 ? 2 : 1;
	if (player == 2 && first_player == 1)
		return true;
	int ptem[23][23] = { 0 };
	for (int i = 0; i < 23; ++i)
	{
		for (int j = 0; j < 23; ++j)
		{
			ptem[i][j] = plate[i][j];
		}
	}
	ptem[a][b] = player;
	float sansan = 0;
	sansan += 0.9 * searchpl6tot(0, m, 0, m, m, 0, ptem);
	sansan += 0.4 * searchpl6tot(0, 0, m, m, m, 0, ptem);
	if (sansan > 1)
		return false;
	float sisi = 0;
	sisi += 0.9 * searchpl6tot(n, m, m, m, m, 0, ptem);
	sisi += 0.4 * searchpl6tot(0, m, m, m, m, 0, ptem);
	sisi += 0.4 * searchpl6tot(0, m, m, 0, m, m, ptem);
	sisi += 0.4 * searchpl6tot(n, m, m, 0, m, m, ptem);
	sisi += 0.9 * searchpl6tot(m, m, m, 0, m, 0, ptem);
	sisi += 0.9 * searchpl6tot(m, m, m, 0, m, n, ptem);
	cout << sansan << sisi;
	if (sisi > 1)
		return false;
	int changlian = 0;
	changlian += searchpl6tot(m, m, m, m, m, m, ptem);
	if (changlian)
		return false;
	return true;
}
bool input(int player)
{
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		int a, b;
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			a = m.x;
			b = m.y;
			if (0 <= a && a <= 480 && 0 <= b && b <= 480)
			{
				if (plate[pn(a)][pn(b)] == 0&&valid_input(pn(a),pn(b),player))
				{
					draw_point(pn(a), pn(b), player);
					return true;
				}
			}
		}
		if (m.uMsg == WM_RBUTTONDOWN)
		{
			cleardevice();
			if (quit_game())
			{
				closegraph();
				return false;
			}
			else
			{
				cleardevice();
				draw_line();
				for (int i = 4; i < 19; ++i)
				{
					for (int j = 4; j < 19; ++j)
					{
						if (plate[i][j] != 0)
						{
							draw_point(i, j, plate[i][j]);
						}
					}
				}
				continue;
			}
		}
		if (m.uMsg == WM_MBUTTONDOWN)
		{
			cleardevice();
			saved();
			cleardevice();
			draw_line();
			for (int i = 4; i < 19; ++i)
			{
				for (int j = 4; j < 19; ++j)
				{
					if (plate[i][j] != 0)
					{
						draw_point(i, j, plate[i][j]);
					}
				}
			}
			continue;
		}
	}
}
bool quit_game(void)
{
	outtextxy(135, 175, _T("  ARE YOU SURE TO QUIT? "));
	outtextxy(90, 205, _T("[LEFT MOUSE BUTTON]  : QUIT AND SAVE"));
	outtextxy(90, 225, _T("[MIDDLE MOUSE BUTTON]: QUIT ONLY"));
	outtextxy(90, 245, _T("[RIGHT MOUSE BUTTON] : CONTINUE GAME"));
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			cleardevice();
			outtextxy(135, 225, _T("              SAVING...   "));
			ofstream file;
			file.open("plate.csv");
			for (int i = 0;i < 23;++i)
			{
				for (int j = 0;j < 23;++j)
				{
					file << plate[i][j];
					if (j < 22)
						file << ",";
				}
				file << endl;
			}
			file.close();
			int storedNum1, storedNum2;
			std::ifstream inFile("godata.txt");
			if (inFile.is_open())
			{
				// 从文件中读取两个整数
				inFile >> storedNum1 >> storedNum2;
				inFile.close();
			}
			else
			{
				storedNum1 = 0;
				storedNum2 = 0;
			}
			int sum1 = storedNum1 + win;
			int sum2 = storedNum2 + lose;
			std::ofstream outFile("godata.txt");
			if (outFile.is_open())
			{
				outFile << sum1 << " " << sum2 << std::endl;
				outFile.close();
			}
			Sleep(300);
			return true;
		}
		if (m.uMsg == WM_RBUTTONDOWN)
		{
			cleardevice();
			return false;
		}
		if (m.uMsg == WM_MBUTTONDOWN)
		{
			cleardevice();
			return true;
		}
	}
}
int aiinput(void)
{
	pairint p = searchp();
	int x = p.x;
	int y = p.y;
	draw_point(x, y, 2);
	return 0;
}
void you_win(void)
{
	win++;
	Sleep(4000);
	cleardevice();
	outtextxy(135, 205, _T("           YOU WIN !       "));
	Sleep(3000);
	cleardevice();
}
void you_lose(void)
{
	lose++;
	Sleep(4000);
	cleardevice();
	outtextxy(135, 205, _T("           YOU LOSE !       "));
	Sleep(3000);
	cleardevice();
}
void inigame(void)
{
	for (int i = 0; i < 23; ++i)
	{
		for (int j = 0; j < 23; ++j)
		{
			plate[i][j] = 0;
		}
	}
}
int endcheck(void)
{
	for (int a = 1; a < 3; ++a)
	{
		for (int i = 4; i < 19; ++i)
		{
			for (int j = 4; j < 19; ++j)
			{
				if (plate[i][j] == a && plate[i][j + 1] == a && plate[i][j + 2] == a && plate[i][j + 3] == a && plate[i][j + 4] == a)
					return a;
				if (plate[i][j] == a && plate[i + 1][j] == a && plate[i + 2][j] == a && plate[i + 3][j] == a && plate[i + 4][j] == a)
					return a;
				if (plate[i][j] == a && plate[i + 1][j + 1] == a && plate[i + 2][j + 2] == a && plate[i + 3][j + 3] == a && plate[i + 4][j + 4] == a)
					return a;
				if (plate[i][j] == a && plate[i + 1][j - 1] == a && plate[i + 2][j - 2] == a && plate[i + 3][j - 3] == a && plate[i + 4][j - 4] == a)
					return a;
			}
		}
	}
	return 0;
}
bool plate_file_exist(void)
{
	const string& name = "plate.csv";
	ifstream f(name.c_str());
	return f.good();
}
void clear_file()
{
	remove("plate.csv");
}
bool read_select(void)
{
	outtextxy(130, 185, _T("CONTINUE PREVIOUS GAME?"));
	outtextxy(130, 215, _T("[LEFT MOUSE BUTTON]   : YES"));
	outtextxy(130, 245, _T("[RIGHT MOUSE BUTTON] : NO"));
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			cleardevice();
			return true;
		}
		if (m.uMsg == WM_RBUTTONDOWN)
		{
			cleardevice();
			return false;
		}
	}
}
void read_save()
{
	ifstream file("plate.csv");
	string line;
	int row = 0;
	while (getline(file, line) && row < 23)
	{
		stringstream lineStream(line);
		string cell;
		int col = 0;
		while (getline(lineStream, cell, ',') && col < 23)
		{
			plate[row][col] = std::stoi(cell);
			col++;
		}
		row++;
	}
	file.close();
}
void judg(void)
{
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < 23; ++i)
	{
		for (int j = 0; j < 23; ++j)
		{
			if (plate[i][j] == 1)
				++count1;
			if (plate[i][j] == 2)
				++count2;
		}
	}
	if (count1 == count2)
	{
		first_player = 1;
		return;
	}
	else
	{
		first_player = 2;
		return;
	}
}
void saved(void)
{
	int storedNum1, storedNum2;
	std::ifstream inFile("godata.txt");
	if (inFile.is_open())
	{
		// 从文件中读取两个整数
		inFile >> storedNum1 >> storedNum2;
		inFile.close();
	}
	else
	{
		storedNum1 = 0;
		storedNum2 = 0;
	}
	int sum1 = storedNum1 + win;
	int sum2 = storedNum2 + lose;
	std::ofstream outFile("godata.txt");
	if (outFile.is_open())
	{
		outFile << sum1 << " " << sum2 << std::endl;
		outFile.close();
	}
	cleardevice();
	TCHAR s[30];
	_stprintf_s(s, _T("%d"), sum1);
	TCHAR r[30];
	_stprintf_s(r, _T("%d"), sum2);
	outtextxy(165, 185, _T("HISTORY RECORDS:      "));
	outtextxy(155, 235, _T("  player : "));
	outtextxy(245, 235, s);
	outtextxy(270, 235, _T("wins"));
	outtextxy(155, 255, _T("    AI   : "));
	outtextxy(245, 255, r);
	outtextxy(270, 255, _T("wins"));
	outtextxy(115, 405, _T(" 五子棋 programmed by xiaoyou"));
	Sleep(5000);
	cleardevice();
}
int main(void)
{
	initgraph(450, 450);
	outtextxy(165, 205, _T("  LETS PLAY GO!      "));
	Sleep(2000);
	cleardevice();
	infgame();
	int game_count = 0;
	while (true)
	{
		++game_count;
		if (game_count == 1 && plate_file_exist())
		{
			if (read_select())
			{
				read_save();
				judg();
				cleardevice();
				draw_line();
				for (int i = 4; i < 19; ++i)
				{
					for (int j = 4; j < 19; ++j)
					{
						if (plate[i][j] != 0)
						{
							draw_point(i, j, plate[i][j]);
						}
					}
				}
				while (true)
				{
					if (!input(1))
						return 0;
					if (endcheck() == 1)
					{
						you_win();
						break;
					}
					aiinput();
					if (endcheck() == 2)
					{
						you_lose();
						break;
					}
				}
				Sleep(200);
				clear_file();
				cleardevice();
			}
			else
			{
				continue;
			}
		}
		else
		{
			inigame();
			black_white();
			Sleep(300);
			draw_line();
			Sleep(1000);
			if (first_player == 1)
			{
				while (true)
				{
					if (!input(1))
						return 0;
					if (endcheck() == 1)
					{
						you_win();
						break;
					}
					aiinput();
					if (endcheck() == 2)
					{
						you_lose();
						break;
					}
				}
			}
			else
			{
				while (true)
				{
					aiinput();
					if (endcheck() == 2)
					{
						you_lose();
						break;
					}
					if (!input(1))
						return 0;
					if (endcheck() == 1)
					{
						you_win();
						break;
					}
				}
			}
			inigame();
		}
	}
}