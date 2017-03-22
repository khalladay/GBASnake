#ifndef GAME_H
#define GAME_H 1

#include "gba.h"

#define NUM_CELLS_X 22
#define NUM_CELLS_Y 14
#define SIZE_CELL 10
#define SIZE_FRAME 2
#define SIZE_PADDING 8

#define STATE_PLAYING 0
#define STATE_WON 1
#define STATE_LOST 2

int getGameState();
int getFinalScore();
void tickAndDrawGame();
void restartGame();

void handleGameInput();

uint8 getCellValue(int x, int y);
void setCellValue(int x, int y, uint8 value);


#endif
