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
	int length;
	int nodeSize;
	int offsetX;
	int offsetY;
	int xVel;
	int yVel;
	int lastXMov;
	int lastYMov;
}Snake;

void InitSnake(Snake* snake, int nodeSize, int gridStartX, int gridStartY, int startX, int startY, int maxLen);
void DrawSnake(Snake* s);
void DrawLooseNode(Snake* s, SnakeNode* node);
int IsCollidingWithNode(Snake* s, SnakeNode* node);
int IsCollidingWithSelf(Snake* s);
void UpdateSnake(Snake* s);
void UpdateVelocityX(Snake* s, int vel);
void UpdateVelocityY(Snake* s, int vel);
void AddNode(Snake* s);

#endif
