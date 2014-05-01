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

#ifndef _DRAW_H_
#define _DRAW_H_

#include <nds.h>

#define COLOR_WHITE RGB15(31,31,31)
#define COLOR_BLACK RGB15(0,0,0)  
#define COLOR_RED RGB15(31,0,0)
#define COLOR_GREEN RGB15(0,31,0) 
#define COLOR_BLUE RGB15(0,0,31)  
#define COLOR_YELLOW RGB15(31,31,0)   
#define RANDOM_COLOR RGB15(rand()%31, rand()%31, rand()%31)

typedef struct {

	u8 x;
	u8 y;
	u16 color;

} Pixel;


void drawInit();
void drawPixelArray(Pixel* pixels, u16 length);
void drawFilledRect(s16 x, s16 y, u8 w, u8 h, u16 color);
void drawRect(u16 x, u16 y, u16 w, u16 h, u16 color);
void drawPixel(u8 x, u8 y, u16 color);
void drawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void drawFilledCircle(u8 rx, u8 ry, u8 radio, u16 color);
void clear();
void render();


#endif
