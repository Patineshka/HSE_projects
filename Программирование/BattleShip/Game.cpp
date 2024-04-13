#include "Game.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <math.h>


/*
  A B C D E F G H I J     A B C D E F G H I J
 *- - - - - - - - - -*   *- - - - - - - - - -*
0|                   |  0|                   |
1|                   |  1|                   |
2|                   |  2|                   |
3|                   |  3|                   |
4|                   |  4|                   |
5|                   |  5|                   |
6|                   |  6|                   |
7|                   |  7|                   |
8|                   |  8|                   |
9|                   |  9|                   |
 *- - - - - - - - - -*   *- - - - - - - - - -*
*/
char draw_symbol[EFIELD_INFO_END] =
{
        ' ' //EMPTY
        ,'*'//SHOT
        ,'X'//STRIKE
        ,'#'//KILL
        ,'&'//SHIP
        ,'^'//SHELL
};

//----------------------------------------------------------------
const char* FIELD[] =
{
        "  A B C D E F G H I J     A B C D E F G H I J "
        ," *- - - - - - - - - -*   *- - - - - - - - - -*"
        ,"0|                   |  0|                   |"
        ,"1|                   |  1|                   |"
        ,"2|                   |  2|                   |"
        ,"3|                   |  3|                   |"
        ,"4|                   |  4|                   |"
        ,"5|                   |  5|                   |"
        ,"6|                   |  6|                   |"
        ,"7|                   |  7|                   |"
        ,"8|                   |  8|                   |"
        ,"9|                   |  9|                   |"
        ," *- - - - - - - - - -*   *- - - - - - - - - -*"
};

