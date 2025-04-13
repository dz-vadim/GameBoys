#include "RaceGame.h"
#include "GameBoy.h"

extern GameBoy gb;

int enemy_x = 2;
int car_speed = 100;
int player_x = 2;
int player_y = 12;

void initRaceGame() {
  player_x = 2;
  player_y = 12;
  car_speed = 100;
  playerCar(player_x, player_y);
}

void enemyCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y - 1);
  gb.drawPoint(x - 1, y - 1);
  gb.drawPoint(x + 1, y - 1);
  gb.drawPoint(x, y - 2);
  gb.drawPoint(x - 1, y - 3);
  gb.drawPoint(x + 1, y - 3);
}

void playerCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
}

void clearenemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x, y - 2);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
}

void clearPlayerCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
}

void createLine(int y) {
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);
  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}

void clearLine(int y) {
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);
  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}

bool Collision(int my_x, int my_y, int enemy_x, int enemy_y) {
  if (my_x == enemy_x && my_y == enemy_y) return true;
  if (enemy_y > 12 && my_x == enemy_x) return true;
  return false;
}

void raceGameLoop() {
  enemy_x = random(0, 10);
  enemy_x = (enemy_x < 5) ? 2 : 5;

  for (int enemy_y = 0; enemy_y < 16; enemy_y++) {
    enemyCar(enemy_x, enemy_y);
    for (int offset = -15; offset < 16; offset += 5)
      createLine(enemy_y + offset);

    int key = gb.getKey();
    if (key == 4) {
      player_x = 2;
      clearPlayerCar(5, 12);
      playerCar(2, 12);
    } else if (key == 5) {
      player_x = 5;
      clearPlayerCar(2, 12);
      playerCar(5, 12);
    }

    if (Collision(player_x, player_y, enemy_x, enemy_y)) {
      gb.sound(COLLISION);
      gb.testMatrix(10);
      car_speed = 100;
      return;
    }

    if (enemy_y > 14) {
      gb.sound(SCORE);
      car_speed -= 1;
      if (car_speed == 1) {
        for (int i = 0; i < 10; i++) gb.sound(SCORE);
        car_speed = 100;
        gb.clearDisplay();
        return;
      }
    }

    delay(car_speed);
    for (int offset = -15; offset < 16; offset += 5)
      clearLine(enemy_y + offset);
    clearenemyCar(enemy_x, enemy_y);
  }
}
