// First demo. You are not expected to understand it
// (don't spend too much time trying and read on).
// But if you do understand (as a newbie): wow!

#include "gba.h"
#include "drawing.h"
#include "text.h"
#include "input.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
SnakeNode targetNode;

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

void SpawnTargetNode()
{
	targetNode.x = rand() % 21;
	targetNode.y = rand() % 11;
	DrawLooseNode(&snake, &targetNode);
}

//bios call to set low power mode until next vblank
void WaitUntilVBlank()
{
	asm("swi 0x05");
}

int main()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; //mode 3 graphics, we aren't actually using bg2 right now
	REG_IME = 1;					//enable interrupts
	//REG_IE |= IRQ_VBLANK;          // send interrupts at vblank

	srand(time(0));
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

	InitSnake(&snake, cellSize, gridStart, gridStart, 3, 2, 22*14);
	SpawnTargetNode();
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

		if ( snake.head.x > 20 ||
			snake.head.x < 0 ||
			snake.head.y > 12 ||
			snake.head.y < 0 )
			{
				write("Game Over", COL_RED, 25, 25);
			}
		else
		{
			UpdateSnake(&snake);
			DrawSnake(&snake);

		}

		if (IsCollidingWithNode(&snake, &targetNode))
		{
			AddNode(&snake);

			SpawnTargetNode();
		}



	}

    return 0;
}
