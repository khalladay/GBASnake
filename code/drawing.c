#include "drawing.h"

void drawRect(int left, int top, int right, int bottom, COLOR clr)
{
    uint32 width = right - left;
    uint32 height = bottom - top; //y increases near bottom in GBA land

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            drawPixel(left + x, top + y, clr);
        }
    }
}

void drawRect2(int left, int top, int width, int height, COLOR clr)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            drawPixel(left + x, top + y, clr);
        }
    }
}
