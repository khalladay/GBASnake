#include "game.h"
#include "snake.h"
#include <stdlib.h>
#include "input.h"
#include <string.h>
#include <time.h>
#include "drawing.h"

uint8 grid[NUM_CELLS_Y*NUM_CELLS_X];
uint8 gameState;

Snake snake;
SnakeNode targetNode;

const int gridStart = SIZE_FRAME + SIZE_PADDING;

void spawnTargetNode();


uint8 getCellValue(int x, int y)
{
    return grid[y * NUM_CELLS_X + x];
}

void setCellValue(int x, int y, uint8 value)
{
    grid[y * NUM_CELLS_X + x] = value;
}



int getGameState()
{
    return gameState;
}

int getFinalScore()
{
    return snake.length;
}


void tickAndDrawGame()
{
    if (snake.head.x > NUM_CELLS_X-1
        || snake.head.x < 0
        || snake.head.y > NUM_CELLS_Y-1
        || snake.head.y < 0 )
    {
        gameState = STATE_LOST;
        return;
    }

    //check for win conditions
    if (snake.length == NUM_CELLS_Y * NUM_CELLS_X)
    {
        gameState = STATE_WON;
        return;
    }

    if (snake.head.x == targetNode.x && snake.head.y == targetNode.y)
    {
        AddNode(&snake);
        AddNode(&snake);

        spawnTargetNode();

    }

    //clear the tail cell, it's the only part of
    //the grid that needs to clear
    drawRect2(gridStart + snake.tail->x * SIZE_CELL,
              gridStart + snake.tail->y * SIZE_CELL,
              SIZE_CELL, SIZE_CELL, COL_BLACK);

    setCellValue(snake.tail->x, snake.tail->y, 0);

    if (!UpdateSnake(&snake))
    {
        gameState = STATE_LOST;
        return;
    }

    drawRect2(gridStart + snake.head.x * SIZE_CELL,
              gridStart + snake.head.y * SIZE_CELL,
              SIZE_CELL, SIZE_CELL, COL_WHITE);

    setCellValue(snake.head.x, snake.head.y, 1);


}

void renderGame()
{
    spawnTargetNode();
}

void restartGame()
{
    gameState = STATE_PLAYING;
    srand(time(NULL));
    memset(&grid[0], 0, sizeof(uint32) * NUM_CELLS_Y * NUM_CELLS_X);

    int snakeStartX = NUM_CELLS_X/2 - 1;
	int snakeStartY = NUM_CELLS_Y/2 - 1;
	InitSnake(&snake, snakeStartX, snakeStartY, NUM_CELLS_Y * NUM_CELLS_X);

    //clear screen
    drawRect2(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_BLACK);

    //redraw frame
    COLOR frameCol = COL_LIME;
    const int PS = SIZE_PADDING+SIZE_FRAME;
    const int FRAME_RIGHT = SCREEN_WIDTH - PS;
    const int FRAME_LEFT = SIZE_PADDING;
    const int FRAME_TOP = SIZE_PADDING;
    const int FRAME_HEIGHT = SCREEN_HEIGHT - PS;
    drawRect2(FRAME_LEFT,  FRAME_TOP, 	SCREEN_WIDTH - (SIZE_PADDING) * 2, SIZE_FRAME, frameCol);
    drawRect2(FRAME_RIGHT, FRAME_TOP, 	SIZE_FRAME, SCREEN_HEIGHT - SIZE_PADDING * 2, frameCol);
    drawRect2(FRAME_LEFT,  FRAME_TOP, 	SIZE_FRAME, SCREEN_HEIGHT - SIZE_PADDING * 2, frameCol);
    drawRect2(FRAME_LEFT,  FRAME_HEIGHT, SCREEN_WIDTH - SIZE_PADDING * 2, SIZE_FRAME, frameCol);
    spawnTargetNode();
}

void spawnTargetNode()
{
	int tX = -1;
	int tY = -1;
	int lastR = -1;

	for (int y = 0; y < NUM_CELLS_Y; ++y)
	{
		for (int x = 0; x < NUM_CELLS_X; ++x)
		{
			uint16 r = rand();
			if (grid[y * NUM_CELLS_X + x] != 1)
			{
				if (tY == -1 || (r > lastR))
				{
					tY = y;
					tX = x;
					lastR = r;
				}
			}
		}
	}

	targetNode.x = tX;
	targetNode.y = tY;

    drawRect2 (gridStart + tX * SIZE_CELL,
               gridStart + tY * SIZE_CELL,
               SIZE_CELL, SIZE_CELL, COL_YELLOW);
}

void handleGameInput()
{
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
