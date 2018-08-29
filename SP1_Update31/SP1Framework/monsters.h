#ifndef _MONS_H
#define _MONS_H

#include "Framework\timer.h"
#include "Framework/console.h"

// struct for the game monster
struct SMapMonster
{
	COORD m_cLocation;
	int m_iDirection;
	char m_cType;
};

// monsters: + up down, = left right, $ clockwise, % anti
extern SMapMonster monsterList[50];

void renderMonsters(class Console &g_Console);	// render monsters
void moveMonsters(char(*myArray)[80], double &g_dMonsterTime, double g_dElapsedTime, bool button0, bool button2, bool button4, bool button6, bool button8);	// moves monsters
void getMonsterXYType(char(*myArray)[80]);	// get monster XY
void clearMonsters(char(*myArray)[80]);		// cleans the struct

// different types of monsters
void moveUpDownMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80], bool button0, bool button2, bool button4, bool button6, bool button8);
void moveLeftRightMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80], bool button0, bool button2, bool button4, bool button6, bool button8);
void moveClockwiseMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80], bool button0, bool button2, bool button4, bool button6, bool button8);
void moveAntiClockwiseMonster(SMapMonster &monster, bool &somethingHappened, char(*myArray)[80], bool button0, bool button2, bool button4, bool button6, bool button8);

#endif