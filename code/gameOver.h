#ifndef GAMEOVER_H
#define GAMEOVER_H

#define END_PLAYING 0
#define END_RESTART 1

void SetMatchResult(int didPlayerWin);

void beginGameOverScreen();
void handleGameOverInput();
int getGameOverState();


#endif
