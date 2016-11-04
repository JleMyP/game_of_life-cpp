#include "life.h"



Life::Life() {}
Life::Life(int width, int height) {
  resizeMap(width, height);
  newGame();
}


Life::~Life() {
  clear();

  delete[] map;
  delete[] newMap;
  //delete[] prevMap;
  //delete[] history;
}


void Life::clear() {
  for (int x = 0; x < mapWidth; x++) {
    delete[] map[x];
    delete[] newMap[x];
    //delete[] prevMap[x];
  }
}


void Life::resizeMap(int width, int height) {
  if (mapWidth) clear();

  mapWidth = width;
  mapHeight = height;

  map = new cellType*[width];
  newMap = new cellType*[width];
  //prevMap = new cellType*[width];
  //history = new cellType**[historySize];

  for (int x = 0; x < width; x++) {
    map[x] = new cellType[height];
    newMap[x] = new cellType[height];
    //prevMap[x] = new unsigned char[height];
  }
}


void Life::newGame(bool empty) {
  frame = 0;
  generateMap(empty);
}


void Life::generateMap(bool empty) {
  int x, y;

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      map[x][y] = empty ? 0 : rand() % 2;
    }
  }
}


int Life::getCell(int x, int y) {
  if (x == mapWidth) x = 0;
  else if (x == -1) x = mapWidth - 1;

  if (y == mapHeight) y = 0;
  else if (y == -1) y = mapHeight - 1;

  return map[x][y];
}


int Life::getSumMur(int x, int y) {
  int sum = 0;
  int xx, yy;

  for (xx = x - 1; xx < x + 2; xx++) {
    for (yy = y - 1; yy < y + 2; yy++) {
      sum += getCell(xx, yy);
    }
  }

  return sum - map[x][y];
}


void Life::step() {
  clock_t t = clock();

  int x, y;
  int sum;
  alive = 0;

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      sum = getSumMur(x, y);

      newMap[x][y] = (sum == 3 || map[x][y] && sum == 2);
    }
  }

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      //prevMap[x][y] = map[x][y];
      alive += map[x][y] = newMap[x][y];
    }
  }

  frame++;
  durationStep = clock() - t;
}