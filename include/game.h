#ifndef _GAME_H_
#define _GAME_H_

#include <nds.h>

#define GAME_STATE_TITLE 0
#define GAME_STATE_BREAKOUT 1

extern u32 lastPressedKeys;
extern u32 pressedKeys;
extern u32 newPressedKeys;
extern u32 releasedKeys;
extern u16 lastPaddle;
extern s16 paddleAccel;
extern u16 guitarGripPressedKeys;
extern touchPosition touchPos;

void update();
void updateKeys();
void setGameState(u8 gameState);

#endif
