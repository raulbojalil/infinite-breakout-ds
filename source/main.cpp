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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "draw.h"
#include "game.h"

#define TIMER_SPEED (BUS_CLOCK/1024) 
 
int main(void)
{
	consoleDemoInit(); 
	drawInit();					
	timerStart(0, ClockDivider_1024, 0, NULL);

	setGameState(GAME_STATE_TITLE);

	while(1)
	{
		update();	 
		swiWaitForVBlank();
	}
 
	return 0;
}
