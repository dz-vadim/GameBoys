#ifndef TETRIS_H
#define TETRIS_H

void initTetrisGame();
void tetrisGameLoop();
void moveBlock();
void drawBlock(byte arr[4][4], int x, int y);
void rotateRight(byte arr[4][4]);
void rotateLeft(byte arr[4][4]);
void generate_block();
void control();
void checkCollision();
void saveBlockToField();
void drawField();
void checkLine();
void deleteLine(int y);
void updateField(int point_y);
void checkGameOver();
void clearField();
int speed();
bool borderRight();
bool borderLeft();

#endif