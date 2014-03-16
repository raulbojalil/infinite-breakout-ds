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
