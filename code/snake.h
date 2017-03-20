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
	SnakeNode* freeNodes;
	uint8* owningGrid;
	int length;
	int xVel;
	int yVel;
	int lastXMov;
	int lastYMov;
}Snake;

void InitSnake(Snake* snake, uint8* owningGrid, int startX, int startY, int maxLen);

void DrawSnake(Snake* s, int gridOffset, int nodeSize);
void ClearTail(Snake* s, int gridOffset, int nodeSize);
void DrawLooseNode(SnakeNode* node, int gridOffset, int nodeSize);
void ClearLooseNode(SnakeNode* node, int gridOffset, int nodeSize);

int IsCollidingWithNode(Snake* s, SnakeNode* node);
int IsCollidingWithSnake(Snake* s, int x, int y);
int UpdateSnake(Snake* s);
void UpdateVelocityX(Snake* s, int vel);
void UpdateVelocityY(Snake* s, int vel);
void AddNode(Snake* s);

#endif
