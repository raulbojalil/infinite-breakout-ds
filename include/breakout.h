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


#ifndef _BREAKOUT_H_
#define _BREAKOUT_H_

#include <nds.h>
#include "collision.h"

#define NEW_BRICKS_SPEED_TICKS 300000
#define NEW_BRICKS_ACCEL_TICKS 25000
#define NEW_BRICKS_MAX_SPEED_TICKS 100000
#define NEW_BRICKS_SCORE 5

#define MAX_BRICKS 32
#define STARTING_BRICKS 20

#define BALL_SPEED 6
#define PADDLE_SPEED 6

#define PADDLE_Y_BOTTOM_OFFSET 20
#define BALL_Y_BOTTOM_OFFSET 20

#define BALL_SIZE 10
#define PADDLE_WIDTH 50
#define PADDLE_HEIGHT 10
#define BRICK_WIDTH 64
#define BRICK_HEIGHT 20

#define FIELD_WIDTH (SCREEN_WIDTH >> 6)
#define FIELD_HEIGHT (MAX_BRICKS/FIELD_WIDTH)

 
typedef struct{
 
	u8 alive;
	u16 color;
	
} Brick;
  
typedef struct{
 
	Rectangle rect;
	u16 color;
	
} Paddle;
 
typedef struct{
 
	Rectangle rect;
	s16 sx;
	s16 sy;
	u16 color;
	
} Ball;

void breakoutInit();

void movePaddle(Paddle* paddle);
void moveBall(Ball* ball);
void reset();
void breakoutUpdate();

void drawPaddle(const Paddle& paddle);
void drawBrick(const Brick& brick);
void drawBall(const Ball& ball);
void breakoutDraw();


#endif
