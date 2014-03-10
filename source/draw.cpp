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

/*void drawCircle(u8 rx, u8 ry, u8 radio, u16 color)
{
	u8 x,y;
	double d;//detail
	const double pi = 3.14159265; //more or less
	for(d=0; d<=2*pi; d+=0.01) //you can play with the value to be added to d
	{
		x=rx+(1*sin(d))*radio;
		y=ry+(1*sin(d+(pi/2)))*radio;
		drawPixel(x,y, color);
	}
}*/

void drawFilledCircle(u8 rx, u8 ry, u8 radius, u16 color)
{
	for(int y=-radius; y<=radius; y++)
		for(int x=-radius; x<=radius; x++)
			if(x*x+y*y <= radius*radius)
				drawPixel(rx+x,ry+y, color);
}

void drawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    int yStep = SCREEN_WIDTH;
    int xStep = 1;      
    int xDiff = x2 - x1;
    int yDiff = y2 - y1;
	int i = 0;
    int errorTerm = 0;
    int offset = y1 * SCREEN_WIDTH + x1; 
    
    //need to adjust if y1 > y2
    if (yDiff < 0)       
    {                  
       yDiff = -yDiff;   //absolute value
       yStep = -yStep;   //step up instead of down   
    }
    
    //same for x
    if (xDiff < 0) 
    {           
       xDiff = -xDiff;            
       xStep = -xStep;            
    }        
 
    //case for changes more in X than in Y	 
    if (xDiff > yDiff) 
    {                            
       for (i = 0; i < xDiff + 1; i++)
       {                           
          VRAM_A[offset] = color;  
 
          offset += xStep;           
 
          errorTerm += yDiff;     
 
          if (errorTerm > xDiff) 
          {  
             errorTerm -= xDiff;     
             offset += yStep;        
          }
       }
    }//end if xdiff > ydiff
    //case for changes more in Y than in X
    else 
    {                       
       for (i = 0; i < yDiff + 1; i++) 
       {  
          VRAM_A[offset] = color;   
 
          offset += yStep;           
 
          errorTerm += xDiff;    
 
          if (errorTerm > yDiff) 
          {     
             errorTerm -= yDiff;  
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
				//VRAM_A[xp + (yp*SCREEN_WIDTH)] = RGB15(31,31,31);
		}
	}

    /*u8 yp = y;
	u8 xp = x;
	
	for(yp=y; yp < y+h; ++yp )
	{
		
		for(xp=x; xp < x+w; ++xp )
		{
			if(xp == SCREEN_WIDTH - 1)
				break;
			
			drawPixel(xp, yp, color);
			//VRAM_A[xp + (yp*SCREEN_WIDTH)] = RGB15(31,31,31);
		}
	}*/

}
 
/*void draw_rect(u8 x, u8 y, u8 w, u8 h)
{
	
}*/
