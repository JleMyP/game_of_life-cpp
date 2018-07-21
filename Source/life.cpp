#include "life.h"



void removeMap(cellType** map, int width) {
  for (int x = 0; x < width; x++) delete[] map[x];
  delete[] map;
}


Life::Life(): history(historySize) {}
Life::Life(int width, int height): history(historySize) {
  resizeMap(width, height);
  newGame();
}


Life::~Life() {
  clearHistory();
  removeMap(map, mapWidth);
  removeMap(newMap, mapWidth);
}


void Life::clearHistory(int start, int end) {
  if (end == -1) end = history.size();
  if (!historyEnabled) return;

  for (int h = start; h < end; h++) delete history[h];

  history.erase(history.begin() + start, history.begin() + end);
}


void Life::resizeMap(int width, int height) {
  if (mapWidth) {
    clearHistory();
    removeMap(map, mapWidth);
    removeMap(newMap, mapWidth);
  }

  mapWidth = width;
  mapHeight = height;

  map = new cellType*[width];
  newMap = new cellType*[width];

  for (int x = 0; x < width; x++) {
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
  int x, y;

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      map[x][y] = empty ? 0 : rand() % 2;
    }
  }
}


void Life::normalize(int& x, int& y) {
  if (x >= mapWidth) x -= mapWidth;
  else if (x < 0) x += mapWidth;

  if (y >= mapHeight) y -= mapHeight;
  else if (y < 0) y += mapHeight;
}


cellType Life::getCell(int x, int y) {
  normalize(x, y);
  return map[x][y] ? 1 : 0;
}


void Life::setCell(int x, int y, cellType v) {
  normalize(x, y);
  map[x][y] = v;
}


char Life::getSumMur(int x, int y) {
  char sum = 0;
  int xx, yy;

  for (xx = x - 1; xx < x + 2; xx++) {
    for (yy = y - 1; yy < y + 2; yy++) {
      sum += getCell(xx, yy);
    }
  }

  return sum - (map[x][y] ? 1 : 0);
}


cellType** Life::copyMap(cellType** sourceMap) {
  int x, y;
  cellType** targetMap = new cellType*[mapWidth];

  for (x = 0; x < mapWidth; x++) {
    targetMap[x] = new cellType[mapHeight];

    for (y = 0; y < mapHeight; y++) {
      targetMap[x][y] = sourceMap[x][y];
    }
  }

  return targetMap;
}

void Life::copyMap(cellType** sourceMap, cellType** targetMap) {
  int x, y;

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      targetMap[x][y] = sourceMap[x][y];
    }
  }
}


void inline Life::save() {
  history.push_back(new HistoryItem(alive, mapWidth, copyMap(map)));
  if (history.size() > historySize) clearHistory(0, 1);
}


void Life::step() {
  clock_t t = clock();

  if (historyEnabled) save();

  int x, y;
  char sum;
  cellType cell;
  cellType calculate;
  alive = 0;

  for (x = 0; x < mapWidth; x++) {
    for (y = 0; y < mapHeight; y++) {
      cell = map[x][y];
      sum = getSumMur(x, y);
      calculate = (sum == 3 || cell && sum == 2) ? (cell < maxAge ? cell + 1 : maxAge) : 0;

      newMap[x][y] = calculate;
      alive += calculate ? 1 : 0;
    }
  }

  cellType** tmp = newMap;
  newMap = map;
  map = tmp;

  frame++;
  durationStep = clock() - t;
}


void Life::back() {
  if (!historyEnabled || history.size() == 0) return;
  
  HistoryItem* prev = history.back();
  alive = prev->alive;
  frame--;

  copyMap(prev->map, map);

  delete history[history.size() - 1];
  // delete prev;
  history.pop_back();
}