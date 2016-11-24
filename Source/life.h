#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <vector>



typedef unsigned char cellType;


struct HistoryItem {
  unsigned int alive;
  unsigned int width;
  cellType** map;

  HistoryItem(unsigned int alive, unsigned int width, cellType** map) : width(width), alive(alive), map(map) { }
  ~HistoryItem() {
    for (unsigned int x = 0; x < width; x++) delete[] map[x];
    delete[] map;
  }
};


class Life {
public:
  cellType maxAge = 20;
  unsigned int mapWidth = 0;
  unsigned int mapHeight = 0;

  unsigned int alive;
  unsigned int frame;
  int durationStep;

  cellType** map;
  cellType** newMap;

  int historySize = 1000;
  bool historyEnabled = true;
  std::vector <HistoryItem*> history;

  Life();
  Life(unsigned int width, unsigned int height);
  ~Life();

  void clear();
  void clearHistory();

  void resizeMap(unsigned int width, unsigned int height);
  void newGame(bool empty = false);
  void generateMap(bool empty = false);

  cellType** copyMap();
  cellType** copyMap(cellType** map);

  void normalize(int& x, int& y);
  cellType getCell(int x, int y);
  void setCell(int x, int y, cellType v = 1);

  unsigned char getSumMur(unsigned int x, unsigned int y);
  void save();
  void step();
  void back();
};

#endif