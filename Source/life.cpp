#include "life.h"
#include "../JuceLibraryCode/JuceHeader.h"



Life::Life(): history(historySize) {}
Life::Life(unsigned int width, unsigned int height): history(historySize) {
  resizeMap(width, height);
  newGame();
}


Life::~Life() {
  clear();
  clearHistory();

  delete[] map;
  delete[] newMap;
}


void Life::clear() {
  for (unsigned int x = 0; x < mapWidth; x++) {
    delete[] map[x];
    delete[] newMap[x];
  }
}


void Life::clearHistory() {
  if (!historyEnabled) return;

  for (unsigned int h = 0; h < history.size(); h++) delete history[h];
  history.clear();
}


void Life::resizeMap(unsigned int width, unsigned int height) {
  if (mapWidth) {
    clear();
    clearHistory();
  }

  mapWidth = width;
  mapHeight = height;

  map = new cellType*[width];
  newMap = new cellType*[width];

  for (unsigned int x = 0; x < width; x++) {
    map[x] = new cellType[height];
    newMap[x] = new cellType[height];
  }
}


void Life::newGame(bool empty) {
  alive = 0;
  frame = 0;
  clearHistory();
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


cellType** Life::copyMap() {
  return copyMap(map);
}

cellType** Life::copyMap(cellType** map) {
  unsigned int x, y;
  cellType** copyMap = new cellType*[mapWidth];

  for (x = 0; x < mapWidth; x++) {
    copyMap[x] = new cellType[mapHeight];

    for (y = 0; y < mapHeight; y++) {
      copyMap[x][y] = map[x][y];
    }
  }

  return copyMap;
}


void inline Life::save() {
  history.push_back(new HistoryItem(alive, mapWidth, copyMap()));
  if (history.size() > historySize) history.erase(history.begin());
}


void Life::step() {
  clock_t t = clock();
  if (historyEnabled) save();

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
}


void Life::back() {
  if (!historyEnabled || history.size() == 0) return;
  
  HistoryItem* prev = history.back();
  frame--;

  for (unsigned int x = 0; x < mapWidth; x++) {
    delete[] map[x];
  }
  delete map;

  alive = prev->alive;
  map = copyMap(prev->map);

  delete history[history.size() - 1];
  history.pop_back();
}