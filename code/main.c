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
#include <string.h>

#define NUM_CELLS_X 22
#define NUM_CELLS_Y 14
const int SIZE_CELL = 10;
const int SIZE_FRAME = 2;
const int SIZE_PADDING = 8;

//22*14 = 308
//308 / 8 == 38.5
//if bit is set, snake exists there
//used for collision tests
uint8 grid[NUM_CELLS_Y*NUM_CELLS_X];

Snake snake;
SnakeNode targetNode;
void DrawFrame();
//has to make sure that the target node
//isn't occupied by snake
void SpawnTargetNode()
{
	int tX = -1;
	int tY = -1;


	for (int y = rand() % NUM_CELLS_Y; y < NUM_CELLS_Y; ++y)
	{
		if (tY == -1 || ((rand() % 50 - 10) > 25))
		{
			for (int x = rand() & NUM_CELLS_X; x < NUM_CELLS_X; ++x)
			{
				if (grid[y * NUM_CELLS_Y + x] != 1)
				{
					if (tX == -1)
					{
						tX = x;
						tY = y;
					}
					else if (rand() % 100 > 50)
					{
						tX = x;
						tY = y;
						break;
					}
				}
			}
		}
	}

	targetNode.x = tX;
	targetNode.y = tY;
}


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

void ClearTargetNode()
{

}

//bios call to set low power mode until next vblank
void WaitUntilVBlank()
{
	asm("swi 0x05");
}

void restart()
{
	static uint32 count = 0;
	time_t t;
    srand(count += rand() %10);
	int gridStart = SIZE_FRAME + SIZE_PADDING;

	memset(&grid[0], 0, sizeof(uint32) * NUM_CELLS_Y);
	int snakeStartX = NUM_CELLS_X/2 - 1;
	int snakeStartY = NUM_CELLS_Y/2 - 1;
	InitSnake(&snake, &grid[0], snakeStartX, snakeStartY , NUM_CELLS_Y * NUM_CELLS_X);
	SpawnTargetNode();

	for (int y = -1; y < NUM_CELLS_Y+1; ++y)
	{
		for (int x = -1; x < NUM_CELLS_X+1; ++x)
		{
			SnakeNode n;
			n.x = x;
			n.y = y;
			ClearLooseNode(&n, gridStart, SIZE_CELL);

		}
	}

	ClearLooseNode(&targetNode, gridStart, SIZE_CELL);
	write("Game Over", COL_BLACK, 25, 25);
	DrawFrame();


}

void DrawFrame()
{
	//draw game frame
		COLOR frameCol = COL_LIME;
		int gridStart = SIZE_FRAME + SIZE_PADDING;
		const int PS = SIZE_PADDING+SIZE_FRAME;
		const int FRAME_RIGHT = SCREEN_WIDTH - PS;
		const int FRAME_LEFT = SIZE_PADDING;
		const int FRAME_TOP = SIZE_PADDING;
		const int FRAME_HEIGHT = SCREEN_HEIGHT - PS;
		drawRect2(FRAME_LEFT,  FRAME_TOP, 	SCREEN_WIDTH - (SIZE_PADDING) * 2, SIZE_FRAME, frameCol);
		drawRect2(FRAME_RIGHT, FRAME_TOP, 	SIZE_FRAME, SCREEN_HEIGHT - SIZE_PADDING * 2, frameCol);
		drawRect2(FRAME_LEFT,  FRAME_TOP, 	SIZE_FRAME, SCREEN_HEIGHT - SIZE_PADDING * 2, frameCol);
		drawRect2(FRAME_LEFT,  FRAME_HEIGHT, SCREEN_WIDTH - SIZE_PADDING * 2, SIZE_FRAME, frameCol);

}

int main()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; //mode 3 graphics, we aren't actually using bg2 right now
	REG_IME = 1;					//enable interrupts
	//REG_IE |= IRQ_VBLANK;          // send interrupts at vblank

	restart();
	DrawFrame();

//setup game
int gridStart = SIZE_FRAME + SIZE_PADDING;


	int gameOver = 0;
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

		if (!gameOver)
		{
			ClearTail(&snake, gridStart, SIZE_CELL);

			if (!UpdateSnake(&snake))
			{
				gameOver = 1;
			}
		}

		if ( (snake.head.x > NUM_CELLS_X-1 ||
			snake.head.x < 0 ||
			snake.head.y > NUM_CELLS_Y-1 ||
			snake.head.y < 0 ) || gameOver)
		{
				write("Game Over", COL_RED, 25, 25);
				gameOver = 1;
		}

		DrawSnake(&snake, gridStart, SIZE_CELL);

		if (IsCollidingWithNode(&snake, &targetNode))
		{
			AddNode(&snake);
			SpawnTargetNode();
		}
		DrawLooseNode(&targetNode, gridStart, SIZE_CELL);

		if (gameOver)
		{
			if ( key_is_down(KEY_START))
			{
				restart();
				gameOver = 0;
			}
		}

	}

    return 0;
}
