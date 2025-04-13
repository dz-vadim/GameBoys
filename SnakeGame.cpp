#include "SnakeGame.h"
#include "GameBoy.h"

extern GameBoy gb;

const int maxLenSnake = 128;
int snakeX[maxLenSnake], snakeY[maxLenSnake];
int foodX, foodY;
int lenSnake = 3;

enum direction { up, right, down, left };
direction dir = right;

void makeFood() {
  foodX = random(8);
  foodY = random(16);
}

void move() {
  for (int i = lenSnake - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  if (dir == up) snakeY[0] = (snakeY[0] == 0) ? 15 : snakeY[0] - 1;
  if (dir == down) snakeY[0] = (snakeY[0] == 15) ? 0 : snakeY[0] + 1;
  if (dir == left) snakeX[0] = (snakeX[0] == 0) ? 7 : snakeX[0] - 1;
  if (dir == right) snakeX[0] = (snakeX[0] == 7) ? 0 : snakeX[0] + 1;
}

void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
  }
}

void makeMove() {
  int key = gb.getKey();
  if (key == 4) dir = left;
  if (key == 5) dir = right;
  if (key == 3) dir = up;
  if (key == 6) dir = down;
}

void spawnFood() {
  gb.drawPoint(foodX, foodY);
}

bool compareSnake() {
  for (int i = 1; i < lenSnake; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) return true;
  }
  return false;
}

void initSnakeGame() {
  lenSnake = 3;
  snakeX[0] = 4;
  snakeY[0] = 7;
  makeFood();
}

void snakeGameLoop() {
  makeMove();
  move();
  gb.clearDisplay();
  drawSnake();
  spawnFood();

  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    lenSnake++;
    makeFood();
  }

  if (compareSnake()) {
    gb.sound(COLLISION);
    gb.testMatrix(10);
    delay(2000);
    initSnakeGame();
  }

  delay(250);
}
