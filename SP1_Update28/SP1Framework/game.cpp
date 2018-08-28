// This is the main file for the game logic and function
//
//
#include "game.h"
#include "monsters.h"
#include "custom.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std; // don't really know the consequences

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
SGameChar	g_sSelectort;	// selector for title screen
SGameChar	g_sSelectorl;	// selector for level select screen

EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime;				// this is to prevent key bouncing, so we won't trigger keypresses more than once
double  g_dMonsterTime;				// for monster
int monsterRenderOrNot = 0;

// for Jeremiah's minigame
vector<int> sequence;				// vector for sequence for minigame
int redTrue, blueTrue, yellowTrue, greenTrue = 2; // for showing the values of the vector in the interface
int indicatorTrue = 1;				// to check if indicator should be red or green
int currentIndex = 0;				// to slowly check array of sequence
double g_dScanTime;					// to have delay for displaying in minigame
int sequenceNumber = 0;				// to display number showing
int inputState = 0;					// for minigame to enter the input state
double g_dSequenceTime;				// to prevent key bouncing when entering input for sequence
int inputSequence[8];				// to store player's inputs
int inputIndex = 0;					// index to save into inputSequence
int miniGameCorrectOrNot = 0;       // check if minigame is correct
double g_dDelayDisplayTime;			// to show players all lights dimmed
bool runMinigame = 0;				// to check if delay is over
bool bMinigameDelayed = 0;			// to make delay happen once only
double g_dButtonColorTime;          // for button to light up for a while
double g_dButtonResetTime;			// for buttons to reset before showing next sequence
bool bScan = false;                 // for function to recognise it should reset

// for Darren's minigame
char mistakes = '0';
char correctguesses = '0';
char currNum = '0';
char nextNum = '0';

// for Ian's minigame
char lefta;
char righta;
char upa;
char downa;
int slideGX;
int slideGY;
char intermediate = '(';

int whichMap = 0;					// to identify current map being played

char myArray[25][80] = { 0, };		// array version of the map
char splashArray[25][80] = { 0, };	// array version of splash screen
char customArray[27][80] = { 0, };	// array version of custom map
char customGArray[27][80] = { 0, };	// array version of custom map editor guide

char saveArray[6];					// stores data for loading and saving
int spawnedOrNot = 0;				// check if player spawned or not

// identify if button has been pressed or not
bool button0 = 0;
bool button2 = 0;
bool button4 = 0;
bool button6 = 0;
bool button8 = 0;

// all the map strings so there is less typing needed
string m0 = "Map_Tutorial.txt";
string m1 = "Map_01.txt";
string m2 = "Map_02.txt";
string m3 = "Map_03.txt";
string m4 = "Map_04.txt";
string m5 = "Map_05.txt";
string death = "death.txt";
string ending = "Game_end.txt";
string secret = "Game_end_2.txt";
string splash = "Splash_Screen.txt";
string custom = "CMap_Template.txt";
string title = "title.txt";
string mini = "Minigame.txt";
string miniGuide = "MinigameGuide.txt";
string highlow = "highorlow.txt";
string slidePuzzle = "slidepuzzle.txt";

// determines the choice of the selection in title and level select
int titleChoice = 0; // init to 0
int levelChoice = 0; // init to 0

// determines where dying to monsters will send to the player depending on whether the custom map is being used
bool isCustomOrNot = 0;

// toggles wall collision.
bool hax = 0;

// Console object
Console g_Console(80, 25, "SP1 Framework");

// plays music in a loop from .wav file
void playMusic()
{
	PlaySound(TEXT("Noxive_Home.wav"), NULL, SND_ASYNC | SND_LOOP);
}

// loads splash from txt file into an array
void splashLoading(string splashString)
{
	// get console size
	COORD c = g_Console.getConsoleSize();

	string splashData;
	ifstream splashDataFile;

	// open file
	splashDataFile.open(splashString);

	// skip 2 lines
	getline(splashDataFile, splashData);
	getline(splashDataFile, splashData);

	// "scan" the whole txt file and assign the characters to splashArray
	for (unsigned int row = 0; row < 25; ++row)
	{
		if (!getline(splashDataFile, splashData))
		{
			break;
		}

		for (unsigned int column = 0; column < 80; ++column)
		{
			splashArray[row][column] = (char)splashData[column];
		}
	}
	// close file
	splashDataFile.close();
}

