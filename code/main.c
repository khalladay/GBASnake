// First demo. You are not expected to understand it
// (don't spend too much time trying and read on).
// But if you do understand (as a newbie): wow!

#include "gba.h"
#include "drawing.h"
#include "text.h"
#include "input.h"
#include "snake.h"
#include <stdio.h>

int x = 0;
void update()
{
	x++;
	drawPixel( 120+x, 80, RGB15(31, 0, 0) );    // or CLR_RED
	//REG_IF = IRQ_HBLANK;

}

void vsync()
{
  while (REG_VCOUNT >= 160);
  while (REG_VCOUNT < 160);
}

Snake snake;

void processInput()
{
	key_poll();
	if (key_curr_state() != key_prev_state())
	{
		if (key_is_down(KEY_RIGHT))
		{
			UpdateVelocityX(&snake, SNAKE_RIGHT);
		}
		else if (key_is_down(KEY_LEFT))
		{
			UpdateVelocityX(&snake, SNAKE_LEFT);
		}

		if (key_is_down(KEY_UP))
		{
			UpdateVelocityY(&snake, SNAKE_UP);
		}
		else if (key_is_down(KEY_DOWN))
		{
			UpdateVelocityY(&snake, SNAKE_DOWN);
		}
	}

}


int main()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

//draw game frame
	int frameWidth = 2;
	int padding = 8;
	COLOR frameCol = COL_LIME;

	int gridStart = frameWidth + padding;
	int cellSize = 10;

	drawRect2(padding, padding, SCREEN_WIDTH - (padding) * 2, frameWidth, frameCol);
	drawRect2(padding, padding, frameWidth, SCREEN_HEIGHT - padding * 2, frameCol);
	drawRect2(SCREEN_WIDTH - (padding+frameWidth), padding, frameWidth, SCREEN_HEIGHT - padding * 2, frameCol);
	drawRect2(padding, SCREEN_HEIGHT - padding, SCREEN_WIDTH - padding * 2, frameWidth, frameCol);

	InitSnake(&snake, cellSize, gridStart, gridStart, 3, 2);

    while(1)
	{
		vsync();
		processInput();
		vsync();
		processInput();

		vsync();
		processInput();

		vsync();
		processInput();

		if (snake.head.x > 20 ||
			snake.head.x < 1 ||
			snake.head.y > 12 ||
			snake.head.y < 1 )
			{

			}
			else
		{
			UpdateSnake(&snake);
			DrawSnake(&snake);
		}



	}

    return 0;
}
