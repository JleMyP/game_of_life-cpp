#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#include <cstdlib>
#include <ctime>



typedef unsigned char cellType;



class Life {
public:
  cellType maxAge = 40;
  unsigned int mapWidth = 0;
  unsigned int mapHeight = 0;
  //int historySize = 100;

  unsigned int alive;
  unsigned int frame;
  int durationStep;

  cellType** map;
  cellType** newMap;
  //cellType*** history;

  Life();
  Life(unsigned int width, unsigned int height);
  ~Life();

  void clear();

  void resizeMap(unsigned int width, unsigned int height);
  void newGame(bool empty = false);
  void generateMap(bool empty = false);

  void normalize(int& x, int& y);
  cellType getCell(int x, int y);
  void setCell(int x, int y, cellType v = 1);

  unsigned char getSumMur(unsigned int x, unsigned int y);
  void step();
};

#endif