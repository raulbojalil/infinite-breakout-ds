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
