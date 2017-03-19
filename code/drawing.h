#ifndef DRAWING_H
#define DRAWING_H

#include "gba.h"

inline void drawPixel (int x, int y, COLOR clr)
{
    vid_mem[y*SCREEN_WIDTH+x]= clr;
}

void drawRect(int left, int top, int right, int bottom, COLOR clr);
void drawRect2(int left, int top, int width, int height, COLOR clr);

#endif
