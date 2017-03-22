#ifndef SNAKE_H
#define SNAKE_H

#include "gba.h"
#include "game.h"

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
	SnakeNode freeNodes[NUM_CELLS_Y * NUM_CELLS_X];
	int length;
	int xVel;
	int yVel;
	int lastXMov;
	int lastYMov;
}Snake;

void InitSnake(Snake* snake, int startX, int startY, int maxLen);

void DrawLooseNode(SnakeNode* node, int gridOffset, int nodeSize);
void ClearLooseNode(SnakeNode* node, int gridOffset, int nodeSize);

int IsCollidingWithNode(Snake* s, SnakeNode* node);
int UpdateSnake(Snake* s);
void UpdateVelocityX(Snake* s, int vel);
void UpdateVelocityY(Snake* s, int vel);
void AddNode(Snake* s);

#endif
