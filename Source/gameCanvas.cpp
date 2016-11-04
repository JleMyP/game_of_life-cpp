#include "gameCanvas.h"
#include "MainComponent.h"



gameCanvas::gameCanvas(unsigned char cellSize, Colour color) : penColor(color), cellSize(cellSize) { }


gameCanvas::~gameCanvas() { }


void gameCanvas::mouseMove(const MouseEvent & event) {
  mouseX = event.x / cellSize;
  mouseY = event.y / cellSize;
  
  MainContentComponent *parent = findParentComponentOfClass<MainContentComponent>();
  parent->labelMouseX->setText(String::formatted("X: %i", mouseX), NotificationType::dontSendNotification);
  parent->labelMouseY->setText(String::formatted("Y: %i", mouseY), NotificationType::dontSendNotification);
}


void gameCanvas::mouseDrag(const MouseEvent & event) {
  mouseDown(event);
}


void gameCanvas::mouseDown(const MouseEvent & event) {
  int x = event.x / cellSize;
  int y = event.y / cellSize;

  if (x < 0 || y < 0) return;

  if (map[x][y] == 0 && draw) alive++;
  else if (map[x][y] == 1 && !draw) alive--;

  map[x][y] = draw ? 1 : 0;
  repaint();
}



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
//  NativeMessageBox::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "start", "resize" + String(getWidth()));
  resizeMap(getWidth() / cellSize, getHeight() / cellSize);
//  NativeMessageBox::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "start", "new game");
  newGame();
//  NativeMessageBox::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "end", "resize");
}


void gameCanvas::parentHierarchyChanged() {
//  parent = findParentComponentOfClass<MainContentComponent>();
}