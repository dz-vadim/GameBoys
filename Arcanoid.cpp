#include <GameBoy.h>
#include "Arcanoid_blocks.h"
#include "Arcanoid.h"

extern GameBoy gb;

byte arcField[8][16];
byte arcBlocks[4][8];
int platformX = 2;
int platformY = 13;
int ballDirX = 1;
int ballDirY = 1;
int ballX;
int ballY;
int level = 1;
int levelCount = 3;
long time_game;
long clickTime;

void initArcanoidGame() {
  gb.begin(1);
  randomSeed(analogRead(4));

  generateLevel();
}

void arcanoidGameLoop() {
  if (millis() - time_game > 200) {
    gb.clearDisplay();
    fieldClear();
    drawBlocks(arcBlocks);
    drawPlatform();
    fieldDraw();

    dirBall();
    moveBall();

    checkLoose();
    checkWin();

    time_game = millis();
  }
  movePlatform();
}

void drawPlatform() {
  for (int x = 0; x < 3; x++) {
    arcField[x + platformX][platformY] = 1;
  }
}

void drawBlocks(byte arr[4][8]) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 4; y++) {
      if (arr[y][x] == 1) {
        arcField[x][y] = 1;
      }
    }
  }
}

void fieldDraw() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 16; y++) {
      if (arcField[x][y] == 1) {
        gb.drawPoint(x, y);
      }
    }
  }
}

void fieldClear() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 16; y++) {
      arcField[x][y] = 0;
    }
  }
}

void movePlatform() {
  if (millis() - clickTime > 100) {
    if (gb.getKey() == 5 && platformX < 5) {
      platformX++;
    } else if (gb.getKey() == 4 && platformX > 0) {
      platformX--;
    }
    clickTime = millis();
  }
}

void dirBall() {
  if (ballX == 0) ballDirX = 1;
  else if (ballX == 7) ballDirX = -1;

  if (arcField[ballX][ballY + 1] == 1 || arcField[ballX + ballDirX][ballY + 1] == 1) ballDirY = -1;

  if (arcField[ballX][ballY - 1] == 1 && ballDirY == -1) {
    arcBlocks[ballY - 1][ballX] = 0;
    ballDirY = 1;
  }
  if (arcField[ballX][ballY + 1] == 1) {
    arcBlocks[ballY + 1][ballX] = 0;
    ballDirY = -1;
  }
  if (arcField[ballX][ballY - 1] == 0 && arcField[ballX + ballDirX][ballY - 1] == 1 && ballDirY == -1) {
    arcBlocks[ballY - 1][ballX + ballDirX] = 0;
    ballDirY = 1;
  }
  if (arcField[ballX][ballY + 1] == 0 && arcField[ballX + ballDirX][ballY + 1] == 1) {
    arcBlocks[ballY + 1][ballX + ballDirX] = 0;
    ballDirX = -1;
  }

  if (ballY == 0) ballDirY = 1;
}

void moveBall() {
  ballX += ballDirX;
  ballY += ballDirY;
  gb.drawPoint(ballX, ballY);
}

void generateLevel() {
  ballX = random(0, 7);
  ballY = 7;

  switch (level) {
    case 1: memcpy(arcBlocks, blocks_level1, sizeof(arcBlocks)); break;
    case 2: memcpy(arcBlocks, blocks_level2, sizeof(arcBlocks)); break;
    case 3: memcpy(arcBlocks, blocks_level3, sizeof(arcBlocks)); break;
  }
}

void checkLoose() {
  if (ballY == 15) {
    gb.testMatrix(10);
    generateLevel();
  }
}

void checkWin() {
  int count = 0;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 4; y++) {
      if (arcBlocks[y][x] == 1) count++;
    }
  }

  if (count == 0) {
    level++;
    if (level > levelCount) level = 1;

    generateLevel();
  }
}