#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <vector>



typedef unsigned char cellType;


struct HistoryItem {
  unsigned int alive;
  int width;
  cellType** map;

  HistoryItem(unsigned int alive, int width, cellType** map): width(width), alive(alive), map(map) { }
  ~HistoryItem() {
    for (int x = 0; x < width; x++) delete[] map[x];
    delete[] map;
  }
};


class Life {
public:
  cellType maxAge = 20;
  int mapWidth = 0;
  int mapHeight = 0;

  unsigned int alive;
  unsigned int frame;
  int durationStep;

  cellType** map;
  cellType** newMap;

  int historySize = 1000;
  bool historyEnabled = true;
  std::vector <HistoryItem*> history;

  Life();
  Life(int width, int height);
  ~Life();

  void clear();
  void clearHistory(int start = 0, int end = -1);

  void resizeMap(int width, int height);
  void newGame(bool empty = false);
  void generateMap(bool empty = false);

  cellType** copyMap();
  cellType** copyMap(cellType** map);

  void normalize(int& x, int& y);
  cellType getCell(int x, int y);
  void setCell(int x, int y, cellType v = 1);

  unsigned char getSumMur(int x, int y);
  void save();
  void step();
  void back();
};

#endif