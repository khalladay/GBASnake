#include "snake.h"
#include "drawing.h"
#include <stdlib.h>
#include "text.h"
#include <string.h>


void InitSnake(Snake* snake, int startX, int startY, int maxLen)
{
    snake->head.x = startX;
    snake->head.y = startY;
    snake->length = 1;
    snake->xVel = SNAKE_RIGHT;
    snake->yVel = SNAKE_STOPPED;
    snake->lastXMov = SNAKE_RIGHT;
    snake->lastYMov = SNAKE_STOPPED;

    snake->tail = &snake->head;
    snake->tail->prev = NULL;

    memset(&snake->freeNodes[0], 0, sizeof(SnakeNode) * NUM_CELLS_X * NUM_CELLS_Y);
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
            if (getCellValue(newX, newY))
            {
                return 0;
            }

            curNode->x = newX;
            curNode->y = newY;

            s->lastXMov =  (s->xVel);
            s->lastYMov = (s->yVel);
            setCellValue(newX,newY,1);

            break;
        }

    }
    return 1;
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
              nodeSize, nodeSize, COL_YELLOW);

}

void ClearLooseNode(SnakeNode* n, int gridOffset, int nodeSize)
{
    drawRect2(gridOffset + n->x * nodeSize,
              gridOffset + n->y * nodeSize,
              nodeSize, nodeSize, COL_BLACK);

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
