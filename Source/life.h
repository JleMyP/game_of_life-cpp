#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#include <cstdlib>
#include <ctime>



typedef unsigned char cellType;


class Life {
public:
  unsigned int mapWidth = 0;
  unsigned int mapHeight = 0;
  //int historySize = 0;

  cellType** map;
  cellType** newMap;
  //cellType*** history;

  unsigned int alive;
  unsigned int frame;
  int durationStep;

  Life();
  Life(unsigned int width, unsigned int height);
  ~Life();
  void clear();

  void resizeMap(unsigned int width, unsigned int height);
  void newGame(bool empty = false);
  void generateMap(bool empty=false);
  cellType getCell(int x, int y);
  unsigned int getSumMur(int x, int y);
  void step();
};

#endif