// mapLoading function, used for loading majority of txt files within the game
// similar to splashLoading except with a different array
void mapLoading(string stringMap)
{
	string LineData;
	ifstream MapDataFile;

	MapDataFile.open(stringMap);

	getline(MapDataFile, LineData);
	getline(MapDataFile, LineData);

	for (unsigned int row = 0; row < 25; ++row)
	{
		if (!getline(MapDataFile, LineData))
		{
			break;
		}

		for (unsigned int column = 0; column < 80; ++column)
		{
			myArray[row][column] = (char)LineData[column];
		}
	}
	MapDataFile.close();
}

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
	
	// loads the splash from txt file to array
	splashLoading(splash);

	// set the starting point of the selector characters
	g_sSelectort.m_cLocation.Y = 9;
	g_sSelectort.m_cLocation.X = 31;

	g_sSelectorl.m_cLocation.Y = 7;
	g_sSelectorl.m_cLocation.X = 31;

	// loads the custom map user guide from txt file to array
	customGuide(customGArray);

	// plays music (universal throughout the game)
	playMusic();

	// to make rand random
	srand((unsigned int)time(NULL));
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{   
	// default keypress registers
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);

	// added on top of the framework; used for minigames and custom map builder
	g_abKeyPressed[K_RSHIFT]	= isKeyPressed(VK_RSHIFT);
	g_abKeyPressed[K_LSHIFT]	= isKeyPressed(VK_LSHIFT);
	g_abKeyPressed[K_0]			= isKeyPressed(0x30);
	g_abKeyPressed[K_1]			= isKeyPressed(0x31);
	g_abKeyPressed[K_2]			= isKeyPressed(0x32);
	g_abKeyPressed[K_3]			= isKeyPressed(0x33);
	g_abKeyPressed[K_4]			= isKeyPressed(0x34);
	g_abKeyPressed[K_5]			= isKeyPressed(0x35);
	g_abKeyPressed[K_6]			= isKeyPressed(0x36);
	g_abKeyPressed[K_7]			= isKeyPressed(0x37);
	g_abKeyPressed[K_8]			= isKeyPressed(0x38);
	g_abKeyPressed[K_9]			= isKeyPressed(0x39);
	g_abKeyPressed[K_PLUS]		= isKeyPressed(VK_OEM_PLUS);
	g_abKeyPressed[K_MINUS]		= isKeyPressed(VK_OEM_MINUS);
	g_abKeyPressed[K_COMMA]		= isKeyPressed(VK_OEM_COMMA);
	g_abKeyPressed[K_PERIOD]	= isKeyPressed(VK_OEM_PERIOD);
	g_abKeyPressed[K_TAB]		= isKeyPressed(VK_TAB);
	g_abKeyPressed[K_HAX]		= isKeyPressed(VK_OEM_3);

	// for Jeremiah's minigame
	g_abKeyPressed[K_N1] = isKeyPressed(VK_NUMPAD1);
	g_abKeyPressed[K_N2] = isKeyPressed(VK_NUMPAD2);
	g_abKeyPressed[K_N3] = isKeyPressed(VK_NUMPAD3);
	g_abKeyPressed[K_N4] = isKeyPressed(VK_NUMPAD4);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_ENDSCREEN: endLogic(); // logic for end screen (when player completes the game successfully)
			break;
		case S_SECRET: secretLogic(); // logic for secret reward scren
			break;
		case S_TITLE: titleLogic(); // logic for title
			break;
		case S_LEVELS: levelsLogic(); // logic for selection of levels
			break;
		case S_CUSTOM: customLogic( // logic for custom map editor (in another separate .cpp and .h file)
			g_dBounceTime,
			g_dElapsedTime,
			g_abKeyPressed,
			g_eGameState,
			customArray,
			myArray,
			hax,
			g_sChar,
			g_Console
		);
			break;
		case S_DEATH: deathLogic(); // game logic for the death screen
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_USERG: userGLogic(g_dBounceTime, g_dElapsedTime, g_abKeyPressed, g_eGameState); // logic for user guide screen
			break;
		case S_MINIGAME: minigameLogic(); // logic for minigame
			break;
		case S_MINIGUIDE: miniGuideLogic(); // logic for guide
			break;
		case S_HIGHORLOW: highorlow();
			break;
		case S_PUZZLE: slide();
			break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen(); // renders the splash screen
            break;
		case S_ENDSCREEN: endRender(); // renders the end screen
			break;
		case S_SECRET: endRender(); // don't really need another renderer for secret screen
			break;
		case S_DEATH: deathRender(); // renders death screen
			break;
		case S_TITLE: titleRender(); // renders title screen
			break;
		case S_LEVELS: levelsRender(); // renders level select screen
			break;
		case S_CUSTOM: customRender(customArray, g_Console); // renders the custom map editor
			break;
        case S_GAME: renderGame(); // render main game
            break;
		case S_USERG: customGRender(customGArray, g_Console); // renders custom map user guide
			break;
		case S_MINIGAME: renderMinigame(); // renders keypad puzzle
			break;
		case S_MINIGUIDE: renderMiniGuide(); // renders guide
			break;
		case S_HIGHORLOW: highorlowrender();
			break;
		case S_PUZZLE: slideRender();
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
	{
		splashLoading(title);
		g_eGameState = S_TITLE;
	}
}

