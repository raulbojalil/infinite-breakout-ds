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
#include <stdio.h>
#include "draw.h"
#include "game.h"
#include "breakout.h"

Brick bricks[MAX_BRICKS];
Paddle paddle;
Ball ball;
  
u16 score;
u8 gameOver;
uint ticks;
u8 playing;

s16 lastBallPosX;
s16 lastBallPosY;

uint newBricksSpeedTicks;


void movePaddle(Paddle* paddle)
{
	if(paddleIsInserted())
	{
		paddle->rect.x += paddleAccel;
		
		if(paddle->rect.x < 0)
				paddle->rect.x = 0;
		if(paddle->rect.x > SCREEN_WIDTH - paddle->rect.w)
				paddle->rect.x = SCREEN_WIDTH - paddle->rect.w;
			//paddle->rect.x = touchpos;
	}
	else
	{
		if(pressedKeys & KEY_TOUCH)
		{
			s16 tp = touchPos.px - (paddle->rect.w/2);
			if(tp < 0) tp = 0;
			else if(tp > SCREEN_WIDTH - paddle->rect.w)
				tp = SCREEN_WIDTH - paddle->rect.w;
			
			if(paddle->rect.x < tp)
			{
				paddle->rect.x += PADDLE_SPEED;
				if(paddle->rect.x > tp)
					paddle->rect.x = tp;
			}
			else if(paddle->rect.x > tp)
			{
				paddle->rect.x -= PADDLE_SPEED;
				if(paddle->rect.x < tp)
					paddle->rect.x = tp;
			}
		
		}
		else
		{
			if(pressedKeys & KEY_LEFT)
			{
				//clear();
				paddle->rect.x -= PADDLE_SPEED;
				if(paddle->rect.x < 0)
					paddle->rect.x = 0;
			}
			else if(pressedKeys & KEY_RIGHT)
			{
				//clear();
				paddle->rect.x += PADDLE_SPEED;
				if(paddle->rect.x > SCREEN_WIDTH - paddle->rect.w)
					paddle->rect.x = SCREEN_WIDTH - paddle->rect.w;
			}
		}
	}
}

void moveBall(Ball* ball)
{
	ball->rect.x += ball->sx;
	ball->rect.y += ball->sy;
	
	
	if((ball->rect.x <= 0 && ball->sx < 0) || ((ball->rect.x + ball->rect.w) > SCREEN_WIDTH && ball->sx > 0))
		ball->sx*=-1;
	
	if((ball->rect.y <= 0 && ball->sy < 0))
		ball->sy*=-1;
		
	if(((ball->rect.y + ball->rect.h) > SCREEN_HEIGHT && ball->sy > 0))
	{
		gameOver = 1;
		consoleClear();
		iprintf("\x1b[10;11HGAME OVER\n\n       Your score: %05i\n\nPress the A button to play again", score);
	}
	
}

void reset()
{
	playing = 0;
	score = 0;
	gameOver = 0;
	ticks = 0;
	
	newBricksSpeedTicks = NEW_BRICKS_SPEED_TICKS;

	paddle.rect.w = PADDLE_WIDTH;
	paddle.rect.h = PADDLE_HEIGHT;
	paddle.rect.x = (SCREEN_WIDTH/2) - (paddle.rect.w/2);
	paddle.rect.y = SCREEN_HEIGHT - paddle.rect.h - PADDLE_Y_BOTTOM_OFFSET;
	paddle.color = COLOR_YELLOW;
	
	ball.rect.w = BALL_SIZE;
	ball.rect.h = BALL_SIZE;
	ball.rect.x = (SCREEN_WIDTH/2) - (ball.rect.w/2);
	ball.rect.y = paddle.rect.y - ball.rect.h - BALL_Y_BOTTOM_OFFSET;
	
	
	//float angle = getAngleBetweenPoints(0, 20, 20,0);
	
	ball.sx = cos(0.7854)*BALL_SPEED;
	ball.sy = -sin(0.7854)*BALL_SPEED;
	ball.color = COLOR_YELLOW;
	
	u8 i;
	//u8 row = 0;
	//u8 col = 0;
	for(i=0; i < MAX_BRICKS; ++i)
	{
		Brick brick;
		
		if(i < STARTING_BRICKS)		
			brick.alive = 1;
		else brick.alive = 0;
		
		brick.color = RANDOM_COLOR;
		bricks[i] = brick;
	}
	
	consoleClear();
	iprintf("\x1b[20;2HTouch to control the paddle");
}

void breakoutInit()
{
	reset();
}

void handleBallPaddleCollision(Ball* ball, Paddle* paddle)
{
	if(rectsCollide(paddle->rect, ball->rect))
	{
		ball->rect.y = paddle->rect.y - ball->rect.h;
	
		//TODO: Mejorar
		float collisionAngle = getAngleBetweenPoints(paddle->rect.x + (paddle->rect.w/2), 
													 paddle->rect.y + (paddle->rect.h/2),
													 ball->rect.x + (ball->rect.w/2),
													 ball->rect.y + (ball->rect.h/2));

		ball->sx = cos(collisionAngle)*BALL_SPEED;
		ball->sy = -sin(collisionAngle)*BALL_SPEED;
	}
}

