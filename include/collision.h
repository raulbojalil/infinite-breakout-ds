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
