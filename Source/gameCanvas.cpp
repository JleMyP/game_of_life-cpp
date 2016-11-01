#include "gameCanvas.h"



gameCanvas::gameCanvas(unsigned char cellSize, Colour color) {
  penColor = color;
  this->cellSize = cellSize;
}


gameCanvas::~gameCanvas() { }


void gameCanvas::paint(Graphics& g) {
  if (running) step();

  g.fillAll(Colours::black);
  g.setColour(penColor);

  clock_t t = clock();
  int x, y, px;

  for (x = 0; x < mapWidth; x++) {
    px = x * cellSize + 1;

    for (y = 0; y < mapHeight; y++) {
      if (map[x][y]) {
      //if (map[x][y] != prevMap[x][y] || frame == 1) {
        //g.setColour(map[x][y] ? penColor : Colours::black);
        g.fillRect(px, y * cellSize + 1, cellSize - 1, cellSize - 1);
      }
    }
  }

  durationDraw = clock() - t;
}



void gameCanvas::resized() {
  resizeMap(getWidth() / cellSize, getHeight() / cellSize);
  newGame();
}