void handleBallBricksCollisions(Ball* ball)
{
	u8 leftEdge = 0;
	u8 topEdge = 0;
	u8 rightEdge = 0;
	u8 bottomEdge = 0;
	s16 collidingBrickIndex = -1;
	
	u8 row;
	u8 col;
	u8 i;

	for(row=0; row < FIELD_HEIGHT; ++row)
	{
		for(col=0; col < FIELD_WIDTH; ++col)
		{
			i = (row*FIELD_WIDTH) + col;

			if(bricks[i].alive)
			{
				u8 brickX = col*BRICK_WIDTH;
				u8 brickY = row*BRICK_HEIGHT;
			
				if((brickY + BRICK_HEIGHT) < ball->rect.y) continue;
				if((ball->rect.y + BALL_SIZE) < brickY) continue;
				if((brickX + BRICK_WIDTH) < ball->rect.x) continue;
				if((ball->rect.x + BALL_SIZE) < brickX) continue;
		
				if(ball->rect.x < brickX)
				{
					u8 d = getDistanceOfLineInRect(ball->rect, brickX, brickY, brickX, brickY + BRICK_HEIGHT);
					if(d > leftEdge) { collidingBrickIndex = i; leftEdge = d; }
				}

				if(ball->rect.y < brickY)
				{
					u8 d = getDistanceOfLineInRect(ball->rect, brickX, brickY, brickX + BRICK_WIDTH, brickY);
					if(d > topEdge) { collidingBrickIndex = i; topEdge = d; }
				}

				if(ball->rect.x > brickX)
				{
					u8 d = getDistanceOfLineInRect(ball->rect, brickX + BRICK_WIDTH, brickY, brickX + BRICK_WIDTH, brickY + BRICK_HEIGHT); 
					if(d > rightEdge) { collidingBrickIndex = i; rightEdge = d; } 
				}

				if(ball->rect.y > brickY)
				{
					u8 d = 	getDistanceOfLineInRect(ball->rect, brickX, brickY + BRICK_HEIGHT, brickX + BRICK_WIDTH, brickY + BRICK_HEIGHT);
					if(d > bottomEdge) { collidingBrickIndex = i; bottomEdge = d; }
				}
			}
		}
	}

	if(collidingBrickIndex != -1)
	{
		bricks[collidingBrickIndex].alive = 0;
		ball->rect.x = lastBallPosX;
		ball->rect.y = lastBallPosY;

		u8 edge = 1; 
		s16 max = topEdge;
		if(leftEdge > topEdge) { edge = 0; max = leftEdge; }
		if(rightEdge > max) { edge = 2; max = rightEdge; }
		if(bottomEdge > max) { edge = 3; }
			
		if(edge == 0 || edge == 2) //izquierda o derecha
			ball->sx*=-1;
		else 
			ball->sy*=-1; //arriba o abajo
			
		score++;
			
		if(score % NEW_BRICKS_SCORE == 0)	
		{
			if(newBricksSpeedTicks >= NEW_BRICKS_MAX_SPEED_TICKS)
				newBricksSpeedTicks -= 	NEW_BRICKS_ACCEL_TICKS;
		}
				
		iprintf("\x1b[1;1HScore = %05i\n", score);
	}
	
	lastBallPosX = ball->rect.x;
	lastBallPosY = ball->rect.y;

}

void addNewBricks()
{
	ticks += timerElapsed(0);

	if(ticks > newBricksSpeedTicks)
	{
		ticks = 0;
		s16 i;

		for(i=MAX_BRICKS-1; i >= 0; i--)
		{
			if(bricks[i].alive)
			{
				if(i+FIELD_WIDTH >= MAX_BRICKS) return; 
				bricks[i+FIELD_WIDTH] = bricks[i];
				bricks[i].alive = 0;	
			}
		}
		
		for(i=0; i < FIELD_WIDTH; i++)
		{
			bricks[i].alive = 1;
			bricks[i].color = RANDOM_COLOR;
		}
	
	}
}

void breakoutUpdate()
{
	if(gameOver)
	{
		if(releasedKeys & KEY_TOUCH || releasedKeys & KEY_A)
			reset();	
	}
	else if(playing)
	{
		movePaddle(&paddle);
		moveBall(&ball);
		
		handleBallBricksCollisions(&ball);
		handleBallPaddleCollision(&ball, &paddle);
		
		addNewBricks();
	}
	else
	{
		ticks += timerElapsed(0);
		if(ticks > 50000 || releasedKeys & KEY_TOUCH || releasedKeys & KEY_A)
			playing = 1;
	}
}
  
void drawPaddle(const Paddle& paddle)
{
	drawFilledRect(paddle.rect.x, paddle.rect.y, paddle.rect.w, paddle.rect.h, paddle.color);
}
 
void drawBrick(u8 row, u8 col, const Brick& brick)
{
	drawFilledRect(col * BRICK_WIDTH, row * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT, brick.color);
}

void drawBall(const Ball& ball)
{
	drawFilledRect(ball.rect.x, ball.rect.y, ball.rect.w, ball.rect.h, ball.color);
}

void breakoutDraw()
{
	clear();

	drawPaddle(paddle);
	drawBall(ball);
	
	u8 row;
	u8 col;
	for(row=0; row < FIELD_HEIGHT; ++row)
	{
		for(col=0; col < FIELD_WIDTH; ++col)
		{
			if(bricks[(row*FIELD_WIDTH) + col].alive)
				drawBrick(row, col, bricks[(row*FIELD_WIDTH) + col]);
		}
	}

	render();
}
