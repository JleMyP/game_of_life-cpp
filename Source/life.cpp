#include "life.h"
#include "../JuceLibraryCode/JuceHeader.h"



Life::Life() : history(historySize) {}
Life::Life(unsigned int width, unsigned int height) : history(historySize) {
  resizeMap(width, height);
  newGame();
}


Life::~Life() {
  clear();

  delete[] map;
  delete[] newMap;
}


void Life::clear() {
  for (unsigned int x = 0; x < mapWidth; x++) {
    delete[] map[x];
    delete[] newMap[x];
  }
}


void Life::resizeMap(unsigned int width, unsigned int height) {
  if (mapWidth) clear();

  mapWidth = width;
  mapHeight = height;

  map = new cellType*[width];
  newMap = new cellType*[width];
  //history = new cellType**[historySize];

  for (unsigned int x = 0; x < width; x++) {
    map[x] = new cellType[height];
    newMap[x] = new cellType[height];
  }
}


void Life::newGame(bool empty) {
  frame = 0;
  generateMap(empty);
}


void Life::generateMap(bool empty) {
  unsigned int x, y;

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      map[x][y] = empty ? 0 : rand() % 2;
    }
  }
}



void Life::normalize(int& x, int& y) {
  if (x == mapWidth) x = 0;
  else if (x == -1) x = mapWidth - 1;

  if (y == mapHeight) y = 0;
  else if (y == -1) y = mapHeight - 1;
}


cellType Life::getCell(int x, int y) {
  normalize(x, y);
  return map[x][y] ? 1 : 0;
}


void Life::setCell(int x, int y, cellType v) {
  normalize(x, y);
  map[x][y] = v;
}


unsigned char Life::getSumMur(unsigned int x, unsigned int y) {
  unsigned char sum = 0;
  int xx, yy;

  for (xx = x - 1; xx < x + 2; xx++) {
    for (yy = y - 1; yy < y + 2; yy++) {
      sum += getCell(xx, yy);
    }
  }

  return sum - (map[x][y] ? 1 : 0);
}


void Life::step() {
  clock_t t = clock();

  unsigned int x, y;
  unsigned char sum;
  alive = 0;

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      sum = getSumMur(x, y);

      newMap[x][y] = (sum == 3 || map[x][y] && sum == 2) ? (map[x][y] < maxAge ? map[x][y] + 1 : maxAge) : 0;
    }
  }

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      alive += (map[x][y] = newMap[x][y]) ? 1 : 0;
    }
  }

  frame++;
  durationStep = clock() - t;
  //history.push_back(map);
}


void Life::back() {
  frame--;
}