//----------------------------------------------------------------
void draw_field(eFieldInfo* ap_data, eFieldInfo* ap_dataP, unsigned short a_target, int tmp, char* opponentName)
{
    printf("Your field:              %s's field:\n", opponentName);
    printf("%s\n", FIELD[0]);
    printf("%s\n", FIELD[1]);
    int index = 0;
    unsigned char target_x = 0;
    unsigned char target_y = 0;
    target_x = a_target;
    target_y = a_target >> 8;

    for (int i = 0; i < 10; ++i)
    {
        printf("%c%c", FIELD[i + 2][0], FIELD[i + 2][1]);
        index = 0;
        for (int j = 0; j < FIELD_SIZE; ++j) //������� ���� 1
        {
            if (j % 2 == 0)
            {
                printf("%c", draw_symbol[ap_data[i * 10 + index]]);
                index++;
            }
            else
                printf(" ");
        }
        for (int j = 21; j < 26; ++j)
            printf("%c", FIELD[i + 2][j]);
        index = 0;
        for (int j = 0; j < FIELD_SIZE; ++j) //������� ���� 2
        {
            if (j % 2 == 0)
            {
                if (i == target_y && j == target_x)
                {
                    printf("%c", TARGET);
                }
                else
                    printf("%c", draw_symbol[ap_dataP[i * 10 + index]]);
                index++;
            }
            else
                printf(" ");
            //if (i == target_y && j == target_x)
            //	printf("%c", TARGET);
            /*else
            {
                if (j % 2 == 0)
                {
                    printf("%c", draw_symbol[ap_dataP[i * 10 + index]]);
                    index++;
                }
                else
                    printf(" ");
            }*/
        }
        printf("%c\n", FIELD[2][45]);

    }
    printf("%s\n", FIELD[N_LINSE - 1]);
}
//----------------------------------------------------------------
void ship_generate(eFieldInfo* ap_data, struct BOAT* boat) //�������� ��������� ������ �������������� � ���� ����������� �������: i*n+j (i-�����, n-������ �������(����� �����), j-�������)
{
	srand(time(NULL));
	int a, i, j, k, l, b, c;
	int p = 0;
	//char ap_data[100]; ------------
	a = (rand()) % 10;
	b = (rand()) % 10;
	c = (rand()) % 10;

	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 10; i++)
		{
			ap_data[j * 10 + i] = EMPTY;

		}
	}
	//=========================================================
	if (b % 2 == 0)  //4palub goriz
	{

		for (j = 0; j < 10; j++)
		{
			if (j == c)
			{
				if (a < 7)
				{
					for (i = a; i < a + 4; i++)
					{
						ap_data[j * 10 + i] = SHIP;

						for (k = j - 1; k < j + 2; k++)
						{
							for (l = i - 1; l < i + 2; l++)
							{
								if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
								{
									ap_data[k * 10 + l] = SHELL;
								}
							}
						}
					}
					boat[p].numberOfDescks = 4;
					boat[p].regulation = 1;
					for (int v = 0; v < 4; v++) {
						boat[p].coordinates[v][0] = a + v; // x
						boat[p].coordinates[v][1] = c;// y
					}
					p++;
				}
				else
				{
					for (i = a - 4; i < a; i++)
					{
						ap_data[j * 10 + i] = SHIP;

						for (k = j - 1; k < j + 2; k++)
						{
							for (l = i - 1; l < i + 2; l++)
							{
								if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
								{
									ap_data[k * 10 + l] = SHELL;
								}
							}
						}
					}
					boat[p].numberOfDescks = 4;
					boat[p].regulation = 1;
					for (int v = 0; v < 4; v++) {
						boat[p].coordinates[v][0] = a - 4 + v; // x
						boat[p].coordinates[v][1] = c;// y
					}
					p++;

				}


			}
		}
	}
	else  //4palub vert
	{
		if (c < 7)
		{
			for (j = c; j < c + 4; j++)
			{
				for (i = 0; i < 10; i++)
				{
					if (i == a)
					{
						ap_data[j * 10 + i] = SHIP;
						for (k = j - 1; k < j + 2; k++)
						{
							for (l = i - 1; l < i + 2; l++)
							{
								if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
								{
									ap_data[k * 10 + l] = SHELL;
								}
							}
						}

					}
				}
				boat[p].numberOfDescks = 4;
				boat[p].regulation = 2;
				for (int v = 0; v < 4; v++) {
					boat[p].coordinates[v][0] = a; // x
					boat[p].coordinates[v][1] = c + v;// y
				}
				p++;

			}
		}
		else
		{
			for (j = c - 4; j < c; j++)
			{
				for (i = 0; i < 10; i++)
				{
					if (i == a)
					{
						ap_data[j * 10 + i] = SHIP;
						for (k = j - 1; k < j + 2; k++)
						{
							for (l = i - 1; l < i + 2; l++)
							{
								if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
								{
									ap_data[k * 10 + l] = SHELL;
								}
							}
						}
					}
				}
				boat[p].numberOfDescks = 4;
				boat[p].regulation = 2;
				for (int v = 0; v < 4; v++) {
					boat[p].coordinates[v][0] = a; // x
					boat[p].coordinates[v][1] = c - 4 + v;// y
				}
				p++;
			}
		}
	}
	//=========================================================
	for (int t = 0; t < 2; t++)
	{
		a = (rand()) % 10;
		b = (rand()) % 10;
		c = (rand()) % 10;
		if (a % 2 == 0)  //3palub goriz
		{
			if (c < 7)
			{
				while (ap_data[b * 10 + c] == SHIP || ap_data[b * 10 + c] == SHELL || ap_data[b * 10 + c + 1] == SHIP || ap_data[b * 10 + c + 1] == SHELL || ap_data[b * 10 + c + 2] == SHIP || ap_data[b * 10 + c + 2] == SHELL)
				{
					b = (rand()) % 10;
					c = (rand()) % 7;
				}
			}
			else
			{
				while (ap_data[b * 10 + c - 1] == SHIP || ap_data[b * 10 + c - 1] == SHELL || ap_data[b * 10 + c - 2] == SHIP || ap_data[b * 10 + c - 2] == SHELL || ap_data[b * 10 + c - 3] == SHIP || ap_data[b * 10 + c - 3] == SHELL)
				{
					b = (rand()) % 10;
					c = 9 - ((rand()) % 3);
				}
			}
			for (j = 0; j < 10; j++)
			{
				if (j == b)
				{
					if (c < 7)
					{
						for (i = c; i < c + 3; i++)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
						boat[p].numberOfDescks = 3;
						boat[p].regulation = 1;
						for (int v = 0; v < 3; v++) {
							boat[p].coordinates[v][0] = c + v; // x
							boat[p].coordinates[v][1] = b;// y
						}
						p++;
					}
					else
					{
						for (i = c - 3; i < c; i++)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
						boat[p].numberOfDescks = 3;
						boat[p].regulation = 1;
						for (int v = 0; v < 3; v++) {
							boat[p].coordinates[v][0] = c - 3 + v; // x
							boat[p].coordinates[v][1] = b;// y
						}
						p++;
					}


				}
			}
		}
		else  //3palub vert
		{
			if (b < 7)
			{
				while (ap_data[b * 10 + c] == SHIP || ap_data[b * 10 + c] == SHELL || ap_data[(b + 1) * 10 + c] == SHIP || ap_data[(b + 1) * 10 + c] == SHELL || ap_data[(b + 2) * 10 + c] == SHIP || ap_data[(b + 2) * 10 + c] == SHELL)
				{
					b = (rand()) % 7;
					c = (rand()) % 10;
				}
			}
			else
			{
				while (ap_data[(b - 1) * 10 + c] == SHIP || ap_data[(b - 1) * 10 + c] == SHELL || ap_data[(b - 2) * 10 + c] == SHIP || ap_data[(b - 2) * 10 + c] == SHELL || ap_data[(b - 3) * 10 + c] == SHIP || ap_data[(b - 3) * 10 + c] == SHELL)
				{
					b = 9 - ((rand()) % 3);
					c = (rand()) % 10;
				}
			}
			if (b < 7)
			{
				for (j = b; j < b + 3; j++)
				{
					for (i = 0; i < 10; i++)
					{
						if (i == c)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
					}
					boat[p].numberOfDescks = 3;
					boat[p].regulation = 2;
					for (int v = 0; v < 3; v++) {
						boat[p].coordinates[v][0] = c; // x
						boat[p].coordinates[v][1] = b + v;// y
					}
					p++;
				}
			}
			else
			{
				for (j = b - 3; j < b; j++)
				{
					for (i = 0; i < 10; i++)
					{
						if (i == c)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
					}
					boat[p].numberOfDescks = 3;
					boat[p].regulation = 2;
					for (int v = 0; v < 3; v++) {
						boat[p].coordinates[v][0] = c; // x
						boat[p].coordinates[v][1] = b - 3 + v;// y
					}
					p++;
				}
			}
		}
	}
	//=========================================================
	for (int t = 0; t < 3; t++)
	{
		a = (rand()) % 10;
		b = (rand()) % 10;
		c = (rand()) % 10;
		if (a % 2 == 0)  //2palub goriz
		{
			if (c < 9)
			{
				while (ap_data[b * 10 + c] == SHIP || ap_data[b * 10 + c] == SHELL || ap_data[b * 10 + c + 1] == SHIP || ap_data[b * 10 + c + 1] == SHELL)
				{
					b = (rand()) % 10;
					c = (rand()) % 9;
				}
			}
			else
			{
				while (ap_data[b * 10 + c - 1] == SHIP || ap_data[b * 10 + c - 1] == SHELL || ap_data[b * 10 + c - 2] == SHIP || ap_data[b * 10 + c - 2] == SHELL)
				{
					b = (rand()) % 10;
					c = 9;
				}
			}
			for (j = 0; j < 10; j++)
			{
				if (j == b)
				{
					if (c < 9)
					{
						for (i = c; i < c + 2; i++)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
						boat[p].numberOfDescks = 2;
						boat[p].regulation = 1;
						for (int v = 0; v < 2; v++) {
							boat[p].coordinates[v][0] = c + v; // x
							boat[p].coordinates[v][1] = b;// y
						}
						p++;
					}
					else
					{
						for (i = c - 2; i < c; i++)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
						boat[p].numberOfDescks = 2;
						boat[p].regulation = 1;
						for (int v = 0; v < 2; v++) {
							boat[p].coordinates[v][0] = c - 2 + v; // x
							boat[p].coordinates[v][1] = b;// y
						}
						p++;
					}


				}
			}
		}
		else  //2palub vert
		{
			if (b < 9)
			{
				while (ap_data[b * 10 + c] == SHIP || ap_data[b * 10 + c] == SHELL || ap_data[(b + 1) * 10 + c] == SHIP || ap_data[(b + 1) * 10 + c] == SHELL)
				{
					b = (rand()) % 9;
					c = (rand()) % 10;
				}
			}
			else
			{
				while (ap_data[(b - 1) * 10 + c] == SHIP || ap_data[(b - 1) * 10 + c] == SHELL || ap_data[(b - 2) * 10 + c] == SHIP || ap_data[(b - 2) * 10 + c] == SHELL)
				{
					b = 9;
					c = (rand()) % 10;
				}
			}
			if (b < 9)
			{
				for (j = b; j < b + 2; j++)
				{
					for (i = 0; i < 10; i++)
					{
						if (i == c)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
					}
					boat[p].numberOfDescks = 2;
					boat[p].regulation = 2;
					for (int v = 0; v < 2; v++) {
						boat[p].coordinates[v][0] = c; // x
						boat[p].coordinates[v][1] = b + v;// y
					}
					p++;
				}
			}
			else
			{
				for (j = b - 2; j < b; j++)
				{
					for (i = 0; i < 10; i++)
					{
						if (i == c)
						{
							ap_data[j * 10 + i] = SHIP;
							for (k = j - 1; k < j + 2; k++)
							{
								for (l = i - 1; l < i + 2; l++)
								{
									if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
									{
										ap_data[k * 10 + l] = SHELL;
									}
								}
							}
						}
					}
					boat[p].numberOfDescks = 2;
					boat[p].regulation = 2;
					for (int v = 0; v < 2; v++) {
						boat[p].coordinates[v][0] = c; // x
						boat[p].coordinates[v][1] = b - 2 + v;// y
					}
					p++;
				}
			}
		}
	}
	//=========================================================
	for (int t = 0; t < 4; t++)
	{
		b = (rand()) % 10;
		c = (rand()) % 10; //1palub
		while (ap_data[b * 10 + c] == SHIP || ap_data[b * 10 + c] == SHELL)
		{
			b = (rand()) % 10;
			c = (rand()) % 10;
		}
		ap_data[b * 10 + c] = SHIP;
		for (k = b - 1; k < b + 2; k++)
		{
			for (l = c - 1; l < c + 2; l++)
			{
				if (k >= 0 && l >= 0 && ap_data[k * 10 + l] != SHIP && k < 10 && l < 10)
				{
					ap_data[k * 10 + l] = SHELL;
				}
			}
		}
		boat[p].numberOfDescks = 1;
		boat[p].regulation = 2;
		boat[p].coordinates[0][0] = c; // x
		boat[p].coordinates[0][1] = b; // y
		p++;
	}
}
//----------------------------------------------------------------
unsigned char get_target_possition(unsigned char* ap_x, unsigned char* ap_y)
{
    int key = 0;
    key = _getch();
    switch (key)
    {
    case ARROW_KEY_PRESSED:
    {
        switch (_getch())
        {
        case KEY_DOWN:
        {
            if (*ap_y < 9)
                (*ap_y)++;
            return 0;
        }
        case KEY_UP:
        {
            if (*ap_y > 0)
                (*ap_y)--;
            return 0;
        }
        case KEY_RIGHT:
        {
            if (*ap_x < 19 - 1)
            {
                (*ap_x)++;
                (*ap_x)++;
            }

            return 0;
        }
        case KEY_LEFT:
        {
            if (*ap_x > 0)
            {
                (*ap_x)--;
                (*ap_x)--;
            }
            return 0;
        }
        }
    }
    case KEY_ENTER:
    {
        return 1;
    }
    }
}
//----------------------------------------------------------------
unsigned char shot_analiz(eFieldInfo* ap_dataP, eFieldInfo* ap_data, int x, int y, int* score, int tmp1)
{
    //i* n + j(i - �����, n - ������ �������(����� �����), j - �������)
    switch (ap_data[y * 10 + x])
    {
    case EMPTY:
    {
		if (tmp1 == 0)
			ap_dataP[y * 10 + x] = SHOT;
        ap_data[y * 10 + x] = SHOT;
        printf("YOU MISSED");
        return 0;
    }
    case SHOT:
    {
        printf("YOU'VE ALREADY SHOT HERE");
        return 1;
    }
    case STRIKE:
    {
        printf("YOU'VE ALREADY SHOT HERE");
        return 1;
    }
    case KILL:
    {
        printf("YOU'VE ALREADY SHOT HERE");
        return 1;
    }
    case SHIP:
    {
        ap_data[y * 10 + x] = STRIKE;
		if (tmp1 == 0)
			ap_dataP[y * 10 + x] = STRIKE;
        score[tmp1]++;
        printf("THERE IS A BREAKOUT");
        return 1;
    }
    case SHELL:
    {
		ap_data[y * 10 + x] = SHOT;
		if (tmp1 == 0)
			ap_dataP[y * 10 + x] = SHOT;
        printf("YOU MISSED");
        return 0;
    }
    }
}

