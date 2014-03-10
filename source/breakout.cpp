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
	
	ball.rect.x = (SCREEN_WIDTH/2) - (ball.rect.w/2);
	ball.rect.y = paddle.rect.y - ball.rect.h - BALL_Y_BOTTOM_OFFSET;
	ball.rect.w = BALL_SIZE;
	ball.rect.h = BALL_SIZE;
	
	//float angle = getAngleBetweenPoints(0, 20, 20,0);
	
	ball.sx = cos(0.7854)*BALL_SPEED;
	ball.sy = -sin(0.7854)*BALL_SPEED;
	ball.color = COLOR_YELLOW;
	
	u8 i;
	u8 row = 0;
	u8 col = 0;
	for(i=0; i < MAX_BRICKS; ++i)
	{
		Brick brick;
		brick.rect.w = BRICK_WIDTH;
		brick.rect.h = BRICK_HEIGHT;
		brick.rect.x = col*brick.rect.w;
		brick.rect.y = row;
		
		if(i < STARTING_BRICKS)		
			brick.alive = 1;
		else brick.alive = 0;
		
		brick.color = RANDOM_COLOR;
		bricks[i] = brick;
		
		col++;
		
		if(col == SCREEN_WIDTH/brick.rect.w)
		{
			col = 0;
			row += brick.rect.h;
		}
		
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

		//s16 distance = (ball.rect.x + ball.rect.w/2) - (paddle.rect.x + paddle.rect.w/2);
			
		/*float collisionAngle = (45 * distance) / (paddle.rect.w/2);
		
		ball.sx = cos(collisionAngle)*4;
		ball.sy = -sin(collisionAngle)*4;*/
	}
}

void handleBallBricksCollisions(Ball* ball)
{
	u8 numColls = 0;
	u8 i;
	for(i=0; i < MAX_BRICKS; ++i)
	{
		if(bricks[i].alive && rectsCollide(bricks[i].rect, ball->rect))
		{
			bricks[i].alive = 0;
			numColls++;
			
			s16 l = getDistanceOfLineInRect(ball->rect, bricks[i].rect.x, bricks[i].rect.y, bricks[i].rect.x, bricks[i].rect.y + bricks[i].rect.h);
			s16 t = getDistanceOfLineInRect(ball->rect, bricks[i].rect.x, bricks[i].rect.y, bricks[i].rect.x + bricks[i].rect.w, bricks[i].rect.y);
			s16 r = getDistanceOfLineInRect(ball->rect, bricks[i].rect.x + bricks[i].rect.w, bricks[i].rect.y, bricks[i].rect.x + bricks[i].rect.w, bricks[i].rect.y + bricks[i].rect.h);
			s16 b = getDistanceOfLineInRect(ball->rect, bricks[i].rect.x, bricks[i].rect.y + bricks[i].rect.h, bricks[i].rect.x + bricks[i].rect.w, bricks[i].rect.y + bricks[i].rect.h);
			
			u8 edge = 1; s16 max = t;
			if(l > t) { edge = 0; max = l; }
			if(r > max) { edge = 2; max = r; }
			if(b > max) { edge = 3; max = b; }
			
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
	}
	
	/*if(numColls > 1)
		iprintf("%d", numColls);*/
}

void addNewBricks()
{
	ticks += timerElapsed(0);

	if(ticks > newBricksSpeedTicks)
	{
		ticks = 0;

		u8 bricksLeftToAdd = 4;
		u8 i;

		for(i=0; i < MAX_BRICKS; ++i)
		{
			if(bricks[i].alive)
			{
				bricks[i].rect.y += bricks[i].rect.h;
				
			}
			else if(bricksLeftToAdd > 0)
			{
				bricks[i].alive = true;
				bricks[i].rect.x = (bricksLeftToAdd-1)*bricks[i].rect.w;
				bricks[i].rect.y = 0;
				bricksLeftToAdd --;
			}
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
 
void drawBrick(const Brick& brick)
{
	drawFilledRect(brick.rect.x, brick.rect.y, brick.rect.w, brick.rect.h, brick.color);
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
	
	u8 i;
	for(i=0; i < MAX_BRICKS; ++i)
	{
		if(bricks[i].alive)
			drawBrick(bricks[i]);
	}

	render();
}
