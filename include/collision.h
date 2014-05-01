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

#ifndef _COLLISION_H_
#define _COLLISION_H_

typedef struct{

	s16 x;
	s16 y;
	u8 w;
	u8 h;

} Rectangle;

u8 rectsCollide(const Rectangle& rect1, const Rectangle& rect2);
u8 getDistanceOfLineInRect(const Rectangle& rect, s16 linex1, s16 liney1, s16 linex2, s16 liney2);
float getAngleBetweenPoints(s16 x1, s16 y1, s16 x2, s16 y2); //radians

#endif
