#ifndef ARCANOID_H
#define ARCANOID_H

void initArcanoidGame();
void arcanoidGameLoop();
void drawPlatform();
void drawBlocks(byte arr[4][8]);
void fieldDraw();
void fieldClear();
void movePlatform();
void dirBall();
void moveBall();
void generateLevel();
void checkLoose();
void checkWin();

#endif