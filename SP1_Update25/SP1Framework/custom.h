#ifndef _CUST_H
#define _CUST_H

#include "Framework\timer.h"
#include "Framework/console.h"

void customGuide	(char(*customGArray)[80]);
void customLoading	(char(*customArray)[80]);

void userGLogic(double &g_dBounceTime, double g_dElapsedTime, bool g_abKeyPressed[], enum EGAMESTATES &g_eGameState);
void customKeyReg(bool g_abKeyPressed[], struct SGameChar &g_sChar, char(*customArray)[80]);

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

void customMoveCharacter(
	char(*customArray)[80],
	double &g_dBounceTime,
	double g_dElapsedTime,
	bool g_abKeyPressed[],
	struct SGameChar &g_sChar,
	class Console &g_Console
);

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

void customGRender(char(*customGArray)[80], Console &g_Console);

void customRender(char(*customArray)[80], Console &g_Console);

#endif