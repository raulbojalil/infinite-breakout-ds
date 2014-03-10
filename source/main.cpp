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


/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	Simple console print demo
	-- dovoto


---------------------------------------------------------------------------------*/
/*#include <nds.h>

#include <stdio.h>

volatile int frame = 0;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}
	
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	iprintf("      Hello DS dev'rs\n");
	iprintf("     \x1b[32mwww.devkitpro.org\n");
	iprintf("   \x1b[32;1mwww.drunkencoders.com\x1b[39m");
 
	while(1) {
	
		swiWaitForVBlank();
		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH 
		iprintf("\x1b[10;0HFrame = %d",frame);
		iprintf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
		iprintf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);		
	
	}

	return 0;
}*/
