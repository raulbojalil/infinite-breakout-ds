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
