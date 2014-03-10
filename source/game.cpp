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
			paddleAccel = (4096 - paddle) + lastPaddle;
		else if(paddleAccel < -4000) //d
			paddleAccel = (4096 - lastPaddle) + paddle;
	  
	   
	   //if(paddleAccel != 0 && paddleAccel != -5 && paddleAccel != 5 && paddleAccel != -10 && paddleAccel != 10 && paddleAccel != 15 && paddleAccel != -15)
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