void endLogic()
{
	// end game logic
	// bSomethingHappened is a variable from the framework that is useful for preventing infinite input
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// player can press esc to return to title screen and be a normal person
	if (g_abKeyPressed[K_ESCAPE])
	{
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	// or press spacebar and discover the highorlow minigame
	if (g_abKeyPressed[K_SPACE])
	{
		bSomethingHappened = true;
		mapLoading(highlow);
		currNum = rand() % 10 + 48;
		g_eGameState = S_HIGHORLOW;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
}

void secretLogic()
{
	// same again
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// press esc to return to title screen
	if (g_abKeyPressed[K_ESCAPE])
	{
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
}

void levelsLogic()
{
	// same again
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// update the saveArray with contents from the txt file
	string saveData;
	ifstream saveLoad("Saveload.txt");

	getline(saveLoad, saveData);

	for (int i = 0; i < 6; i++)
	{
		saveArray[i] = (char)saveData[i];
	}
	saveLoad.close();

	// moves the selector character and changes the value of levelChoice
	if ((g_abKeyPressed[K_DOWN]) && (levelChoice < 5))
	{
		levelChoice++;
		g_sSelectorl.m_cLocation.Y += 2;
		bSomethingHappened = true;
	}

	// moves the selector character and changes the value of levelChoice
	if ((g_abKeyPressed[K_UP]) && (levelChoice > 0))
	{
		levelChoice--;
		g_sSelectorl.m_cLocation.Y -= 2;
		bSomethingHappened = true;
	}

	// press esc to go back to title screen
	if (g_abKeyPressed[K_ESCAPE])
	{
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	// if the array says that the player has unlocked the next level, allow loading
	if ((g_abKeyPressed[K_SPACE]) && (saveArray[levelChoice] == '1'))
	{
		bSomethingHappened = true;
		whichMap = levelChoice;
		mapIdentifier();
		getMonsterXYType(myArray);
		g_eGameState = S_GAME;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
}

void titleLogic()
{
	// same again
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// use the value of 1 since there are only 2 choices (as of time of writing), 0 for level select and 1 for custom map editor.
	// moves the selector character and changes the value of titleChoice
	if ((g_abKeyPressed[K_DOWN]) && (titleChoice < 2)) 
	{
		titleChoice++;
		g_sSelectort.m_cLocation.Y += 2;
		bSomethingHappened = true;
	}

	// moves the selector character and changes the value of titleChoice
	if ((g_abKeyPressed[K_UP]) && (titleChoice > 0))
	{
		titleChoice--;
		g_sSelectort.m_cLocation.Y -= 2;
		bSomethingHappened = true;
	}

	// goes to level select screen
	if ((g_abKeyPressed[K_SPACE]) && (titleChoice == 0))
	{
		isCustomOrNot = 0;
		bSomethingHappened = true;
		g_eGameState = S_LEVELS;
	}

	// preps the custom map editor for use
	if ((g_abKeyPressed[K_SPACE]) && (titleChoice == 1))
	{
		// identify the isCustomOrNot so we can have a special action set
		isCustomOrNot = 1;
		bSomethingHappened = true;

		// load the custom map from root to the array
		customLoading(customArray);

		// sets character to center. Previously, we had bugs where character was displaced outside of boundaries.
		g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
		g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;

		// change game state
		g_eGameState = S_CUSTOM;
	}

	// preps the slide puzzle by Ian
	if ((g_abKeyPressed[K_SPACE]) && (titleChoice == 2))
	{
		isCustomOrNot = 0;
		bSomethingHappened = true;

		// load the slide puzzle from txt file to myArray
		mapLoading(slidePuzzle);

		// change game state
		g_eGameState = S_PUZZLE;
	}

	// press esc to quit the game
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
}

// logic for death screen
void deathLogic()
{
	// usual
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// press spacebar to respawn
	if (g_abKeyPressed[K_SPACE])
	{
		mapIdentifier();
		getMonsterXYType(myArray);
		bSomethingHappened = true;
		g_eGameState = S_GAME;
	}

	// press esc to return to title
	if (g_abKeyPressed[K_ESCAPE])
	{
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.1; // 125ms should be enough
	}
}

// resets game values used to default 
void deathReset()
{
	// clean the monsters in myArray
	clearMonsters(myArray);

	// the game now recognises the character as not spawned yet
	spawnedOrNot = 0;
	monsterRenderOrNot = 0;
	button0 = 0; // resets all buttons after death
	button2 = 0;
	button4 = 0;
	button6 = 0;
	button8 = 0;

	// change game state to the death state
	g_eGameState = S_DEATH;
}

void teleport() // one way teleporting from < to >
{
	if (myArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '<')
	{
		for (int row = 0; row < 25; row++)
		{
			for (int column = 0; column < 80; column++)
			{
				if (myArray[row][column] == '>')
				{
					g_sChar.m_cLocation.Y = row;
					g_sChar.m_cLocation.X = column;
				}
			}
		}
	}
}

void playerSpawn()
{
	if (spawnedOrNot == 0)
	{
		// find the '@' starting point of the player and spawn there
		for (int lesserno = 0; lesserno < 25; lesserno++)
		{
			for (int greaterno = 0; greaterno < 80; greaterno++)
			{
				if (myArray[lesserno][greaterno] == '@')
				{
					// set the x and y coordinates of the player to iteration of the forloop where it hits the '@'
					g_sChar.m_cLocation.X = greaterno;
					g_sChar.m_cLocation.Y = lesserno;
					// game now recognises the character as spawned 
					spawnedOrNot = 1;
				}
			}
		}
	}
	else
	{
		; // do nothing
	}

	// if its still not spawned (means no '@' in the map)
	if (spawnedOrNot == 0)
	{
		// set player position to center
		g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
		g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;

		// game now recognises the character as spawned 
		spawnedOrNot = 1;
	}
}

void buttonReg()
{
	// register buttons walked over
	switch (myArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X])
	{
	case '0':
		button0 = 1;
		break;
	case '2':
		button2 = 1;
		break;
	case '4':
		button4 = 1;
		break;
	case '6':
		button6 = 1;
		break;
	case '8':
		button8 = 1;
		break;
	default:
		break;
	}
}

// identifies the map from whichMap variable and loads it into myArray using the mapLoading function
void mapIdentifier()
{
	switch (whichMap)
	{
	case 0:
		mapLoading(m0);
		break;
	case 1:
		mapLoading(m1);
		break;
	case 2:
		mapLoading(m2);
		break;
	case 3:
		mapLoading(m3);
		break;
	case 4:
		mapLoading(m4);
		break;
	case 5:
		mapLoading(m5);
		break;
	case 6: // final map is the ending screen
		splashLoading(ending);
		g_eGameState = S_ENDSCREEN;
		break;
	default:
		break;
	}
}

void greenReg() // when the player hits the green tile, hence the name.
{
	// change the map when reach the end point '*'
	// reset the button states for reuse
	if (myArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '*')
	{
		// when player finishes a level, update the array
		saveArray[whichMap + 1] = '1';

		// and update the txt file with the new array
		if (whichMap < 5)
		{
			ofstream saveLoad("Saveload.txt");

			for (int i = 0; i < 6; i++)
			{
				saveLoad << saveArray[i];
			}

			saveLoad.close();
		}

		// clean monsters
		clearMonsters(myArray);
		
		// game recognises the player as not spawned
		spawnedOrNot = 0; 
		button0 = 0; //resets all buttons
		button2 = 0;
		button4 = 0;
		button6 = 0;
		button8 = 0;
		monsterRenderOrNot = 0; // game recognises the monster as not spawned

		if (whichMap == 5)
		{
			mapLoading(miniGuide);
			g_eGameState = S_MINIGUIDE;
			return;
		}
		else
		{
			whichMap++;
		}
		// load the map from whichMap
		mapIdentifier();
	}
}

void gameplay()         // gameplay logic
{
	playerSpawn();		// spawns the player

	// registers player death when touching monsters
	for (int i = 0; i < 50; i++)
	{
		// if the monster coordinates overlaps the player coordinates, trigger death actions
		if ((g_sChar.m_cLocation.Y == monsterList[i].m_cLocation.Y) &&
			(g_sChar.m_cLocation.X == monsterList[i].m_cLocation.X))
		{
			// if not custom map, do a normal death action
			if (isCustomOrNot == 0)
			{
				deathReset();
			}
			// else use the custom death action
			else
			{
				customEndingReg(
					myArray,
					spawnedOrNot,
					button0,
					button2,
					button4,
					button6,
					button8,
					monsterRenderOrNot,
					g_eGameState
					);
			}
		}
	}

	// if monster not rendered yet, get the XY coordinates and render them
	while (monsterRenderOrNot != 1)
	{
		getMonsterXYType(myArray);
		monsterRenderOrNot = 1; // game will then recognise the monsters as spawned
	}

	moveMonsters(myArray, g_dMonsterTime, g_dElapsedTime);     // moves monsters
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	teleport();			// one-way teleport mechanics
	buttonReg();		// register button presses
	greenReg();			// register if player has reached the end of a level

	// this if is for detecting a successful green tile touch in custom maps. Unlike normal maps which use '*',
	// custom maps use '^' to denote green tiles and hence can easily be configured for another action.
	if (myArray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '^') 
	{
		// pass to the custom ending function with parameters (right-click and go to definition for more details)
		customEndingReg(
			myArray,
			spawnedOrNot,
			button0, // resets buttons
			button2,
			button4,
			button6,
			button8,
			monsterRenderOrNot,
			g_eGameState
		);
	}
}

// player collision function (return 1 means player can move, return 0 means player cannot move)
int playerCollision(int Y, int X)
{
	if (((button0 == 1) && (myArray[Y][X] == '1')) ||// allows players to walk on hidden paths/doors after buttons are pressed
		((button2 == 1) && (myArray[Y][X] == '3')) ||
		((button4 == 1) && (myArray[Y][X] == '5')) ||
		((button6 == 1) && (myArray[Y][X] == '7')) ||
		((button8 == 1) && (myArray[Y][X] == '9')))
	{
		return 1;
	}

	if ((myArray[Y][X] == '0') ||
		(myArray[Y][X] == '2') ||
		(myArray[Y][X] == '4') ||
		(myArray[Y][X] == '6') ||
		(myArray[Y][X] == '8'))
	{
		return 1;
	}

	// if the player is not stepping on a wall or numbers (numbers are used to denote the buttons and paths),
	// return a 1.
	if (((myArray[Y][X] < '0') || (myArray[Y][X] > '9')) && (myArray[Y][X] != '#'))
	{
		return 1;
	}

	// if hax == true, return 1 no matter what. (hax is a hidden dev mode activated with the '~' key)
	if (hax == true)
	{
		return 1;
	}

	return 0;
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenever we shift the character

	// if player press UP key
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
		// send the future coordinates to the collision function
		if (playerCollision(g_sChar.m_cLocation.Y - 1, g_sChar.m_cLocation.X) == 1)
		{
			g_sChar.m_cLocation.Y--;
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
		if (playerCollision(g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X - 1) == 1)
		{
			g_sChar.m_cLocation.X--;
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
		if (playerCollision(g_sChar.m_cLocation.Y + 1, g_sChar.m_cLocation.X) == 1)
		{
			g_sChar.m_cLocation.Y++;
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
		if (playerCollision(g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X + 1) == 1)
		{
			g_sChar.m_cLocation.X++;
		}
        bSomethingHappened = true;
    }

  //  if (g_abKeyPressed[K_SPACE])
  //  {
		//; // removed code due to lack of use in the game involving movement
  //  }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.1; // 125ms should be enough
    }
}

void processUserInput()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// switches between true and false for hax variable with every key press of '~'
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

    // change to level select if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
	{
		spawnedOrNot = 0;
		button0 = 0;
		button2 = 0;
		button4 = 0;
		button6 = 0;
		button8 = 0;
		monsterRenderOrNot = 0;
		clearMonsters(myArray);
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	// change to custom map editor
	if ((g_abKeyPressed[K_SPACE]) && isCustomOrNot == 1)
	{
		spawnedOrNot = 0;
		button0 = 0;// resets buttons
		button2 = 0;
		button4 = 0;
		button6 = 0;
		button8 = 0;
		monsterRenderOrNot = 0;
		clearMonsters(myArray);
		bSomethingHappened = true;
		g_eGameState = S_CUSTOM;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.2;
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void endRender()
{
	renderSplashScreen(); // the renderer for the ending screen can use the same renderer as the splash screen due to similarities.
}

void levelsRender()
{
	// semi-hardcoded writing to buffer but very easy to write
	COORD c = g_Console.getConsoleSize();
	c.Y = 7;
	c.X = 33;
	g_Console.writeToBuffer(c, "TUTORIAL", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	c.Y += 2;
	g_Console.writeToBuffer(c, "LEVEL I", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	c.Y += 2;
	g_Console.writeToBuffer(c, "LEVEL II", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	c.Y += 2;
	g_Console.writeToBuffer(c, "LEVEL III", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	c.Y += 2;
	g_Console.writeToBuffer(c, "LEVEL IV", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	c.Y += 2;
	g_Console.writeToBuffer(c, "LEVEL V", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

	c.Y = 9;
	c.X = 44;

	// starts at 1 because the first container [0] is reserved for tutorial
	for (int i = 1; i < 6; i++)
	{
		if (saveArray[i] == '1')
		{
			g_Console.writeToBuffer(c, "UNLOCKED", FOREGROUND_GREEN);
		}
		else
		{
			g_Console.writeToBuffer(c, "LOCKED", FOREGROUND_RED);
		}
		c.Y += 2;
	}

	// render the selector
	g_Console.writeToBuffer(g_sSelectorl.m_cLocation, '>', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}

void titleRender()
{
	/*splashLoading(title);*/ // loading the splash screen (from txt file) has been moved to splashScreenWait()
	// so that the renderer is not opening and closing the txt file for every single frame
	renderSplashScreen();
	g_Console.writeToBuffer(g_sSelectort.m_cLocation, '>', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}

void deathRender()
{
	splashLoading(death); // load death txt file
	renderSplashScreen(); // render what is in the splashArray
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c;

	for (unsigned int row = 0; row < 25; row++)
	{
		c.Y = row;

		for (unsigned int column = 0; column < 80; column++)
		{
			c.X = column;

			// renders from the array instead of the txt file now
			switch (splashArray[c.Y][c.X])
			{
			case '#':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			case '-':
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			default:
				g_Console.writeToBuffer(c, splashArray[c.Y][c.X], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			}
		}
	}
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
	renderMonsters(g_Console);   // to render monsters
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;

	for (unsigned int row = 0; row < 25; ++row)
	{
		c.Y = row;

		// There is a better way to do this but we need the different characters to mark positions on the maps
		for (unsigned int column = 0; column < 80; ++column)
		{
			c.X = column;

			switch (myArray[c.Y][c.X])
			{
			case '#': // The walls
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			case '-': // The spacing
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '*': // The end point
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN);
				break;
			case '^': // The end point for custom map
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN);
				break;
			case '@': // The player start point
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '%': // The monster start point
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '+': // The monster start point
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '=': // The monster start point
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '$': // The monster start point
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '/': // The monster path
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '<': // The entry point for teleporters
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			case '[': // A usable visual clone of teleporter entry point so it can be used as an "inert" character in the txt file
				// used to explain the teleporter concept to players without affecting the teleporter logic
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			case '>': // The exit point for teleporters
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			case ']': // A usable visual clone of teleporter entry point so it can be used as an "inert" character in the txt file
				// used to explain the teleporter concept to players without affecting the teleporter logic
				g_Console.writeToBuffer(c, 219, FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			case '!': // A usable visual clone of the enemy
				g_Console.writeToBuffer(c, 219, FOREGROUND_RED);
				break;
			case '0': // purple button
				g_Console.writeToBuffer(c, 219, FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '1':
				if (button0 == 0) //not pressed then doors renders as black
				{
					g_Console.writeToBuffer(c, 219, 0x00);
				}
				else if (button0 == 1) // pressed then renders as white
				{
					g_Console.writeToBuffer(c, 219, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				break;
			case '3':
				if (button2 == 0)//not pressed then doors renders as black
				{
					g_Console.writeToBuffer(c, 219, 0x00);
				}
				else if (button2 == 1) // pressed then renders as white
				{
					g_Console.writeToBuffer(c, 219, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				break;
			case '5':
				if (button4 == 0)//not pressed then doors renders as black
				{
					g_Console.writeToBuffer(c, 219, 0x00);
				}
				else if (button4 == 1) // pressed then renders as white
				{
					g_Console.writeToBuffer(c, 219, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				break;
			case '7':
				if (button6 == 0)//not pressed then doors renders as black
				{
					g_Console.writeToBuffer(c, 219, 0x00);
				}
				else if (button6 == 1) // pressed then renders as white
				{
					g_Console.writeToBuffer(c, 219, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				break;
			case '9':
				if (button8 == 0)//not pressed then doors renders as black
				{
					g_Console.writeToBuffer(c, 219, 0x00);
				}
				else if (button8 == 1) // pressed then renders as white
				{
					g_Console.writeToBuffer(c, 219, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				break;
			default:
				g_Console.writeToBuffer(c, myArray[c.Y][c.X], FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			}

			// if the value in the array is an even interger number between 0 and 9, it is a purple button
			if ((myArray[c.Y][c.X] >= '0') && (myArray[c.Y][c.X] <= '9'))
			{
				switch ((myArray[c.Y][c.X] - 48) % 2)
				{
				case 0:
					g_Console.writeToBuffer(c, 219, FOREGROUND_BLUE | FOREGROUND_RED);
					break;
				default:
					break;
				}
			}
		}
	}
}

//void renderHaxToggle() // originally idea for displaying to the screen when player toggles hax but dropped due to time constraint
//{
//	COORD c;
//	c.Y = g_Console.getConsoleSize().Y / 2;
//	c.X = (g_Console.getConsoleSize().X / 2) - 10;
//
//	if (hax == true)
//	{
//		g_Console.writeToBuffer(c, "Collision toggled ON", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
//	}
//	else
//	{
//		g_Console.writeToBuffer(c, "Collision toggled OFF", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
//	}
//}

void renderCharacter()
{
    // Draw the location of the character
	WORD charColor = FOREGROUND_BLUE;
    if (g_sChar.m_bActive)
    {
		charColor = FOREGROUND_BLUE; // useless for now
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)219, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

// Darren's code
void updateCurr() // randomise the current and next number
{
	currNum = nextNum;
	do
	{
		nextNum = rand() % 10 + 48;
	} while (nextNum == currNum);
}

void highorlow() //game logic
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (mistakes == '3')
	{
		// go back to main game
		mistakes = '0';
		correctguesses = '0';
		currNum = '0';
		g_eGameState = S_TITLE;
	}
	if (correctguesses == '5')
	{
		// go to secret endscreen
		mistakes = '0';
		correctguesses = '0';
		currNum = '0';
		splashLoading(secret);
		g_eGameState = S_SECRET;
	}

	do
	{
		nextNum = rand() % 10 + 48; //randomise next number until it is different from current number
	} while (nextNum == currNum);

	if (g_abKeyPressed[K_UP])
	{
		if (currNum < nextNum)
		{
			correctguesses++;
		}
		else if (currNum > nextNum)
		{
			mistakes++;
		}
		updateCurr();
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN])
	{
		if (currNum > nextNum)
		{
			correctguesses++;
		}
		else if (currNum < nextNum)
		{
			mistakes++;
		}
		updateCurr();
		bSomethingHappened = true;
	}
	/*currNum = nextNum;*/

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.2;
	}
}

void highorlowrender()
{
	COORD c;

	for (int x = 0; x < 80; x++)
	{
		c.X = x;

		for (int y = 0; y < 25; y++)
		{
			c.Y = y;

			/*c.Y = 4;
			c.X = 32;
			g_Console.writeToBuffer(c, "Current Number is ", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 6;
			c.X = 48;
			g_Console.writeToBuffer(c, "Enter DOWN ARROW for lower", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 6;
			c.X = 6;
			g_Console.writeToBuffer(c, "Enter UP ARROW for higher", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 12;
			c.X = 9;
			g_Console.writeToBuffer(c, "Correct Guesses : ", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 12;
			c.X = 52;
			g_Console.writeToBuffer(c, "Wrong Guesses : ", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 23;
			c.X = 25;
			g_Console.writeToBuffer(c, "3 chances to get 5 correct guesses", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 2;
			c.X = 33;
			g_Console.writeToBuffer(c, "Higher Or Lower", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			c.Y = 24;
			c.X = 28;
			g_Console.writeToBuffer(c, "Numbers are between 0 and 9", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 4;
			c.X = 50;
			g_Console.writeToBuffer(c, currNum, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 12;
			c.X = 27;
			g_Console.writeToBuffer(c, correctguesses, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			c.Y = 12;
			c.X = 68;
			g_Console.writeToBuffer(c, mistakes, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);*/

			switch (myArray[c.Y][c.X])
			{
			case '.':
				g_Console.writeToBuffer(c, currNum, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case ',':
				g_Console.writeToBuffer(c, correctguesses, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '|':
				g_Console.writeToBuffer(c, mistakes, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			case '#':
				g_Console.writeToBuffer(c, 217, 0x00);
				break;
			default:
				g_Console.writeToBuffer(c, myArray[c.Y][c.X], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				break;
			}
		}
	}
}


// Code for minigame guide
void renderMiniGuide() // renders minigame
{
	COORD c;

	for (unsigned int row = 0; row < 25; ++row)
	{
		c.Y = row;
		for (unsigned int column = 0; column < 80; ++column)
		{
			c.X = column;
			switch (myArray[c.Y][c.X])
			{
			case '!':
				g_Console.writeToBuffer(c, 219, 0x44);
				break;
			case '-':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			case '@':
				g_Console.writeToBuffer(c, 219, 0x11);
				break;
			case '=':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			case '$':
				g_Console.writeToBuffer(c, 219, 0x66);
				break;
			case '+':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			case '%':
				g_Console.writeToBuffer(c, 219, 0x22);
				break;
			case ')':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			case ']':
				g_Console.writeToBuffer(c, 219, 0xAA);
				break;
			case '(':
				g_Console.writeToBuffer(c, 219, 0xCC);
				break;
			case '#':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			default:
				g_Console.writeToBuffer(c, myArray[c.Y][c.X], FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			}
		}
	}
}

// if you hit space in guide then go to minigame
void miniGuideLogic()
{
	if (g_abKeyPressed[K_SPACE])
	{
		mapLoading(mini);
		g_eGameState = S_MINIGAME;
	}
}

// Jeremiah's code for minigame
// to delay display of sequence so user has time to prepare to see sequence
void delayDisplay()
{
	if (bMinigameDelayed == 0)
	{
		g_dDelayDisplayTime = g_dElapsedTime + 1.50;
		bMinigameDelayed = 1;
	}

	if (g_dElapsedTime >= g_dDelayDisplayTime)
	{
		runMinigame = 1;
		redTrue, blueTrue, yellowTrue, greenTrue = 0;
		indicatorTrue = 0;
	}
}

// to initialise vector with random numbers for sequence
void initSequence()
{
	if (sequence.empty())
	{
		for (int i = 0; i < 7; i++)
		{
			sequence.push_back(rand() % 4 + 1);
		}
		sequence.push_back(0);
	}
}

// checking the sequence and changing the correct variables for keypad to show the right colours
void checkSequence()
{
	bool bSomethingHappened = false;
	if (g_dScanTime > g_dElapsedTime)
		return;

	if (inputState == 0)
	{
		switch (sequence[currentIndex])
		{
		case 0:
			redTrue = 0;
			blueTrue = 0;
			yellowTrue = 0;
			greenTrue = 0;
			inputState = 1;
			break;
		case 1:
			redTrue = 1;
			blueTrue = 0;
			yellowTrue = 0;
			greenTrue = 0;
			break;
		case 2:
			redTrue = 0;
			blueTrue = 1;
			yellowTrue = 0;
			greenTrue = 0;
			break;
		case 3:
			redTrue = 0;
			blueTrue = 0;
			yellowTrue = 1;
			greenTrue = 0;
			break;
		case 4:
			redTrue = 0;
			blueTrue = 0;
			yellowTrue = 0;
			greenTrue = 1;
			break;
		}
	}
}

// to reset button colours to nothing
void buttonReset()
{
	redTrue = 0;
	blueTrue = 0;
	yellowTrue = 0;
	greenTrue = 0;
}

// to reset display after showing one colour
// this is so the player can differentiate when the same colour is being shown twice, previously it was constantly lit up and was hard to tell
void resetDisplay()
{
	if (g_dButtonResetTime > g_dElapsedTime || bScan == false)
		return;

	buttonReset();
	bScan = false;
}

// goes through the vector, this delays the function checkSequence() so it doesn't show the colours rapidly but with a delay
void scanForDisplay()
{
	bool bSomethingHappened = false;
	if (g_dScanTime > g_dElapsedTime || bScan == true)
		return;

	if (currentIndex < 7)
	{
		currentIndex++;
		sequenceNumber++;
		bSomethingHappened = true;
		bScan = true;
	}
	else
	{
		return;
	}

	if (bSomethingHappened)
	{
		g_dScanTime = g_dElapsedTime + 1.25;
		g_dButtonResetTime = g_dElapsedTime + 1.00;
	}
}

// this checks the input after everything is displayed, and displays on the keypad when user hits the corresponding key
void checkInput()
{
	bool bSomethingHappened = false;
	bool bSomethingPressed = false;
	if (g_dSequenceTime > g_dElapsedTime)
		return;

	if (inputState == 1 && inputIndex < 7)
	{
		inputSequence[7] = 0;

		if (g_dButtonColorTime < g_dElapsedTime)
		{
			redTrue = 0;
			blueTrue = 0;
			yellowTrue = 0;
			greenTrue = 0;
		}

		if (g_abKeyPressed[K_1] || g_abKeyPressed[K_N1])
		{
			inputSequence[inputIndex] = 1;
			inputIndex++;
			redTrue = 1;
			bSomethingHappened = true;
			bSomethingPressed = true;
		}

		if (g_abKeyPressed[K_2] || g_abKeyPressed[K_N2])
		{
			inputSequence[inputIndex] = 2;
			inputIndex++;
			blueTrue = 1;
			bSomethingHappened = true;
			bSomethingPressed = true;
		}

		if (g_abKeyPressed[K_3] || g_abKeyPressed[K_N3])
		{
			inputSequence[inputIndex] = 3;
			inputIndex++;
			yellowTrue = 1;
			bSomethingHappened = true;
			bSomethingPressed = true;
		}

		if (g_abKeyPressed[K_4] || g_abKeyPressed[K_N4])
		{
			inputSequence[inputIndex] = 4;
			inputIndex++;
			greenTrue = 1;
			bSomethingHappened = true;
			bSomethingPressed = true;
		}

		if (bSomethingPressed)
		{
			g_dButtonColorTime = g_dElapsedTime + 0.150;
		}
	}

	if (inputIndex >= 7)
	{
		inputState = 2;
	}

	if (bSomethingHappened)
	{
		g_dSequenceTime = g_dElapsedTime + 0.150;
	}
}

// this is to reset the minigame, so it can be playable when you go back into the keypad game
void cleanMinigame()
{
	redTrue = 0;
	blueTrue = 0;
	yellowTrue = 0;
	greenTrue = 0;
	currentIndex = 0;
	sequenceNumber = 0;
	inputState = 0;
	inputSequence[8] = { 0, };
	inputIndex = 0;
	sequence.clear();
	miniGameCorrectOrNot = 0;
	runMinigame = 0;
	bMinigameDelayed = 0;
	indicatorTrue = 1;
}

// this function compares the vector that was randomised and the user's input
// if they are the same, goes to the end screen else the player dies
void compareArray()
{
	if (inputState == 2)
	{
		for (int i = 0; i < 7; i++)
		{
			// if player enters the sequence correctly
			if (inputSequence[i] == sequence[i])
			{
				miniGameCorrectOrNot++;
			}
		}

		if (miniGameCorrectOrNot == 7)
		{
			cleanMinigame();
			whichMap = 6;
			mapIdentifier();
		}
		else
		{
			cleanMinigame();
			g_eGameState = S_DEATH;
		}
	}
}

// logic for minigame
void minigameLogic()
{
	switch (runMinigame)
	{
	case 0:
		delayDisplay();
		break;
	case 1:
		initSequence();
		checkSequence();
		scanForDisplay();
		resetDisplay();
		checkInput();
		compareArray();
		break;
	}
}

// for rendering the minigame
void renderMinigame()
{
	COORD c;

	for (unsigned int row = 0; row < 25; ++row)
	{
		c.Y = row;
		for (unsigned int column = 0; column < 80; ++column)
		{
			c.X = column;
			switch (myArray[c.Y][c.X])
			{
			case '!':
				g_Console.writeToBuffer(c, 219, 0x44);
				break;
			case '-':
				switch (redTrue)
				{
				case 0:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				case 1:
					g_Console.writeToBuffer(c, 219, 0xFF);
					break;
				case 2:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				}
				break;
			case '@':
				g_Console.writeToBuffer(c, 219, 0x11);
				break;
			case '=':
				switch (blueTrue)
				{
				case 0:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				case 1:
					g_Console.writeToBuffer(c, 219, 0xFF);
					break;
				case 2:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				}
				break;
			case '$':
				g_Console.writeToBuffer(c, 219, 0x66);
				break;
			case '+':
				switch (yellowTrue)
				{
				case 0:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				case 1:
					g_Console.writeToBuffer(c, 219, 0xFF);
					break;
				case 2:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				}
				break;
			case '%':
				g_Console.writeToBuffer(c, 219, 0x22);
				break;
			case ')':
				switch (greenTrue)
				{
				case 0:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				case 1:
					g_Console.writeToBuffer(c, 219, 0xFF);
					break;
				case 2:
					g_Console.writeToBuffer(c, 219, 0x00);
					break;
				}
				break;
			case '(':
				switch (indicatorTrue)
				{
				case 0:
					if (inputState == 0)
					{
						g_Console.writeToBuffer(c, 219, 0xCC);
					}
					else
					{
						g_Console.writeToBuffer(c, 219, 0xAA);
					}
					break;
				case 1:
					g_Console.writeToBuffer(c, 219, 0x44);
					break;
				}
				break;
			case '#':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			default:
				g_Console.writeToBuffer(c, myArray[c.Y][c.X], FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			}
		}
	}
}

// Ian's code
void identifyAround() //checks for tiles around the blank
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (myArray[i][j] == '=')
			{
				slideGX = j;
				slideGY = i;
			}
		}
	}

	lefta = myArray[slideGY][slideGX - 9]; //left of blank
	righta = myArray[slideGY][slideGX + 9]; //right of blank
	upa = myArray[slideGY - 5][slideGX]; //above the blank
	downa = myArray[slideGY + 5][slideGX]; //below the blank
}

void mover(char direction, int X, int Y)//controls movement of the blank tile
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (direction == '#' || direction == '_')
			{
				break;
			}
			else
			{
				if ((myArray[i][j] == ')') || (myArray[i][j] == '='))
				{
					myArray[i][j] = '(';
				}

				if (myArray[i][j] == direction)
				{
					myArray[i][j] = ')';
				}

				if (myArray[i][j] == '(')
				{
					myArray[i][j] = direction;
				}

				myArray[Y][X] = '=';
			}
		}
	}
}

void slide()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	identifyAround();

	if (g_abKeyPressed[K_LEFT])
	{
		mover(lefta, slideGX - 9, slideGY);//tile moves left
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_RIGHT])
	{
		mover(righta, slideGX + 9, slideGY);//tile moves right
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_DOWN])
	{
		mover(downa, slideGX, slideGY + 5);//tile moves down
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_UP])
	{
		mover(upa, slideGX, slideGY - 5);//tile moves up
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_ESCAPE])
	{
		bSomethingHappened = true;
		g_eGameState = S_TITLE;
	}

	if ((myArray[4][27] == '$') && (myArray[4][36] == '?') && (myArray[4][45] == ')') &&
		(myArray[9][27] == '-') && (myArray[9][36] == '@') && (myArray[9][45] == '^') &&
		(myArray[14][27] == '&') && (myArray[14][36] == '*') && (myArray[14][45] == '%'))
	{
		splashLoading(secret);
		g_eGameState = S_SECRET; //game ending condition
	}

	if (bSomethingHappened) // no infinite input
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
}

void slideRender()
{
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD c = g_Console.getConsoleSize();

	for (int Y = 0; Y < 25; ++Y)
	{
		c.Y = Y;

		for (int X = 0; X < 80; ++X)
		{
			c.X = X;

			switch (myArray[c.Y][c.X])
			{
			case '#':
				g_Console.writeToBuffer(c, 219, 0x00);
				break;
			case ')':
				g_Console.writeToBuffer(c, 219, 0x6F);
				break;
			case '(':
				g_Console.writeToBuffer(c, 219, 0x6F);
				break;
			case '?':
				g_Console.writeToBuffer(c, 219, 0x1A);
				break;
			case '@':
				g_Console.writeToBuffer(c, 219, 0x2B);
				break;
			case '$':
				g_Console.writeToBuffer(c, 219, 0x3C);
				break;
			case '%':
				g_Console.writeToBuffer(c, 219, 0x4D);
				break;
			case '^':
				g_Console.writeToBuffer(c, 219, 0x5E);
				break;
			case '&':
				g_Console.writeToBuffer(c, 219, 0xE5);
				break;
			case '*':
				g_Console.writeToBuffer(c, 219, 0xA1);
				break;
			case '-':
				g_Console.writeToBuffer(c, 219, 0xB2);
				break;
			case '=':
				g_Console.writeToBuffer(c, 219, 0x6F);
				break;
			case '1':
				g_Console.writeToBuffer(c, 219, 0x3C);
				break;
			case '2':
				g_Console.writeToBuffer(c, 219, 0x1A);
				break;
			case '3':
				g_Console.writeToBuffer(c, 219, 0x6F);
				break;
			case '4':
				g_Console.writeToBuffer(c, 219, 0xB2);
				break;
			case '5':
				g_Console.writeToBuffer(c, 219, 0x2B);
				break;
			case '6':
				g_Console.writeToBuffer(c, 219, 0x5E);
				break;
			case '7':
				g_Console.writeToBuffer(c, 219, 0xE5);
				break;
			case '8':
				g_Console.writeToBuffer(c, 219, 0xA1);
				break;
			case '9':
				g_Console.writeToBuffer(c, 219, 0x4D);
				break;
			default:
				g_Console.writeToBuffer(c, myArray[c.Y][c.X], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			}
		}
	}
}