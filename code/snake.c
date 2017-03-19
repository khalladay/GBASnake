#include "snake.h"
#include "drawing.h"
#define NULL 0

void InitSnake(Snake* snake, int nodeSize, int gridStartX, int gridStartY, int startX, int startY)
{
    snake->head.x = startX;
    snake->head.y = startY;
    snake->nodeSize = nodeSize;
    snake->xVel = SNAKE_RIGHT;
    snake->yVel = SNAKE_STOPPED;
    snake->offsetX = gridStartX;
    snake->offsetY = gridStartY;
    snake->tail = &snake->head;
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

        }
        else
        {
            curNode->x += (s->xVel - 1);
            curNode->y += (s->yVel - 1);
            break;
        }

    }
}

void UpdateVelocityX(Snake* s, uint32 vel)
{
    s->xVel = vel;
    s->yVel = SNAKE_STOPPED;

}

void UpdateVelocityY(Snake* s, uint32 vel)
{
    s->xVel = SNAKE_STOPPED;
    s->yVel = vel;

}
