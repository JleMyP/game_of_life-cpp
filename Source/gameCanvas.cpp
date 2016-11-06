#include "gameCanvas.h"
#include "MainComponent.h"



GameCanvas::GameCanvas(unsigned char cellSize, Colour color) : penColor(color), cellSize(cellSize) { }


GameCanvas::~GameCanvas() { }


void GameCanvas::mouseMove(const MouseEvent & event) {
  mouseX = event.x / cellSize;
  mouseY = event.y / cellSize;
  
  MainContentComponent *parent = findParentComponentOfClass<MainContentComponent>();
  parent->labelMouseX->setText(String::formatted("X: %i", mouseX), NotificationType::dontSendNotification);
  parent->labelMouseY->setText(String::formatted("Y: %i", mouseY), NotificationType::dontSendNotification);
}


void GameCanvas::mouseDrag(const MouseEvent & event) {
  mouseDown(event);
}


void GameCanvas::mouseDown(const MouseEvent & event) {
  int x = event.x / cellSize;
  int y = event.y / cellSize;

  if (x < 0 || y < 0) return;

  if (map[x][y] == 0 && penMode == penModes::draw) {
    map[x][y] = 1;
    alive++;
  } else if (map[x][y] == 1 && penMode == penModes::erase) {
    map[x][y] = 0;
    alive--;
  }

  repaint();
}



void GameCanvas::paint(Graphics& g) {
  if (running) step();

  g.fillAll(Colours::black);
  g.setColour(penColor);

  clock_t t = clock();
  unsigned int x, y, px;

  for (x = 0; x < mapWidth; x++) {
    px = x * cellSize + 1;

    for (y = 0; y < mapHeight; y++) {
      if (map[x][y]) {
        g.fillRect(px, y * cellSize + 1, cellSize - 1, cellSize - 1);
      }
    }
  }

  durationDraw = clock() - t;
}



void GameCanvas::resized() {
  resizeMap(getWidth() / cellSize, getHeight() / cellSize);
  newGame();
}