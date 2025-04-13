#include <GameBoy.h>
#include "SnakeGame.h"
#include "RaceGame.h"
#include "Menu.h"

GameBoy gb;

int modeCount = 1;
int modes = 0;

void setup() {
  gb.begin(0);
  initSnakeGame();
  initRaceGame();
}

void loop() {
  int key = gb.getKey();
  if (key == 2 && modeSelect() == 0) {
    gb.clearDisplay();
    modes = 1;
  } else if (key == 2 && modeSelect() == 1) {
    gb.clearDisplay();
    modes = 2;
  } else if (key == 1) {
    gb.clearDisplay();
    modes = 0;
  }

  switch (modes) {
    case 0: menu(); break;
    case 1: raceGameLoop(); break;
    case 2: snakeGameLoop(); break;
  }
}
