#include "monsters.h"

SMapMonster monsterList[50];

//0 Down 1 Up 2 Left 3 Right
//Function for moving monsters up and down
void moveUpDownMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80])
{
	switch (monster.m_iDirection)
	{
	case 0:
		if (myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] != '#')
		{
			monster.m_cLocation.Y++;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 1;
		}
		break;
	case 1:
		if (myArray[monster.m_cLocation.Y - 1][monster.m_cLocation.X] != '#')
		{
			monster.m_cLocation.Y--;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 0;
		}
		break;
	case 4:
		if (myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] != '#')
		{
			monster.m_iDirection = 0;
		}
		else
		{
			monster.m_iDirection = 1;
		}
		break;
	}
}

//Function for moving monsters left and right
void moveLeftRightMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80])
{
	switch (monster.m_iDirection)
	{
	case 2:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] != '#')
		{
			monster.m_cLocation.X--;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 3;
		}
		break;
	case 3:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X + 1] != '#')
		{
			monster.m_cLocation.X++;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 2;
		}
		break;
	case 4:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] != '#')
		{
			monster.m_iDirection = 2;
		}
		else
		{
			monster.m_iDirection = 3;
		}
		break;
	}
}

//Function for moving monsters clockwise
void moveClockwiseMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80])
{
	switch (monster.m_iDirection)
	{
	case 0:
		if (myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] != '#')
		{
			monster.m_cLocation.Y++;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 2;
		}
		break;
	case 1:
		if (myArray[monster.m_cLocation.Y - 1][monster.m_cLocation.X] != '#')
		{
			monster.m_cLocation.Y--;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 3;
		}
		break;
	case 2:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] != '#')
		{
			monster.m_cLocation.X--;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 1;
		}
		break;
	case 3:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X + 1] != '#')
		{
			monster.m_cLocation.X++;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 0;
		}
		break;
	case 4:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] == '#' && myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] == '#')
		{
			monster.m_iDirection = 1;
		}
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] == '#' && myArray[monster.m_cLocation.Y - 1][monster.m_cLocation.X] == '#')
		{
			monster.m_iDirection = 3;
		}
		if (myArray[monster.m_cLocation.Y - 1][monster.m_cLocation.X] == '#' && myArray[monster.m_cLocation.Y][monster.m_cLocation.X + 1] == '#')
		{
			monster.m_iDirection = 0;
		}
		if (myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] == '#' && myArray[monster.m_cLocation.Y][monster.m_cLocation.X + 1] == '#')
		{
			monster.m_iDirection = 2;
		}
		break;
	}
}

//Function for moving monsters anticlockwise
void moveAntiClockwiseMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80])
{
	switch (monster.m_iDirection)
	{
	case 0:
		if (myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] != '#')
		{
			monster.m_cLocation.Y++;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 3;
		}
		break;
	case 1:
		if (myArray[monster.m_cLocation.Y - 1][monster.m_cLocation.X] != '#')
		{
			monster.m_cLocation.Y--;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 2;
		}
		break;
	case 2:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] != '#')
		{
			monster.m_cLocation.X--;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 0;
		}
		break;
	case 3:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X + 1] != '#')
		{
			monster.m_cLocation.X++;
			somethingHappened = true;
		}
		else
		{
			monster.m_iDirection = 1;
		}
		break;
	case 4:
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] == '#' && myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] == '#')
		{
			monster.m_iDirection = 3;
		}
		if (myArray[monster.m_cLocation.Y][monster.m_cLocation.X - 1] == '#' && myArray[monster.m_cLocation.Y - 1][monster.m_cLocation.X] == '#')
		{
			monster.m_iDirection = 0;
		}
		if (myArray[monster.m_cLocation.Y - 1][monster.m_cLocation.X] == '#' && myArray[monster.m_cLocation.Y][monster.m_cLocation.X + 1] == '#')
		{
			monster.m_iDirection = 2;
		}
		if (myArray[monster.m_cLocation.Y + 1][monster.m_cLocation.X] == '#' && myArray[monster.m_cLocation.Y][monster.m_cLocation.X + 1] == '#')
		{
			monster.m_iDirection = 1;
		}
		break;
	}
}

void getMonsterXYType(char(*myArray)[80])
{
	int i = 0;

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			switch (myArray[y][x])
			{
			case '+':
				monsterList[i].m_cLocation.Y = y;
				monsterList[i].m_cLocation.X = x;
				monsterList[i].m_cType = '+';
				monsterList[i].m_iDirection = 4;
				i++;
				break;
			case '=':
				monsterList[i].m_cLocation.Y = y;
				monsterList[i].m_cLocation.X = x;
				monsterList[i].m_cType = '=';
				monsterList[i].m_iDirection = 4;
				i++;
				break;
			case '$':
				monsterList[i].m_cLocation.Y = y;
				monsterList[i].m_cLocation.X = x;
				monsterList[i].m_cType = '$';
				monsterList[i].m_iDirection = 4;
				i++;
				break;
			case '%':
				monsterList[i].m_cLocation.Y = y;
				monsterList[i].m_cLocation.X = x;
				monsterList[i].m_cType = '%';
				monsterList[i].m_iDirection = 4;
				i++;
			}
		}
	}
}

void clearMonsters(char(*myArray)[80])
{
	for (int i = 0; i < 50; i++)
	{
		monsterList[i].m_cLocation = { 0, };
		monsterList[i].m_iDirection = 0;
		monsterList[i].m_cType = 0;
	}

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			myArray[i][j] = 0;
		}
	}
}

void renderMonsters(class Console &g_Console)
{
	WORD monsterColor = FOREGROUND_RED;
	for (int i = 0; i < 50; i++)
	{
		g_Console.writeToBuffer(monsterList[i].m_cLocation, (char)219, monsterColor);
	}
}

void moveMonsters(char(*myArray)[80], double &g_dMonsterTime, double g_dElapsedTime)
{
	bool bSomethingHappened = false;
	if (g_dMonsterTime > g_dElapsedTime)
		return;

	for (int i = 0; i < 50; i++)
	{
		switch (monsterList[i].m_cType)
		{
		case '+':
			moveUpDownMonster(monsterList[i], bSomethingHappened, myArray);
			break;
		case '=':
			moveLeftRightMonster(monsterList[i], bSomethingHappened, myArray);
			break;
		case '$':
			moveClockwiseMonster(monsterList[i], bSomethingHappened, myArray);
			break;
		case '%':
			moveAntiClockwiseMonster(monsterList[i], bSomethingHappened, myArray);
			break;
		}

		if (bSomethingHappened)
		{
			g_dMonsterTime = g_dElapsedTime + 0.1;
		}
	}
}