#include <nds.h>
#include <stdio.h>
#include "title.h"
#include "game.h"
#include "draw.h"

u16 segments[12] = {0,84,144,159,204,243,250,258,263,305,330,342 };
Pixel pixels[350] = {{113,47,COLOR_YELLOW},{110,44,COLOR_YELLOW},{106,41,COLOR_YELLOW},{103,38,COLOR_YELLOW},{96,33,COLOR_YELLOW},{91,30,COLOR_YELLOW},{87,27,COLOR_YELLOW},{84,26,COLOR_YELLOW},{82,25,COLOR_YELLOW},{78,25,COLOR_YELLOW},{73,24,COLOR_YELLOW},{67,24,COLOR_YELLOW},{62,24,COLOR_YELLOW},{59,25,COLOR_YELLOW},{56,26,COLOR_YELLOW},{51,28,COLOR_YELLOW},{48,32,COLOR_YELLOW},{44,36,COLOR_YELLOW},{43,41,COLOR_YELLOW},{41,44,COLOR_YELLOW},{40,49,COLOR_YELLOW},{40,52,COLOR_YELLOW},{41,55,COLOR_YELLOW},{44,59,COLOR_YELLOW},{47,62,COLOR_YELLOW},{50,65,COLOR_YELLOW},{54,67,COLOR_YELLOW},{58,68,COLOR_YELLOW},{61,68,COLOR_YELLOW},{66,68,COLOR_YELLOW},{72,67,COLOR_YELLOW},{77,64,COLOR_YELLOW},{84,60,COLOR_YELLOW},{89,56,COLOR_YELLOW},{95,52,COLOR_YELLOW},{102,46,COLOR_YELLOW},{107,43,COLOR_YELLOW},{113,38,COLOR_YELLOW},{120,33,COLOR_YELLOW},{126,30,COLOR_YELLOW},{129,28,COLOR_YELLOW},{133,26,COLOR_YELLOW},{137,24,COLOR_YELLOW},{142,22,COLOR_YELLOW},{143,22,COLOR_YELLOW},{143,21,COLOR_YELLOW},{144,21,COLOR_YELLOW},{146,21,COLOR_YELLOW},{148,21,COLOR_YELLOW},{149,21,COLOR_YELLOW},{151,21,COLOR_YELLOW},{155,23,COLOR_YELLOW},{162,25,COLOR_YELLOW},{166,27,COLOR_YELLOW},{167,29,COLOR_YELLOW},{169,30,COLOR_YELLOW},{170,32,COLOR_YELLOW},{173,34,COLOR_YELLOW},{173,36,COLOR_YELLOW},{174,40,COLOR_YELLOW},{174,45,COLOR_YELLOW},{174,50,COLOR_YELLOW},{173,53,COLOR_YELLOW},{171,55,COLOR_YELLOW},{167,59,COLOR_YELLOW},{163,61,COLOR_YELLOW},{157,63,COLOR_YELLOW},{153,64,COLOR_YELLOW},{147,64,COLOR_YELLOW},{142,65,COLOR_YELLOW},{138,65,COLOR_YELLOW},{134,64,COLOR_YELLOW},{130,64,COLOR_YELLOW},{127,63,COLOR_YELLOW},{125,61,COLOR_YELLOW},{122,58,COLOR_YELLOW},{119,56,COLOR_YELLOW},{116,54,COLOR_YELLOW},{114,52,COLOR_YELLOW},{111,49,COLOR_YELLOW},{109,46,COLOR_YELLOW},{108,45,COLOR_YELLOW},{108,44,COLOR_YELLOW},{107,44,COLOR_YELLOW},{26,152,COLOR_YELLOW},{25,144,COLOR_YELLOW},{24,139,COLOR_YELLOW},{23,132,COLOR_YELLOW},{23,128,COLOR_YELLOW},{21,122,COLOR_YELLOW},{21,118,COLOR_YELLOW},{21,114,COLOR_YELLOW},{21,112,COLOR_YELLOW},{21,111,COLOR_YELLOW},{21,109,COLOR_YELLOW},{21,108,COLOR_YELLOW},{22,106,COLOR_YELLOW},{25,105,COLOR_YELLOW},{27,105,COLOR_YELLOW},{28,105,COLOR_YELLOW},{30,104,COLOR_YELLOW},{31,104,COLOR_YELLOW},{33,104,COLOR_YELLOW},{34,105,COLOR_YELLOW},{36,106,COLOR_YELLOW},{38,108,COLOR_YELLOW},{38,111,COLOR_YELLOW},{38,113,COLOR_YELLOW},{38,116,COLOR_YELLOW},{37,119,COLOR_YELLOW},{34,121,COLOR_YELLOW},{33,124,COLOR_YELLOW},{32,125,COLOR_YELLOW},{31,126,COLOR_YELLOW},{31,127,COLOR_YELLOW},{30,127,COLOR_YELLOW},{29,127,COLOR_YELLOW},{28,127,COLOR_YELLOW},{27,127,COLOR_YELLOW},{26,127,COLOR_YELLOW},{27,127,COLOR_YELLOW},{36,129,COLOR_YELLOW},{38,129,COLOR_YELLOW},{40,130,COLOR_YELLOW},{41,132,COLOR_YELLOW},{43,135,COLOR_YELLOW},{43,137,COLOR_YELLOW},{44,139,COLOR_YELLOW},{44,143,COLOR_YELLOW},{44,145,COLOR_YELLOW},{44,149,COLOR_YELLOW},{43,150,COLOR_YELLOW},{42,151,COLOR_YELLOW},{41,153,COLOR_YELLOW},{39,153,COLOR_YELLOW},{39,154,COLOR_YELLOW},{37,154,COLOR_YELLOW},{34,154,COLOR_YELLOW},{33,154,COLOR_YELLOW},{30,154,COLOR_YELLOW},{29,154,COLOR_YELLOW},{28,154,COLOR_YELLOW},{27,154,COLOR_YELLOW},{26,154,COLOR_YELLOW},{54,132,COLOR_YELLOW},{54,138,COLOR_YELLOW},{54,143,COLOR_YELLOW},{53,148,COLOR_YELLOW},{53,150,COLOR_YELLOW},{53,151,COLOR_YELLOW},{53,150,COLOR_YELLOW},{53,148,COLOR_YELLOW},{55,143,COLOR_YELLOW},{56,138,COLOR_YELLOW},{59,135,COLOR_YELLOW},{62,131,COLOR_YELLOW},{64,130,COLOR_YELLOW},{65,128,COLOR_YELLOW},{66,128,COLOR_YELLOW},{74,140,COLOR_YELLOW},{81,141,COLOR_YELLOW},{85,141,COLOR_YELLOW},{86,141,COLOR_YELLOW},{87,141,COLOR_YELLOW},{87,140,COLOR_YELLOW},{88,139,COLOR_YELLOW},{88,138,COLOR_YELLOW},{88,137,COLOR_YELLOW},{88,136,COLOR_YELLOW},{88,135,COLOR_YELLOW},{88,134,COLOR_YELLOW},{88,133,COLOR_YELLOW},{88,132,COLOR_YELLOW},{88,130,COLOR_YELLOW},{87,130,COLOR_YELLOW},{86,130,COLOR_YELLOW},{85,130,COLOR_YELLOW},{84,129,COLOR_YELLOW},{83,129,COLOR_YELLOW},{82,128,COLOR_YELLOW},{80,128,COLOR_YELLOW},{78,128,COLOR_YELLOW},{76,129,COLOR_YELLOW},{74,130,COLOR_YELLOW},{71,132,COLOR_YELLOW},{69,134,COLOR_YELLOW},{67,136,COLOR_YELLOW},{67,137,COLOR_YELLOW},{66,140,COLOR_YELLOW},{66,143,COLOR_YELLOW},{66,145,COLOR_YELLOW},{67,148,COLOR_YELLOW},{68,151,COLOR_YELLOW},{70,153,COLOR_YELLOW},{73,155,COLOR_YELLOW},{75,156,COLOR_YELLOW},{77,157,COLOR_YELLOW},{80,157,COLOR_YELLOW},{83,157,COLOR_YELLOW},{86,157,COLOR_YELLOW},{88,155,COLOR_YELLOW},{90,154,COLOR_YELLOW},{92,152,COLOR_YELLOW},{92,150,COLOR_YELLOW},{115,133,COLOR_YELLOW},{113,132,COLOR_YELLOW},{111,132,COLOR_YELLOW},{110,132,COLOR_YELLOW},{108,132,COLOR_YELLOW},{107,132,COLOR_YELLOW},{105,134,COLOR_YELLOW},{105,135,COLOR_YELLOW},{103,137,COLOR_YELLOW},{102,139,COLOR_YELLOW},{100,142,COLOR_YELLOW},{99,144,COLOR_YELLOW},{97,146,COLOR_YELLOW},{97,147,COLOR_YELLOW},{97,150,COLOR_YELLOW},{97,152,COLOR_YELLOW},{98,153,COLOR_YELLOW},{99,155,COLOR_YELLOW},{100,155,COLOR_YELLOW},{102,156,COLOR_YELLOW},{104,157,COLOR_YELLOW},{107,157,COLOR_YELLOW},{108,157,COLOR_YELLOW},{111,156,COLOR_YELLOW},{112,156,COLOR_YELLOW},{114,154,COLOR_YELLOW},{115,152,COLOR_YELLOW},{117,150,COLOR_YELLOW},{117,147,COLOR_YELLOW},{118,145,COLOR_YELLOW},{118,143,COLOR_YELLOW},{118,140,COLOR_YELLOW},{118,138,COLOR_YELLOW},{118,139,COLOR_YELLOW},{119,148,COLOR_YELLOW},{119,154,COLOR_YELLOW},{119,155,COLOR_YELLOW},{119,156,COLOR_YELLOW},{120,156,COLOR_YELLOW},{129,115,COLOR_YELLOW},{129,128,COLOR_YELLOW},{129,136,COLOR_YELLOW},{129,145,COLOR_YELLOW},{129,153,COLOR_YELLOW},{129,158,COLOR_YELLOW},{129,160,COLOR_YELLOW},{130,139,COLOR_YELLOW},{133,140,COLOR_YELLOW},{136,142,COLOR_YELLOW},{139,145,COLOR_YELLOW},{142,150,COLOR_YELLOW},{144,153,COLOR_YELLOW},{145,154,COLOR_YELLOW},{145,155,COLOR_YELLOW},{133,141,COLOR_YELLOW},{139,136,COLOR_YELLOW},{143,132,COLOR_YELLOW},{144,130,COLOR_YELLOW},{145,130,COLOR_YELLOW},{163,133,COLOR_YELLOW},{161,133,COLOR_YELLOW},{159,133,COLOR_YELLOW},{157,135,COLOR_YELLOW},{156,135,COLOR_YELLOW},{156,136,COLOR_YELLOW},{155,136,COLOR_YELLOW},{154,137,COLOR_YELLOW},{154,139,COLOR_YELLOW},{154,141,COLOR_YELLOW},{153,144,COLOR_YELLOW},{153,146,COLOR_YELLOW},{153,148,COLOR_YELLOW},{153,151,COLOR_YELLOW},{155,152,COLOR_YELLOW},{156,155,COLOR_YELLOW},{158,157,COLOR_YELLOW},{160,158,COLOR_YELLOW},{162,159,COLOR_YELLOW},{163,159,COLOR_YELLOW},{164,160,COLOR_YELLOW},{166,160,COLOR_YELLOW},{167,160,COLOR_YELLOW},{169,159,COLOR_YELLOW},{169,156,COLOR_YELLOW},{170,155,COLOR_YELLOW},{171,153,COLOR_YELLOW},{171,151,COLOR_YELLOW},{171,149,COLOR_YELLOW},{171,146,COLOR_YELLOW},{171,144,COLOR_YELLOW},{170,142,COLOR_YELLOW},{170,140,COLOR_YELLOW},{169,139,COLOR_YELLOW},{168,137,COLOR_YELLOW},{167,137,COLOR_YELLOW},{166,136,COLOR_YELLOW},{165,135,COLOR_YELLOW},{164,134,COLOR_YELLOW},{163,134,COLOR_YELLOW},{163,133,COLOR_YELLOW},{162,133,COLOR_YELLOW},{181,132,COLOR_YELLOW},{181,136,COLOR_YELLOW},{181,143,COLOR_YELLOW},{181,148,COLOR_YELLOW},{181,152,COLOR_YELLOW},{182,153,COLOR_YELLOW},{184,156,COLOR_YELLOW},{186,158,COLOR_YELLOW},{187,158,COLOR_YELLOW},{188,158,COLOR_YELLOW},{189,158,COLOR_YELLOW},{190,158,COLOR_YELLOW},{191,158,COLOR_YELLOW},{192,158,COLOR_YELLOW},{194,156,COLOR_YELLOW},{195,154,COLOR_YELLOW},{195,153,COLOR_YELLOW},{196,150,COLOR_YELLOW},{197,148,COLOR_YELLOW},{197,146,COLOR_YELLOW},{197,143,COLOR_YELLOW},{197,141,COLOR_YELLOW},{197,138,COLOR_YELLOW},{197,134,COLOR_YELLOW},{197,133,COLOR_YELLOW},{217,103,COLOR_YELLOW},{217,113,COLOR_YELLOW},{217,120,COLOR_YELLOW},{217,125,COLOR_YELLOW},{217,130,COLOR_YELLOW},{217,138,COLOR_YELLOW},{217,142,COLOR_YELLOW},{217,146,COLOR_YELLOW},{217,149,COLOR_YELLOW},{216,151,COLOR_YELLOW},{216,154,COLOR_YELLOW},{216,155,COLOR_YELLOW},{207,128,COLOR_YELLOW},{212,128,COLOR_YELLOW},{217,129,COLOR_YELLOW},{222,129,COLOR_YELLOW},{225,129,COLOR_YELLOW},{226,129,COLOR_YELLOW},{227,129,COLOR_YELLOW},{228,129,COLOR_YELLOW}};/*u16 segments[2] = {}
Pixel pixels[215] = {{24,36,COLOR_YELLOW},{24,37,COLOR_YELLOW},{24,44,COLOR_YELLOW},{25,52,COLOR_YELLOW},{26,64,COLOR_YELLOW},{26,83,COLOR_YELLOW},{24,100,COLOR_YELLOW},{23,112,COLOR_YELLOW},{20,124,COLOR_YELLOW},{20,132,COLOR_YELLOW},{19,137,COLOR_YELLOW},{19,140,COLOR_YELLOW},{19,139,COLOR_YELLOW},{19,136,COLOR_YELLOW},{21,127,COLOR_YELLOW},{23,118,COLOR_YELLOW},{28,107,COLOR_YELLOW},{33,101,COLOR_YELLOW},{40,97,COLOR_YELLOW},{44,95,COLOR_YELLOW},{48,93,COLOR_YELLOW},{49,92,COLOR_YELLOW},{50,92,COLOR_YELLOW},{51,92,COLOR_YELLOW},{51,93,COLOR_YELLOW},{52,96,COLOR_YELLOW},{55,102,COLOR_YELLOW},{57,108,COLOR_YELLOW},{57,116,COLOR_YELLOW},{56,122,COLOR_YELLOW},{55,128,COLOR_YELLOW},{54,132,COLOR_YELLOW},{53,135,COLOR_YELLOW},{52,139,COLOR_YELLOW},{51,141,COLOR_YELLOW},{51,143,COLOR_YELLOW},{51,144,COLOR_YELLOW},{52,144,COLOR_YELLOW},{52,144,COLOR_YELLOW},{53,144,COLOR_YELLOW},{55,141,COLOR_YELLOW},{56,137,COLOR_YELLOW},{60,132,COLOR_YELLOW},{62,128,COLOR_YELLOW},{64,125,COLOR_YELLOW},{66,120,COLOR_YELLOW},{68,116,COLOR_YELLOW},{73,111,COLOR_YELLOW},{76,107,COLOR_YELLOW},{80,104,COLOR_YELLOW},{85,100,COLOR_YELLOW},{91,98,COLOR_YELLOW},{96,96,COLOR_YELLOW},{99,96,COLOR_YELLOW},{98,96,COLOR_YELLOW},{92,99,COLOR_YELLOW},{87,100,COLOR_YELLOW},{84,102,COLOR_YELLOW},{80,105,COLOR_YELLOW},{76,108,COLOR_YELLOW},{73,112,COLOR_YELLOW},{71,117,COLOR_YELLOW},{68,122,COLOR_YELLOW},{68,126,COLOR_YELLOW},{68,129,COLOR_YELLOW},{68,132,COLOR_YELLOW},{68,136,COLOR_YELLOW},{70,137,COLOR_YELLOW},{72,138,COLOR_YELLOW},{75,139,COLOR_YELLOW},{80,140,COLOR_YELLOW},{85,140,COLOR_YELLOW},{89,140,COLOR_YELLOW},{93,139,COLOR_YELLOW},{96,136,COLOR_YELLOW},{100,133,COLOR_YELLOW},{102,128,COLOR_YELLOW},{104,122,COLOR_YELLOW},{104,118,COLOR_YELLOW},{105,115,COLOR_YELLOW},{105,112,COLOR_YELLOW},{104,108,COLOR_YELLOW},{104,105,COLOR_YELLOW},{101,104,COLOR_YELLOW},{99,103,COLOR_YELLOW},{99,102,COLOR_YELLOW},{96,102,COLOR_YELLOW},{93,102,COLOR_YELLOW},{90,103,COLOR_YELLOW},{87,104,COLOR_YELLOW},{84,108,COLOR_YELLOW},{82,111,COLOR_YELLOW},{82,113,COLOR_YELLOW},{82,115,COLOR_YELLOW},{82,116,COLOR_YELLOW},{83,117,COLOR_YELLOW},{84,117,COLOR_YELLOW},{88,120,COLOR_YELLOW},{92,120,COLOR_YELLOW},{96,120,COLOR_YELLOW},{101,120,COLOR_YELLOW},{108,118,COLOR_YELLOW},{115,115,COLOR_YELLOW},{120,112,COLOR_YELLOW},{125,106,COLOR_YELLOW},{132,97,COLOR_YELLOW},{136,89,COLOR_YELLOW},{140,81,COLOR_YELLOW},{143,76,COLOR_YELLOW},{145,71,COLOR_YELLOW},{148,66,COLOR_YELLOW},{151,62,COLOR_YELLOW},{152,60,COLOR_YELLOW},{152,60,COLOR_YELLOW},{152,60,COLOR_YELLOW},{148,61,COLOR_YELLOW},{142,64,COLOR_YELLOW},{136,70,COLOR_YELLOW},{134,74,COLOR_YELLOW},{132,79,COLOR_YELLOW},{130,84,COLOR_YELLOW},{128,89,COLOR_YELLOW},{127,95,COLOR_YELLOW},{124,101,COLOR_YELLOW},{123,108,COLOR_YELLOW},{123,114,COLOR_YELLOW},{122,119,COLOR_YELLOW},{121,124,COLOR_YELLOW},{121,128,COLOR_YELLOW},{122,131,COLOR_YELLOW},{123,132,COLOR_YELLOW},{124,134,COLOR_YELLOW},{125,135,COLOR_YELLOW},{127,136,COLOR_YELLOW},{129,137,COLOR_YELLOW},{132,139,COLOR_YELLOW},{134,140,COLOR_YELLOW},{136,140,COLOR_YELLOW},{140,140,COLOR_YELLOW},{141,139,COLOR_YELLOW},{145,136,COLOR_YELLOW},{149,132,COLOR_YELLOW},{153,128,COLOR_YELLOW},{158,124,COLOR_YELLOW},{164,120,COLOR_YELLOW},{168,116,COLOR_YELLOW},{175,112,COLOR_YELLOW},{180,110,COLOR_YELLOW},{188,106,COLOR_YELLOW},{192,104,COLOR_YELLOW},{195,104,COLOR_YELLOW},{196,104,COLOR_YELLOW},{197,104,COLOR_YELLOW},{200,104,COLOR_YELLOW},{202,104,COLOR_YELLOW},{204,106,COLOR_YELLOW},{203,107,COLOR_YELLOW},{195,109,COLOR_YELLOW},{183,112,COLOR_YELLOW},{179,112,COLOR_YELLOW},{174,114,COLOR_YELLOW},{171,116,COLOR_YELLOW},{165,120,COLOR_YELLOW},{163,124,COLOR_YELLOW},{160,128,COLOR_YELLOW},{159,132,COLOR_YELLOW},{157,136,COLOR_YELLOW},{157,139,COLOR_YELLOW},{158,141,COLOR_YELLOW},{160,143,COLOR_YELLOW},{161,144,COLOR_YELLOW},{162,144,COLOR_YELLOW},{164,144,COLOR_YELLOW},{170,144,COLOR_YELLOW},{176,144,COLOR_YELLOW},{182,142,COLOR_YELLOW},{188,140,COLOR_YELLOW},{192,136,COLOR_YELLOW},{195,132,COLOR_YELLOW},{199,126,COLOR_YELLOW},{200,118,COLOR_YELLOW},{202,113,COLOR_YELLOW},{202,111,COLOR_YELLOW},{203,108,COLOR_YELLOW},{203,109,COLOR_YELLOW},{199,115,COLOR_YELLOW},{192,127,COLOR_YELLOW},{188,134,COLOR_YELLOW},{187,140,COLOR_YELLOW},{186,143,COLOR_YELLOW},{185,146,COLOR_YELLOW},{185,149,COLOR_YELLOW},{188,153,COLOR_YELLOW},{189,155,COLOR_YELLOW},{192,156,COLOR_YELLOW},{194,156,COLOR_YELLOW},{202,156,COLOR_YELLOW},{212,154,COLOR_YELLOW},{220,152,COLOR_YELLOW},{224,150,COLOR_YELLOW},{229,146,COLOR_YELLOW},{232,144,COLOR_YELLOW},{232,143,COLOR_YELLOW},{119,8,COLOR_YELLOW},{125,35,COLOR_YELLOW},{124,70,COLOR_YELLOW},{120,88,COLOR_YELLOW},{117,99,COLOR_YELLOW},{113,112,COLOR_YELLOW},{109,129,COLOR_YELLOW},{104,143,COLOR_YELLOW},{98,158,COLOR_YELLOW},{94,168,COLOR_YELLOW},{92,177,COLOR_YELLOW},{88,188,COLOR_YELLOW}};*/
uint drawingTicks = 0;
u16 p = 0;
u8 keepDrawing = 1;
u8 segmentIndex = 1;

void titleInit()
{
	consoleClear();	   
	iprintf("\x1b[10;9HPress START or\n     touch the touch screen");      
}

void titleDraw()
{
	if(!keepDrawing) return;
	
	if(p == 350-2) keepDrawing = 0;

	if(drawingTicks > 500)
	{
		if(segments[segmentIndex] == p+1)
			segmentIndex++;
		else
			drawLine(pixels[p].x, pixels[p].y, pixels[p+1].x, pixels[p+1].y, pixels[p].color);
		
		drawingTicks = 0;
		p++;
		
	}
}

void titleUpdate()
{
	if(keepDrawing)
		drawingTicks += timerElapsed(0);

	if(releasedKeys & KEY_TOUCH || releasedKeys & KEY_START)
		setGameState(GAME_STATE_BREAKOUT);

}