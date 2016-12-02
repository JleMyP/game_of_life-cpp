#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <vector>



typedef unsigned char cellType;


void removeMap(cellType** map, int width);


struct HistoryItem {
  unsigned int alive;
  int width;
  cellType** map;

  HistoryItem(unsigned int alive, int width, cellType** map): width(width), alive(alive), map(map) { }
  ~HistoryItem() { removeMap(map, width); }
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
  cellType** oldMap;

  int historySize = 1000;
  bool historyEnabled = true;
  std::vector <HistoryItem*> history;

  Life();
  Life(int width, int height);
  ~Life();

  //void clear();
  void clearHistory(int start = 0, int end = -1);

  void resizeMap(int width, int height);
  void newGame(bool empty = false);
  void generateMap(cellType** targetMap, bool empty = false);

  cellType** copyMap(cellType** sourceMap);
  void copyMap(cellType** sourceMap, cellType** targetMap);

  void normalize(int& x, int& y);
  cellType getCell(int x, int y);
  void setCell(int x, int y, cellType v = 1);

  unsigned char getSumMur(int x, int y);
  void save();
  void step();
  void back();
};

#endif