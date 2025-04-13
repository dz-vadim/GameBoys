#ifndef RACEGAME_H
#define RACEGAME_H

void initRaceGame();
void raceGameLoop();

void playerCar(int x, int y);
void enemyCar(int x, int y);
void clearPlayerCar(int x, int y);
void clearenemyCar(int x, int y);
void createLine(int y);
void clearLine(int y);
bool Collision(int my_x, int my_y, int enemy_x, int enemy_y);

#endif
