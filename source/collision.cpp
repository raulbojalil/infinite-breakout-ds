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
#include <math.h>
#include "collision.h"

float getAngleBetweenPoints(s16 x1, s16 y1, s16 x2, s16 y2) //radians
{
	return -atan2(y2 - y1, x2 - x1);
}														 

u8 getDistanceOfLineInRect(const Rectangle& rect, s16 linex1, s16 liney1, s16 linex2, s16 liney2)
{
	s16 start;
	s16 end;

	if(linex1 == linex2) //vertical
	{
		if(linex1 < rect.x || linex1 > (rect.x + rect.w)) return 0;
		
		if(liney1 > liney2) { start = liney2; end = liney1; }
		else { start = liney1; end = liney2; }
		
		if(start < rect.y)
			start = rect.y;
			
		if(end > (rect.y + rect.h))
			end = rect.y + rect.h;
			
		return ((end - start) < 0) ? 0 : (end - start);

	}
	else if(liney1 == liney2) //horizontal
	{
		if(liney1 < rect.y || liney1 > (rect.y + rect.h)) return 0;
	
		if(linex1 > linex2) { start = linex2; end = linex1; }
		else { start = linex1; end = linex2; }
		
		if(start < rect.x)
			start = rect.x;
			
		if(end > (rect.x + rect.w))
			end = rect.x + rect.w;
			
		return ((end - start) < 0) ? 0 : (end - start);
	}
	
	return 0;
	//assert
}

u8 rectsCollide(const Rectangle& rect1, const Rectangle& rect2)
{
	u8 horizontalCollision = 0;
	u8 verticalCollision = 0;

	if(rect1.x < rect2.x && rect2.x < (rect1.x + rect1.w))
		horizontalCollision = 1;
    if(rect1.x < (rect2.x + rect2.w) && (rect2.x + rect2.w) < (rect1.x + rect1.w))
		horizontalCollision = 1;
	if(rect1.y < rect2.y && rect2.y < (rect1.y + rect1.h))
		verticalCollision = 1;
    if(rect1.y < (rect2.y + rect2.h) && (rect2.y + rect2.h) < (rect1.y + rect1.h))
		verticalCollision = 1;

	return horizontalCollision && verticalCollision;
}