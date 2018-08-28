#include "custom.h"		// includes
#include "game.h"
#include "monsters.h"
#include <string>
#include <fstream>

// make my life easier
using namespace std;

// Loading functions
void customGuide(char(*customGArray)[80]) // uses pointer so we can touch the array from another cpp file
{
	// create string and ifstream
	string LineData;
	ifstream MapDataFile;

	// open file
	MapDataFile.open("CMap_User_Guide.txt");

	//getline(MapDataFile, LineData);
	//getline(MapDataFile, LineData);

	// "scans" the whole file and assigns characters to the array for custom map editor USER GUIDE
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

	// close file
	MapDataFile.close();
}

// almost same as previous, except opening different file and array being opened
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
// need to use '&' to touch the game state and bounce time from another file
void userGLogic(double &g_dBounceTime, double g_dElapsedTime, bool g_abKeyPressed[], enum EGAMESTATES &g_eGameState)
{
	// use the function from the framework to help us prevent infinite input
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// if press TAB, go back to the custom map editor
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

// need to use pointer and '&' to touch the array and character location
void customKeyReg(bool g_abKeyPressed[], struct SGameChar &g_sChar, char(*customArray)[80])
{
	// a bunch of key presses to register and input the character to the coordinates
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
	// including left and right shift to get more characters
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

// function for player dying to monster in custom map mode
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
	// cleans the array and reset variables
	clearMonsters(myArray);
	spawnedOrNot = 0;
	button0 = 0;
	button2 = 0;
	button4 = 0;
	button6 = 0;
	button8 = 0;
	monsterRenderOrNot = 0;

	// change game state back to the editor
	g_eGameState = S_CUSTOM;
}

// movement for character is less limited in the custom editor than in normal levels so we have to make a new function.
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

// main logic
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
	// again function from framework
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// move character and register keys
	customMoveCharacter(customArray, g_dBounceTime, g_dElapsedTime, g_abKeyPressed, g_sChar, g_Console);
	customKeyReg(g_abKeyPressed, g_sChar, customArray);

	// escape returns user to title screen
	if (g_abKeyPressed[K_ESCAPE])
	{
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	// spacebar saves and simulates the level
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

		// load the customArray into myArray for using in the S_GAME state
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				myArray[i][j] = customArray[i][j];
			}
		}
		// spawns monsters
		getMonsterXYType(myArray);
		g_eGameState = S_GAME;
	}

	// reveals the user guide
	if (g_abKeyPressed[K_TAB])
	{
		bSomethingHappened = true;
		g_eGameState = S_USERG;
	}

	// disables collision (more specifically, sets the value of hax to work with the collision function)
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
	// normal declarations
	COORD c;

	for (unsigned int row = 0; row < 27; row++)
	{
		// get the c.Y
		c.Y = row;

		for (unsigned int column = 0; column < 80; column++)
		{
			// get the c.X
			c.X = column;

			// detect different characters and render
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

void customRender(char(*customArray)[80], class Console &g_Console)
{
	// same
	COORD c;

	// render in raw state
	for (unsigned int row = 0; row < 27; row++)
	{
		c.Y = row;

		for (unsigned int column = 0; column < 80; column++)
		{
			c.X = column;
			// player will see the txt file in the "pure" state
			g_Console.writeToBuffer(c, customArray[c.Y][c.X], FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
	}
	// render the character on top of everything else
	renderCharacter();
}

