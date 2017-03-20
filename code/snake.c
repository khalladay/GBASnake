#include "snake.h"
#include "drawing.h"
#include <stdlib.h>
#include "text.h"



void InitSnake(Snake* snake, uint8* grid, int startX, int startY, int maxLen)
{
    snake->head.x = startX;
    snake->head.y = startY;
    snake->length = 1;
    snake->xVel = SNAKE_RIGHT;
    snake->yVel = SNAKE_STOPPED;
    snake->tail = &snake->head;
    snake->lastXMov = SNAKE_RIGHT;
    snake->lastYMov = SNAKE_STOPPED;
    snake->freeNodes = (SnakeNode*)malloc(sizeof(SnakeNode) * maxLen);
    snake->owningGrid = grid;
}

void ClearTail(Snake* s, int gridOffset, int nodeSize)
{
    //clear tail cell since we're moving the tail
    drawRect2(gridOffset + s->tail->x * nodeSize,
              gridOffset + s->tail->y * nodeSize,
              nodeSize, nodeSize, COL_BLACK);
    s->owningGrid[s->tail->y * 14 + s->tail->x] = 0;

}

void DrawSnake(Snake* s, int gridOffset,int nodeSize)
{
    //draw the head, since it's new
    drawRect2(gridOffset + s->head.x * nodeSize,
              gridOffset + s->head.y * nodeSize,
              nodeSize, nodeSize, COL_WHITE);
}

int UpdateSnake(Snake* s)
{
    SnakeNode* curNode = s->tail;

    while(curNode != NULL)
    {
        SnakeNode* prev = curNode->prev;
        if (prev != NULL)
        {
            curNode->x = prev->x;
            curNode->y = prev->y;
            curNode = curNode->prev;
        }
        else
        {
            int newX = curNode->x + (s->xVel - 1);
            int newY = curNode->y + (s->yVel - 1);

            //are we about to collide with ourselves?
            if (IsCollidingWithSnake(s, newX, newY))
            {
                return 0;
            }

            curNode->x = newX;
            curNode->y = newY;

            s->lastXMov =  (s->xVel);
            s->lastYMov = (s->yVel);
            s->owningGrid[curNode->y * 14 + curNode->x] = 1;

            break;
        }

    }
    return 1;
}

int IsCollidingWithSnake(Snake* s, int x, int y)
{
    SnakeNode* curNode = s->tail;
    while(curNode != NULL)
    {
        SnakeNode* prev = curNode->prev;
        if(prev != NULL)
        {
            if (curNode->x == x && curNode->y == y)
            {
                return 1;
            }
        }
        curNode = curNode->prev;

    }

    return 0;

}

void AddNode(Snake* s)
{
    SnakeNode* newTail = &s->freeNodes[s->length-1];
    newTail->x = s->tail->x;
    newTail->y = s->tail->y;
    newTail->prev = s->tail;
    s->tail = newTail;
    s->length++;
}

void DrawLooseNode(SnakeNode* n, int gridOffset, int nodeSize)
{
    drawRect2(gridOffset + n->x * nodeSize,
              gridOffset + n->y * nodeSize,
              nodeSize, nodeSize, COL_WHITE);

}

int IsCollidingWithNode(Snake* s, SnakeNode* node)
{
    return s->head.x == node->x && s->head.y == node->y;
}


void UpdateVelocityX(Snake* s, int vel)
{
    if (s->lastXMov == SNAKE_STOPPED)
    {
        s->xVel = vel;
        s->yVel = SNAKE_STOPPED;
    }
}

void UpdateVelocityY(Snake* s, int vel)
{
    if (s->lastYMov == SNAKE_STOPPED)
    {
        s->xVel = SNAKE_STOPPED;
        s->yVel = vel;
    }
}
