/*
    Infinite Breakout DS - An infinite breakout clone for the Nintendo DS
    Copyright (C) 2009,2014 Raúl A. Bojalil Becerra

    This file is part of Infinite Breakout DS.

    Infinite Breakout DS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Infinite Breakout DS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Infinite Breakout DS. If not, see <http://www.gnu.org/licenses/>.

*/

#include <nds.h>
#include <nds/arm9/paddle.h>
#include <nds/arm9/guitarGrip.h>
#include "game.h"
#include "breakout.h"
#include "title.h"
#include <stdio.h>

u32 lastPressedKeys = 0;
u32 pressedKeys = 0;
u32 newPressedKeys = 0;
u32 releasedKeys = 0;
u16 lastPaddle = 0;
s16 paddleAccel = 0;
u16 guitarGripPressedKeys = 0;
touchPosition touchPos;

u8 currentGameState;


void update()
{
	updateKeys();
	switch(currentGameState)
	{
		case GAME_STATE_TITLE:
			titleUpdate();
			titleDraw();
			break;
		case GAME_STATE_BREAKOUT:
			breakoutUpdate();
			breakoutDraw();
			break;
	}
}

void setGameState(u8 gameState)
{
	 currentGameState = gameState;

	 switch(currentGameState)
	 {
		case GAME_STATE_TITLE:
			titleInit();
			break;
		case GAME_STATE_BREAKOUT:
			breakoutInit();
			break;
	 }
}

void updateKeys()
{
	
	touchRead(&touchPos);

	if(paddleIsInserted())
	{
	   u16 paddle = paddleRead();
	   paddleAccel = paddle - lastPaddle;
	   lastPaddle = paddle;
	   
		if(paddleAccel > 4000) //i
			paddleAccel = -15;
			//paddleAccel = (4096 - paddle) + lastPaddle;
		else if(paddleAccel < -4000) //d
			//paddleAccel = (4096 - lastPaddle) + paddle;
			paddleAccel = 15;

	   //if(paddleAccel != 0 && paddleAccel != -5 && paddleAccel != 5 && paddleAccel != -10 && paddleAccel != 10 && paddleAccel != 15 && paddleAccel != -15 && paddleAccel != 20 && paddleAccel != -20)
	   //iprintf("%d", paddleAccel);
	   //iprintf("\x1b[14;10H%d       \n", paddleAccel);
	   
	}

	if(guitarGripIsInserted())
	{
		guitarGripScanKeys();
		guitarGripPressedKeys = guitarGripKeysHeld();
	}
	
	scanKeys();
	pressedKeys = keysHeld();

    	u32 keysWithChanges = lastPressedKeys ^ pressedKeys;
    	newPressedKeys = keysWithChanges & pressedKeys;
    	releasedKeys = keysWithChanges & lastPressedKeys;

	lastPressedKeys = pressedKeys;
}