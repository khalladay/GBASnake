#include "snake.h"
#include "drawing.h"
#include <stdlib.h>
#include "text.h"



void InitSnake(Snake* snake, int nodeSize, int gridStartX, int gridStartY, int startX, int startY, int maxLen)
{
    snake->head.x = startX;
    snake->head.y = startY;
    snake->nodeSize = nodeSize;
    snake->length = 1;
    snake->xVel = SNAKE_RIGHT;
    snake->yVel = SNAKE_STOPPED;
    snake->offsetX = gridStartX;
    snake->offsetY = gridStartY;
    snake->tail = &snake->head;
    snake->lastXMov = SNAKE_RIGHT;
    snake->lastYMov = SNAKE_STOPPED;
    snake->freeNodes = (SnakeNode*)malloc(sizeof(SnakeNode) * maxLen);
}

void DrawSnake(Snake* s)
{
    //draw the head, since it's new
    drawRect2(s->offsetX + s->head.x * s->nodeSize,
              s->offsetY + s->head.y * s->nodeSize,
              s->nodeSize, s->nodeSize, COL_WHITE);
}

void UpdateSnake(Snake* s)
{
    //clear tail cell since we're moving the tail
    drawRect2(s->offsetX + s->tail->x * s->nodeSize,
              s->offsetY + s->tail->y * s->nodeSize,
              s->nodeSize, s->nodeSize, COL_BLACK);

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
            curNode->x += (s->xVel - 1);
            curNode->y += (s->yVel - 1);
            s->lastXMov =  (s->xVel);
            s->lastYMov = (s->yVel);
            break;
        }

    }
}

int IsCollidingWithSelf(Snake* s)
{
    int headX = s->head.x;
    int headY = s->head.y;

    SnakeNode* curNode = s->tail;

    while(curNode != &s->head)
    {
        if (curNode->x == headX && curNode->y == headY)
        {
            return 1;
        }
        curNode = curNode->prev;
    }

    return 0;

}

void AddNode(Snake* s)
{
    SnakeNode* oldTail = s->tail;
    SnakeNode* newTail = &s->freeNodes[s->length-1];
    newTail->x = s->tail->x;
    newTail->y = s->tail->y;
    newTail->prev = s->tail;
    s->tail = newTail;
    s->length++;
}

void DrawLooseNode(Snake* s, SnakeNode* n)
{
    drawRect2(s->offsetX + n->x * s->nodeSize,
              s->offsetY + n->y * s->nodeSize,
              s->nodeSize, s->nodeSize, COL_WHITE);

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
