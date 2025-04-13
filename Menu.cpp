#include "Menu.h"
#include "GameBoy.h"

extern GameBoy gb;

int arrows[8][8] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 1, 1, 1, 0, 0, 1, 1, 1 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};

int car[8][8] = {
  { 0, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0 }
};

int snake[8][8] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 }
};

void menu() {
  // Ліва половина — стрілка
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j);
      gb.setLed(i, j, arrows[j][i]);
    }
  }

  // Права половина — залежить від вибраного режиму
  if (modeSelect() == 0) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        gb.wipePoint(i, j + 8);
        gb.setLed(i, j + 8, car[j][i]);
      }
    }
  }

  if (modeSelect() == 1) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        gb.wipePoint(i, j + 8);
        gb.setLed(i, j + 8, snake[j][i]);
      }
    }
  }
}

int modeSelect() {
  if (gb.getKey() == 4) {
    modeCount++;
    delay(250);
    if (modeCount > 1) modeCount = 0;
  } else if (gb.getKey() == 5) {
    modeCount--;
    delay(250);
    if (modeCount < 0) modeCount = 1;
  }
  return modeCount;
}
