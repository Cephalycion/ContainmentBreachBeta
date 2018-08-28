#ifndef _CUST_H
#define _CUST_H

#include "Framework\timer.h"
#include "Framework/console.h"

// use pointer to touch the array
void customGuide(char(*customGArray)[80]);
void customLoading(char(*customArray)[80]);

// use '&' to touch bounce time and game state
void userGLogic(double &g_dBounceTime, double g_dElapsedTime, bool g_abKeyPressed[], enum EGAMESTATES &g_eGameState);

// use pointer and '&' to touch character coordinates and array
void customKeyReg(bool g_abKeyPressed[], struct SGameChar &g_sChar, char(*customArray)[80]);

// need alot of '&' so we can touch the values from another file
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
);

// same here 
void customMoveCharacter(
	char(*customArray)[80],
	double &g_dBounceTime,
	double g_dElapsedTime,
	bool g_abKeyPressed[],
	struct SGameChar &g_sChar,
	class Console &g_Console
);

// same
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
);

// console need '&' to touch the render onto screen
void customGRender(char(*customGArray)[80], Console &g_Console);

void customRender(char(*customArray)[80], Console &g_Console);

#endif