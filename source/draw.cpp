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

#include "draw.h"
#include <nds.h>
#include <math.h>

u8 videoMode = 1;

void drawInit()
{
	videoSetMode(MODE_FB0); //VRAM_A
	//videoMode = 0;
	//enable VRAM A for writing by the cpu and use 
	//as a framebuffer by video hardware
	
	//se usa intercalación para lograr que en un frame un banco sea el backbuffer y el otro el displaybuffer y viceversa
	vramSetBankA(VRAM_A_LCD);
	vramSetBankB(VRAM_B_LCD); 
	
    clear();
}

void drawPixelArray(Pixel* pixels, u16 length)
{
	u16 p;
	for(p = 0; p < length-1; p++)
	{
		drawLine(pixels[p].x, pixels[p].y, pixels[p+1].x, pixels[p+1].y, pixels[p].color);
		//drawPixel(pixels[p].x, pixels[p].y, pixels[p].color);
	}
}

void drawPixel(u8 x, u8 y, u16 color)
{
	//backBuffer[x + (y*SCREEN_WIDTH)] = color;
	//VRAM_A[x + (y*SCREEN_WIDTH)] = color;
	
	if(videoMode == 0)
		VRAM_A[x + (y*SCREEN_WIDTH)] = color;
	else 
		VRAM_B[x + (y*SCREEN_WIDTH)] = color;
}

void clear()
{
	u16 i;
	for(i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; ++i)
	{
		//VRAM_B[i] = COLOR_BLACK;
		if(videoMode == 0)
			VRAM_A[i] = COLOR_BLACK;
		else
			VRAM_B[i] = COLOR_BLACK;
		//backBuffer[i] = COLOR_BLACK;
	}
}

void render()
{
	if(videoMode == 0)
	{
		videoMode = 1;
		videoSetMode(MODE_FB0);
	}
	else
	{
		videoMode = 0;
		videoSetMode(MODE_FB1);
	}
}


void drawFilledCircle(u8 rx, u8 ry, u8 radius, u16 color)
{
	for(int y=-radius; y<=radius; y++)
		for(int x=-radius; x<=radius; x++)
			if(x*x+y*y <= radius*radius)
				drawPixel(rx+x,ry+y, color);
}

void drawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    s32 yStep = SCREEN_WIDTH;
    s32 xStep = 1;      
    s32 xDiff = x2 - x1;
    s32 yDiff = y2 - y1;
	s32 i = 0;
    s32 error = 0;
    s32 offset = y1 * SCREEN_WIDTH + x1; 
    
    if (yDiff < 0)       
    {                  
       yDiff = -yDiff;
       yStep = -yStep;  
    }
    
    if (xDiff < 0) 
    {           
       xDiff = -xDiff;            
       xStep = -xStep;            
    }        
 
    if (xDiff > yDiff) 
    {                            
       for (i = 0; i < xDiff + 1; i++)
       {                           
          VRAM_A[offset] = color;  
          offset += xStep;           
          error += yDiff;     
          if (error > xDiff) 
          {  
             error -= xDiff;     
             offset += yStep;        
          }
       }
    }
    else 
    {                       
       for (i = 0; i < yDiff + 1; i++) 
       {  
          VRAM_A[offset] = color;   
          offset += yStep;           
          error += xDiff;    
          if (error > yDiff) 
          {     
             error -= yDiff;  
             offset += xStep;
          }
       }
    }
 
}

void drawRect(u16 x, u16 y, u16 w, u16 h, u16 color){

    drawLine(x,y, x+w, y, color);
	drawLine(x,y, x, y+h, color);
	drawLine(x+w,y+h, x+w, y, color);
	drawLine(x+w,y+h, x, y+h, color);

}

void drawFilledRect(s16 x, s16 y, u8 w, u8 h, u16 color){
	
	s16 yp;
	s16 xp;

	for(yp=y; yp < y+h; ++yp )
	{
		for(xp=x; xp < x+w; ++xp )
		{
			if(xp > 0 && xp < SCREEN_WIDTH && yp > 0 && yp < SCREEN_HEIGHT)
				drawPixel(xp, yp, color);
		}
	}
}