#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#include <cstdlib>
#include <ctime>



typedef unsigned char cellType;


class Life {
public:
  int mapWidth;
  int mapHeight;
  int historySize;

  cellType** map;
  cellType** newMap;
  //cellType** prevMap;
  //cellType*** history;

  int alive;
  int frame;
  int durationStep;

  Life();
  Life(int width, int height);
  ~Life();
  void clear();

  void resizeMap(int width, int height);
  void newGame(bool empty = false);
  void generateMap(bool empty=false);
  int getCell(int x, int y);
  int getSumMur(int x, int y);
  void step();

};

#endif