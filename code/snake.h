#ifndef SNAKE_H
#define SNAKE_H

#include "gba.h"

#define SNAKE_LEFT 0
#define SNAKE_RIGHT 2

#define SNAKE_UP 0
#define SNAKE_DOWN 2

#define SNAKE_STOPPED 1

typedef struct SnakeNode SnakeNode;

struct SnakeNode
{
	SnakeNode* prev;
	int x;
	int y;
};

typedef struct
{
	SnakeNode head;
	SnakeNode* tail;
	int length;
	int nodeSize;
	int offsetX;
	int offsetY;
	int xVel;
	int yVel;
}Snake;

void InitSnake(Snake* snake, int nodeSize, int gridStartX, int gridStartY, int startX, int startY);
void DrawSnake(Snake* s);
void UpdateSnake(Snake* s);
void UpdateVelocityX(Snake* s, uint32 vel);
void UpdateVelocityY(Snake* s, uint32 vel);

#endif