unsigned char shotBOT_analiz(eFieldInfo* ap_data, int x, int y, int* score, int tmp1)
{
	switch (ap_data[y * 10 + x])
	{
	case EMPTY:
	{
		ap_data[y * 10 + x] = SHOT;
		printf("YOU MISSED");
		return 0;
	}
	case SHOT:
	{
		printf("YOU'VE ALREADY SHOT HERE");
		return 1;
	}
	case STRIKE:
	{
		printf("YOU'VE ALREADY SHOT HERE");
		return 1;
	}
	case KILL:
	{
		printf("YOU'VE ALREADY SHOT HERE");
		return 1;
	}
	case SHIP:
	{
		ap_data[y * 10 + x] = STRIKE;
		score[tmp1]++;
		printf("THERE IS A BREAKOUT");
		return 1;
	}
	case SHELL:
	{
		ap_data[y * 10 + x] = SHOT;
		printf("YOU MISSED");
		return 0;
	}
	}
}
//----------------------------------------------------------------
void analiz(eFieldInfo* ap_dataP1, eFieldInfo* ap_data1, int x, int y, struct BOAT* boat)
{
	//Y * n + X(Y - �����, n - ������ �������(����� �����), X - �������)
	int a = 0, b = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < boat[i].numberOfDescks; j++) {
			if (boat[i].coordinates[j][0] == x && boat[i].coordinates[j][1] == y) {
				boat[i].numberOfHits++;
				if (boat[i].numberOfHits == boat[i].numberOfDescks) {
					if (boat[i].regulation == 1) { //���� �������������
						a = boat[i].coordinates[0][0];
						b = boat[i].coordinates[0][1];
						for (a; a < boat[i].coordinates[0][0] + boat[i].numberOfDescks; a++) {
							ap_data1[b * 10 + a] = KILL;
						}
					}
					else { //�����������
						a = boat[i].coordinates[0][0];
						b = boat[i].coordinates[0][1];
						for (b; b < boat[i].coordinates[0][1] + boat[i].numberOfDescks; b++) {
							ap_data1[b * 10 + a] = KILL;
						}
					}
				}
			}
		}
	}

}

