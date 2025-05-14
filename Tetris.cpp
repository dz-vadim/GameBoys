#include <GameBoy.h>
#include "Tetris.h"
#include "Blocks.h"

extern GameBoy gb;

byte blocks[4][4];
byte field[8][16];
int block_x;
int block_y;
long time;
long click_time;

void initTetrisGame() {
  gb.begin(1);
  randomSeed(analogRead(4));
  generate_block();
}

void tetrisGameLoop() {
  if (millis() - time > speed()) {
    gb.clearDisplay();
    drawBlock(blocks, block_x, block_y);
    drawField();
    moveBlock();
    checkCollision();
    checkLine();
    checkGameOver();
    time = millis();
  }
  control();
  delay(1);
}

void moveBlock() {
  block_y++;
}

void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[i][j] == 1) {
        gb.drawPoint(x + i, y + j);
      }
    }
  }
}

void rotateRight(byte arr[4][4]) {
  byte temp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp[i][j] = arr[j][3 - i];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      arr[i][j] = temp[i][j];
    }
  }
}

void rotateLeft(byte arr[4][4]) {
  byte temp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp[i][j] = arr[3 - j][i];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      arr[i][j] = temp[i][j];
    }
  }
}

void generate_block() {
  block_x = random(0, 4);
  block_y = 0;
  int num = random(0, 7);

  switch (num) {
    case 0: memcpy(blocks, I_Block, sizeof(blocks)); break;
    case 1: memcpy(blocks, L_Block, sizeof(blocks)); break;
    case 2: memcpy(blocks, O_Block, sizeof(blocks)); break;
    case 3: memcpy(blocks, S_Block, sizeof(blocks)); break;
    case 4: memcpy(blocks, Z_Block, sizeof(blocks)); break;
    case 5: memcpy(blocks, T_Block, sizeof(blocks)); break;
    case 6: memcpy(blocks, J_Block, sizeof(blocks)); break;
  }
}


void control() {
  int btn = gb.getKey();
  if (millis() - click_time > 300) {
    if (btn == 3) {
      rotateRight(blocks);
    } else if (btn == 4 && borderLeft()) {
      block_x--;
    } else if (btn == 5 && borderRight()) {
      block_x++;
    }
    click_time = millis();
  }
}

bool borderRight() {
for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (block_x + x >= 7 && blocks[x][y] == 1) {
        return false;
      }
    }
  }
  return true;
}

bool borderLeft() {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (block_x + x <= 0 && blocks[x][y] == 1) {
        return false;
      }
    }
  }
  return true;
}

void checkCollision() {
  for (int x = 0; x < 4; x++) {
    for (int y = 3; y > 0; y--) {
      if (y + block_y >= 15
            && blocks[x][y] == 1
          || y + block_y + 1 <= 15
               && field[x + block_x][y + block_y + 1] == 1
               && blocks[x][y] == 1) {
        saveBlockToField();
        checkGameOver();
        generate_block();
      }
    }
  }
}

void saveBlockToField() {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (blocks[x][y] == 1) {
        field[x + block_x][y + block_y] = 1;
      }
    }
  }
}

void drawField() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 16; y++) {
      if (field[x][y] == 1) {
        gb.drawPoint(x, y);
      }
    }
  }
}

void checkLine() {
  for (int y = 15; y >= 0; y--) {
    int ledInLine = 0;
    for (int x = 0; x < 8; x++) {
      if (field[x][y] == 1) {
        ledInLine++;
      }
    }
    if (ledInLine == 8) {
      deleteLine(y);
      y++;
    }
  }
}

void deleteLine(int y) {
  for (int x = 0; x < 8; x++) {
    field[x][y] = 0;
  }
  updateField(y);
}

void updateField(int point_y) {
  for (int y = point_y; y > 0; y--) {
    for (int x = 0; x < 8; x++) {
      field[x][y] = field[x][y - 1];
    }
  }
}

void checkGameOver() {
  for (int x = 0; x < 8; x++) {
    if (field[x][0] == 1) {
      gb.testMatrix(10);
      clearField();
    }
  }
}

void clearField() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 16; y++) {
      field[x][y] = 0;
    }
  }
}

int speed() {
  if (gb.getKey() == 6) return 100;
  else return 300;
}