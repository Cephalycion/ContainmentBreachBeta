#include "custom.h"
#include "game.h"
#include "monsters.h"
#include <string>
#include <fstream>

using namespace std;

// Loading functions
void customGuide(char(*customGArray)[80])
{
	string LineData;
	ifstream MapDataFile;

	MapDataFile.open("CMap_User_Guide.txt");

	//getline(MapDataFile, LineData);
	//getline(MapDataFile, LineData);

	for (unsigned int row = 0; row < 27; ++row)
	{
		if (!getline(MapDataFile, LineData))
		{
			break;
		}

		for (unsigned int column = 0; column < 80; ++column)
		{
			customGArray[row][column] = (char)LineData[column];
		}
	}
	MapDataFile.close();
}

void customLoading(char(*customArray)[80])
{
	string LineData;
	ifstream MapDataFile;

	MapDataFile.open("CMap_Template.txt");

	//getline(MapDataFile, LineData);
	//getline(MapDataFile, LineData);

	for (unsigned int row = 0; row < 27; ++row)
	{
		if (!getline(MapDataFile, LineData))
		{
			break;
		}

		for (unsigned int column = 0; column < 80; ++column)
		{
			customArray[row][column] = (char)LineData[column];
		}
	}
	MapDataFile.close();
}

// Logic functions
void userGLogic(double &g_dBounceTime, double g_dElapsedTime, bool g_abKeyPressed[], enum EGAMESTATES &g_eGameState)
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_TAB])
	{
		bSomethingHappened = true;
		g_eGameState = S_CUSTOM;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
}

void customKeyReg(bool g_abKeyPressed[], struct SGameChar &g_sChar, char (*customArray)[80])
{
	if (g_abKeyPressed[K_0])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '0';
	}
	if (g_abKeyPressed[K_1])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '1';
	}
	if (g_abKeyPressed[K_2])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '2';
	}
	if (g_abKeyPressed[K_3])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '3';
	}
	if (g_abKeyPressed[K_4])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '4';
	}
	if (g_abKeyPressed[K_5])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '5';
	}
	if (g_abKeyPressed[K_6])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '6';
	}
	if (g_abKeyPressed[K_7])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '7';
	}
	if (g_abKeyPressed[K_8])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '8';
	}
	if (g_abKeyPressed[K_9])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '9';
	}
	if (((g_abKeyPressed[K_2]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_2]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '@';
	}
	if (((g_abKeyPressed[K_3]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_3]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '#';
	}
	if (((g_abKeyPressed[K_4]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_4]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '$';
	}
	if (((g_abKeyPressed[K_5]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_5]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '%';
	}
	if (((g_abKeyPressed[K_6]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_6]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '^';
	}
	if (g_abKeyPressed[K_MINUS])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '-';
	}
	if (((g_abKeyPressed[K_PLUS]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_PLUS]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '+';
	}
	else if (g_abKeyPressed[K_PLUS])
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '=';
	}
	if (((g_abKeyPressed[K_COMMA]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_COMMA]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '<';
	}
	if (((g_abKeyPressed[K_PERIOD]) && (g_abKeyPressed[K_RSHIFT])) ||
		((g_abKeyPressed[K_PERIOD]) && (g_abKeyPressed[K_LSHIFT])))
	{
		customArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = '>';
	}
}

void customEndingReg(
	char(*myArray)[80], 
	int &spawnedOrNot, 
	bool &button0, 
	bool &button2, 
	bool &button4, 
	bool &button6, 
	bool &button8, 
	int &monsterRenderOrNot,
	enum EGAMESTATES &g_eGameState
)  // links S_GAME to S_CUSTOM from custom map maker.
{
	clearMonsters(myArray);
	spawnedOrNot = 0;
	button0 = 0;
	button2 = 0;
	button4 = 0;
	button6 = 0;
	button8 = 0;
	monsterRenderOrNot = 0;

	g_eGameState = S_CUSTOM;
}

void customMoveCharacter(
	char(*customArray)[80],
	double &g_dBounceTime,
	double g_dElapsedTime,
	bool g_abKeyPressed[],
	struct SGameChar &g_sChar,
	class Console &g_Console
)
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenever we shift the character
	if ((g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0) &&
		customArray[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '_')
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 &&
		customArray[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '_')
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE])
	{
		; // removed code due to lack of use in the game (pending future implementation)
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.1; // 125ms should be enough
	}
}

void customLogic(
	double &g_dBounceTime, 
	double g_dElapsedTime, 
	bool g_abKeyPressed[], 
	enum EGAMESTATES &g_eGameState,
	char(*customArray)[80],
	char(*myArray)[80],
	bool &hax,
	struct SGameChar &g_sChar,
	class Console &g_Console
)
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	customMoveCharacter(customArray, g_dBounceTime, g_dElapsedTime, g_abKeyPressed, g_sChar, g_Console);
	customKeyReg(g_abKeyPressed, g_sChar, customArray);

	if (g_abKeyPressed[K_ESCAPE])
	{
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	if (g_abKeyPressed[K_SPACE])
	{
		bSomethingHappened = true;

		// save the contents of customArray into the txt file
		ofstream custom;
		custom.open("CMap_Template.txt");

		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				custom << customArray[i][j];
			}
			custom << "\n";
		}
		custom.close();

		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				myArray[i][j] = customArray[i][j];
			}
		}
		getMonsterXYType(myArray);
		g_eGameState = S_GAME;
	}

	if (g_abKeyPressed[K_TAB])
	{
		bSomethingHappened = true;
		g_eGameState = S_USERG;
	}

	if ((g_abKeyPressed[K_HAX]))
	{
		bSomethingHappened = true;

		if (hax == false)
		{
			hax = true;
		}
		else
		{
			hax = false;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
}

// Render functions
void customGRender(char(*customGArray)[80], class Console &g_Console)
{
	COORD c;

	for (unsigned int row = 0; row < 27; row++)
	{
		c.Y = row;

		for (unsigned int column = 0; column < 80; column++)
		{
			c.X = column;

			switch (customGArray[c.Y][c.X])
			{
			case '#':
				g_Console.writeToBuffer(c, customGArray[c.Y][c.X], 0x00);
				break;
			case '!':
				g_Console.writeToBuffer(c, '#', FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			default:
				g_Console.writeToBuffer(c, customGArray[c.Y][c.X], FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			}
		}
	}
}

void customRender(char (*customArray)[80], class Console &g_Console)
{
	COORD c;

	// render in raw state
	for (unsigned int row = 0; row < 27; row++)
	{
		c.Y = row;

		for (unsigned int column = 0; column < 80; column++)
		{
			c.X = column;
			g_Console.writeToBuffer(c, customArray[c.Y][c.X], FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
	}

	renderCharacter();
}