unsigned short BOT(int* sea, eFieldInfo* ap_data, int m, int a, int b)
{
	unsigned short shot_position = 0;
	srand(time(NULL));
	int v = 0;

	if (v == 0)
	{
		if (m == 1) 
		{
			if (b < 9)
			{
				if (sea[a * 10 + b + 1] == 0)
				{
					v = 1;
					shot_position = (a << 8) | (b + 1);
					return shot_position;
					if (ap_data[a * 10 + b + 1] == SHIP)
					{
						//s += 1;
						sea[a * 10 + b + 1] = 1;
						if (a < 9 && b < 8)
							sea[(a + 1) * 10 + b + 2] = 2;
						if (a > 0)
							sea[(a - 1) * 10 + b] = 2;
						if (a > 0 && b < 8)
							sea[(a - 1) * 10 + b + 2] = 2;
						if (a < 9)
							sea[(a + 1) * 10 + b] = 2;
						if (b < 8)
						{
							if (sea[a * 10 + b + 2] == 0)
								m = 2;
						}
						if (m != 2)
						{
							if (b > 0)
							{
								if (sea[a * 10 + b - 1] == 0)
									m = 7;
							}
						}
						if (m == 1)
							m = 0; //мы - двухпалубник
					}
					else
					{
						sea[a * 10 + b + 1] = 2;
					}
				}
			}
			if (v == 0 && b > 0)
			{
				if (sea[a * 10 + b - 1] == 0)
				{
					v = 1; 
					shot_position = (a << 8) | (b - 1);
					return shot_position;
					if (ap_data[a * 10 + b - 1] == SHIP)
					{
						//s += 1;
						sea[a * 10 + b - 1] = 1; 
						if (a < 9 && b > 1)
							sea[(a + 1) * 10 + b - 2] = 2;
						if (a > 0)
							sea[(a - 1) * 10 + b] = 2;
						if (a > 0 && b > 1)
							sea[(a - 1) * 10 + b - 2] = 2;
						if (a < 9)
							sea[(a + 1) * 10 + b] = 2;
						if (b > 1)
						{
							if (sea[a * 10 + b - 2] == 0)
								m = 3;
						}
						if (m != 3)
						{
							m = 0; //мы - двухпалубник
						}
					}
					else
					{
						sea[a * 10 + b - 1] = 2;
					}
				}
			}
			if (v == 0 && a > 0)
			{
				if (sea[(a - 1) * 10 + b] == 0)
				{
					v = 1; //ход уже сделан
					shot_position = ((a - 1) << 8) | (b);
					return shot_position;
					if (ap_data[(a - 1) * 10 + b] == SHIP)
					{
						//s += 1;
						sea[(a - 1) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
						if (b > 0)
							sea[a * 10 + b - 1] = 2;
						if (a > 1 && b < 9)
							sea[(a - 2) * 10 + b + 1] = 2;
						if (a > 1 && b > 0)
							sea[(a - 2) * 10 + b - 1] = 2;
						if (b < 9)
							sea[a * 10 + b + 1] = 2;
						if (a > 1)
						{
							if (sea[(a - 2) * 10 + b] == 0)
								m = 4;
						}
						if (m != 4)
						{
							if (a < 9)
							{
								if (sea[(a + 1) * 10 + b] == 0)
									m = 10;
							}
						}
						if (m == 1)
							m = 0; //мы - двухпалубник
					}
					else
					{
						sea[(a - 1) * 10 + b] = 2;
					}
				}
			}
			if (v == 0)
			{
				if (a < 9)
				{
					if (sea[(a + 1) * 10 + b] == 0)
					{
						v = 1; //ход уже сделан
						shot_position = ((a + 1) << 8) | (b);
						return shot_position;
						if (ap_data[(a + 1) * 10 + b] == SHIP)
						{
							//s += 1;
							sea[(a + 1) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
							if (a < 8 && b < 9)
								sea[(a + 2) * 10 + b + 1] = 2;
							if (b > 0)
								sea[a * 10 + b - 1] = 2;
							if (a < 8 && b > 0)
								sea[(a + 2) * 10 + b - 1] = 2;
							if (b < 9)
								sea[a * 10 + b + 1] = 2;
							if (a < 8)
							{
								if (sea[(a + 2) * 10 + b] == 0)
									m = 5;
							}
							if (m != 5)
							{
								m = 0; //мы - двухпалубник
							}
						}
						else
						{
							sea[(a + 1) * 10 + b] = 2;
							m = 0; //мы однопалубник
						}
					}
				}
			}
			if (v == 0)
				m = 0; //мы однопалубник
		}
	}
	if (v == 0)
	{
		if (m == 2)
		{
			v = 1; //ход уже сделан
			shot_position = (a << 8) | (b + 2);
			return shot_position;
			if (ap_data[a * 10 + b + 2] == SHIP)
			{
				//s += 1;
				sea[a * 10 + b + 2] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 9 && b < 7)
					sea[(a + 1) * 10 + b + 3] = 2;
				if (a > 0)
					sea[(a - 1) * 10 + b + 1] = 2;
				if (a > 0 && b < 7)
					sea[(a - 1) * 10 + b + 3] = 2;
				if (a < 9)
					sea[(a + 1) * 10 + b + 1] = 2;
				if (b < 7)
				{
					if (sea[a * 10 + b + 3] == 0)
					{
						m = 6;
					}
				}
				if (m != 6)
				{
					if (b > 0)
					{
						if (sea[a * 10 + b - 1] == 0)
							m = 7;
					}
				}
				if (m == 2)
				{
					m = 0; //мы трёхпалубник
				}
			}
			else
			{
				sea[a * 10 + b + 2] = 2;
				if (b > 0)
				{
					if (sea[a * 10 + b - 1] == 0)
						m = 7;
				}
				if (m == 2)
					m = 0; //мы двухпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 3)
		{
			v = 1; //ход уже сделан
			shot_position = (a << 8) | (b - 2);
			return shot_position;
			if (ap_data[a * 10 + b - 2] == SHIP)
			{
				//s += 1;
				sea[a * 10 + b - 2] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 9 && b > 2)
					sea[(a + 1) * 10 + b - 3] = 2;
				if (a > 0)
					sea[(a - 1) * 10 + b - 1] = 2;
				if (a > 0 && b > 2)
					sea[(a - 1) * 10 + b - 3] = 2;
				if (a < 9)
					sea[(a + 1) * 10 + b - 1] = 2;
				if (b > 2)
				{
					if (sea[a * 10 + b - 3] == 0)
					{
						m = 8;
					}
				}
				if (m != 8)
				{
					m = 0; //мы трёхпалубник
				}
			}
			else
			{
				sea[a * 10 + b - 2] = 2;
				m = 0; //мы двухпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 8)
		{
			v = 1;
			shot_position = (a << 8) | (b - 3);
			return shot_position;
			if (ap_data[a * 10 + b - 3] == SHIP)
			{
				sea[a * 10 + b - 3] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 9 && b > 3)
					sea[(a + 1) * 10 + b - 4] = 2;
				if (a > 0)
					sea[(a - 1) * 10 + b - 2] = 2;
				if (a > 0 && b > 3)
					sea[(a - 1) * 10 + b - 4] = 2;
				if (a < 9)
					sea[(a + 1) * 10 + b - 2] = 2;
				m = 0; //мы четырёхпалубник
			}
			else
			{
				sea[a * 10 + b - 3] = 2;
				m = 0; //мы трёхпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 6)
		{
			v = 1; //ход уже сделан
			shot_position = (a << 8) | (b + 3);
			return shot_position;
			if (ap_data[a * 10 + b + 3] == SHIP)
			{
				//s += 1;
				sea[a * 10 + b + 3] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 9 && b < 6)
					sea[(a + 1) * 10 + b + 4] = 2;
				if (a > 0)
					sea[(a - 1) * 10 + b + 2] = 2;
				if (a > 0 && b < 6)
					sea[(a - 1) * 10 + b + 4] = 2;
				if (a < 9)
					sea[(a + 1) * 10 + b + 2] = 2;
				m = 0; //мы четырёхпалубник
				if (b < 6)
					sea[a * 10 + b + 4] = 2;
				if (b > 0)
					sea[a * 10 + b - 1] = 2;
			}
			else
			{
				sea[a * 10 + b + 3] = 2;
				if (b > 0)
				{
					if (sea[a * 10 + b - 1] == 0)
						m = 7;
				}
				if (m != 7)
					m = 0; //мы трёхпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 7)
		{
			v = 1;
			shot_position = (a << 8) | (b - 1);
			return shot_position;
			if (ap_data[a * 10 + b - 1] == SHIP)
			{
				sea[a * 10 + b - 1] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 9 && b > 1)
					sea[(a + 1) * 10 + b - 2] = 2;
				if (a > 0)
					sea[(a - 1) * 10 + b] = 2;
				if (a > 0 && b > 1)
					sea[(a - 1) * 10 + b - 2] = 2;
				if (a < 9)
					sea[(a + 1) * 10 + b] = 2;
				if (b < 8)
				{
					if (sea[a * 10 + b + 2] == 1)
						m = 0;
				}
				if (m != 0)
					m = 12;
				else if (b > 1)
					sea[a * 10 + b - 2] = 2;
			}
			else
			{
				sea[a * 10 + b - 1] = 2;
				m = 0;
			}
		}
	}
	if (v == 0)
	{
		if (m == 4)
		{
			v = 1; //ход уже сделан
			shot_position = ((a - 2) << 8) | (b);
			return shot_position;
			if (ap_data[(a - 2) * 10 + b] == SHIP)
			{
				//s += 1;
				sea[(a - 2) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a > 2 && b < 9)
					sea[(a - 3) * 10 + b + 1] = 2;
				if (b > 0)
					sea[(a - 1) * 10 + b - 1] = 2;
				if (a > 2 && b > 0)
					sea[(a - 3) * 10 + b - 1] = 2;
				if (b < 9)
					sea[(a - 1) * 10 + b + 1] = 2;
				if (a > 2)
				{
					if (sea[(a - 3) * 10 + b] == 0)
					{
						m = 9;
					}
				}
				if (m != 9)
				{
					if (a < 9)
					{
						if (sea[(a + 1) * 10 + b] == 0)
							m = 10;
					}
				}
				if (m == 4)
				{
					m = 0; //мы трёхпалубник
				}
			}
			else
			{
				sea[(a - 2) * 10 + b] = 2;
				if (a < 9)
				{
					if (sea[(a + 1) * 10 + b] == 0)
						m = 10;
				}
				if (m == 4)
					m = 0; //мы двухпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 9)
		{
			v = 1; //ход уже сделан
			shot_position = ((a - 3) << 8) | (b);
			return shot_position;
			if (ap_data[(a - 3) * 10 + b] == SHIP)
			{
				//s += 1;
				sea[(a - 3) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a > 3 && b < 9)
					sea[(a - 4) * 10 + b + 1] = 2;
				if (b > 0)
					sea[(a - 2) * 10 + b - 1] = 2;
				if (a > 3 && b > 0)
					sea[(a - 4) * 10 + b - 1] = 2;
				if (b < 9)
					sea[(a - 2) * 10 + b + 1] = 2;
				m = 0; //мы четырёхпалубник
				if (a > 3)
					sea[(a - 4) * 10 + b] = 2;
				if (a < 9)
					sea[(a + 1) * 10 + b] = 2;
			}
			else
			{
				sea[(a - 3) * 10 + b] = 2;
				if (a < 9)
				{
					if (sea[(a + 1) * 10 + b] == 0)
						m = 10;
				}
				if (m != 10)
					m = 0; //мы трёхпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 10)
		{
			v = 1;
			shot_position = ((a + 1) << 8) | (b);
			return shot_position;
			if (ap_data[(a + 1) * 10 + b] == SHIP)
			{
				sea[(a + 1) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 8 && b > 0)
					sea[(a + 2) * 10 + b - 1] = 2;
				if (b > 0)
					sea[a * 10 + b - 1] = 2;
				if (b < 9)
					sea[a * 10 + b + 1] = 2;
				if (a < 8 && b < 9)
					sea[(a + 2) * 10 + b + 1] = 2;
				if (a > 1)
				{
					if (sea[(a - 2) * 10 + b] == 1)
						m = 0;
				}
				if (m != 0)
					m = 13;
				else if (a < 8)
					sea[(a + 2) * 10 + b] = 2;

			}
			else
			{
				sea[(a + 1) * 10 + b] = 2;
				m = 0;
			}
		}
	}
	if (v == 0)
	{
		if (m == 5)
		{
			v = 1; //ход уже сделан
			shot_position = ((a + 2) << 8) | (b);
			return shot_position;
			if (ap_data[(a + 2) * 10 + b] == SHIP)
			{
				//s += 1;
				sea[(a + 2) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 7 && b > 0)
					sea[(a + 3) * 10 + b - 1] = 2;
				if (b > 0)
					sea[(a + 1) * 10 + b - 1] = 2;
				if (a < 7 && b < 9)
					sea[(a + 3) * 10 + b + 1] = 2;
				if (b < 9)
					sea[(a + 1) * 10 + b + 1] = 2;
				if (a < 7)
				{
					if (sea[(a + 3) * 10 + b] == 0)
					{
						m = 11;
					}
				}
				if (m != 11)
				{
					m = 0; //мы трёхпалубник
				}
			}
			else
			{
				sea[(a + 2) * 10 + b] = 2;
				m = 0; //мы двухпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 11)
		{
			v = 1;
			shot_position = ((a + 3) << 8) | (b);
			return shot_position;
			if (ap_data[(a + 3) * 10 + b] == SHIP)
			{
				sea[(a + 3) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 6 && b > 0)
					sea[(a + 4) * 10 + b - 1] = 2;
				if (b > 0)
					sea[(a + 2) * 10 + b - 1] = 2;
				if (b < 9)
					sea[(a + 2) * 10 + b + 1] = 2;
				if (a < 6 && b < 9)
					sea[(a + 4) * 10 + b + 1] = 2;
				if (a < 6)
					sea[(a + 4) * 10 + b] = 2;
				m = 0; //мы четырёхпалубник
			}
			else
			{
				sea[(a + 3) * 10 + b] = 2;
				m = 0; //мы трёхпалубник
			}
		}
	}
	if (v == 0)
	{
		if (m == 12)
		{
			v = 1;
			shot_position = (a << 8) | (b - 2);
			return shot_position;
			if (ap_data[a * 10 + b - 2] == SHIP)
			{
				sea[a * 10 + b - 2] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 9 && b > 2)
					sea[(a + 1) * 10 + b - 3] = 2;
				if (a > 0)
					sea[(a - 1) * 10 + b - 1] = 2;
				if (a > 0 && b > 2)
					sea[(a - 1) * 10 + b - 3] = 2;
				if (a < 9)
					sea[(a + 1) * 10 + b - 1] = 2;
				if (b > 2)
					sea[a * 10 + b - 3] = 2;
				m = 0;
			}
			else
			{
				sea[a * 10 + b - 2] = 2;
				m = 0;
			}
		}
	}
	if (v == 0)
	{
		if (m == 13)
		{
			v = 1;
			shot_position = ((a + 2) << 8) | (b);
			return shot_position;
			if (ap_data[(a + 2) * 10 + b] == SHIP)
			{
				sea[(a + 2) * 10 + b] = 1; //точно пусто в угловых (если они есть, конечно)
				if (a < 7 && b > 0)
					sea[(a + 3) * 10 + b - 1] = 2;
				if (b > 0)
					sea[(a + 1) * 10 + b - 1] = 2;
				if (b < 9)
					sea[(a + 1) * 10 + b + 1] = 2;
				if (a < 7 && b < 9)
					sea[(a + 3) * 10 + b + 1] = 2;
				if (a < 7)
					sea[(a + 3) * 10 + b] = 2;
				m = 0;
			}
			else
			{
				sea[(a + 2) * 10 + b] = 2;
				m = 0;
			}
		}
	}
	if (v == 0)
	{
		if (m == 0) 
		{
			v = 1;
			a = (rand()) % 10;
			b = (rand()) % 10;
			while (sea[a * 10 + b] != 0)
			{
				a = (rand()) % 10;
				b = (rand()) % 10;
			}
			shot_position = (a << 8) | (b);
			return shot_position;
			if (ap_data[a * 10 + b] == SHIP)
			{
				//s++;
				sea[a * 10 + b] = 1;
				if (a < 9 && b < 9)
				{
					sea[(a + 1) * 10 + b + 1] = 2;
					if (a > 0 && b > 0)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (a > 0)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (b > 0)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0)
							m = 1;
					}
					else
					{
						if (sea[a * 10 + b + 1] == 0 || sea[(a + 1) * 10 + b] == 0)
							m = 1;
					}
				}
				if (a > 0 && b > 0)
				{
					sea[(a - 1) * 10 + b - 1] = 2;
					if (a < 9 && b < 9)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (a < 9)
					{
						if (sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (b < 9)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else
					{
						if (sea[a * 10 + b - 1] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
				}
				if (a > 0 && b < 9)
				{
					sea[(a - 1) * 10 + b + 1] = 2;
					if (a < 9 && b > 0)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (a < 9)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (b > 0)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else
					{
						if (sea[a * 10 + b + 1] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
				}
				if (a < 9 && b > 0)
				{
					sea[(a + 1) * 10 + b - 1] = 2;
					if (a > 0 && b < 9)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (a > 0)
					{
						if (sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0 || sea[(a - 1) * 10 + b] == 0)
							m = 1;
					}
					else if (b < 9)
					{
						if (sea[a * 10 + b + 1] == 0 || sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0)
							m = 1;
					}
					else
					{
						if (sea[a * 10 + b - 1] == 0 || sea[(a + 1) * 10 + b] == 0)
							m = 1;
					}
				}
			}
			else
			{
				sea[a * 10 + b] = 2;
				//s++;
			}
		}
	}
}