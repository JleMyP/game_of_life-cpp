#include "gameCanvas.h"

#include <cmath>
#include "MainComponent.h"


GameCanvas::GameCanvas(char cellSize, Colour color) : Life(12), penColor(color), cellSize(cellSize) {
    historyEnabled = false;
    lastDraw = clock_now();
    fps = 0;
    durationDraw = 0;
}


void GameCanvas::mouseMove(const MouseEvent & event) {
    mousePos.setXY(event.x / cellSize, event.y / cellSize);
    auto* parent = findParentComponentOfClass<MainContentComponent>();
    parent->labelMouseX->setText(String::formatted("X: %i", mousePos.x), NotificationType::dontSendNotification);
    parent->labelMouseY->setText(String::formatted("Y: %i", mousePos.y), NotificationType::dontSendNotification);
}


void GameCanvas::mouseDrag(const MouseEvent& event) {
    mouseDown(event);
}


void GameCanvas::mouseDown(const MouseEvent& event) {
    int x = event.x / cellSize;
    int y = event.y / cellSize;

    if (x < 0 || y < 0)
        return;

    drawRect(x, y);
    repaint();
}


void GameCanvas::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) {
    auto* parent = findParentComponentOfClass<MainContentComponent>();

    if (wheel.deltaY > 0 && penWidth < maxPenWidth)
        penWidth++;
    else if (wheel.deltaY < 0 && penWidth > 1)
        penWidth--;

    parent->labelPenWidth->setText("pen width: " + String(penWidth), NotificationType::dontSendNotification);
}


void GameCanvas::drawRect(int x, int y) {
    int pm = (penWidth - penWidth % 2) / 2;
    int x1 = x - pm + (1 - penWidth % 2);
    int x2 = x + pm;
    int y1 = y - pm + (1 - penWidth % 2);
    int y2 = y + pm;

    int diff = 0;

    int xx, yy;
    cellType cell;

    for (xx = x1; xx <= x2; xx++) {
        for (yy = y1; yy <= y2; yy++) {
            cell = getCell(xx, yy);

            if (penMode == penModes::draw && !cell)
                diff--;
            else if (penMode == penModes::erase && cell)
                diff++;

            setCell(xx, yy, (cellType)penMode);
        }
    }
}


void GameCanvas::paint(Graphics& g) {
    if (running && (alive > 0 || frame == 0 && alive == 0))
        step();

    auto t = clock_now();
    int x, y, px;

    for (x = 0; x < mapWidth; x++) {
        px = x * cellSize + 1;

        for (y = 0; y < mapHeight; y++) {
            if (map[x][y] == 0)
                continue;

            g.setColour(penColor.withAlpha(1.0f / std::ceil(float(map[x][y]) / rateAging)));
            g.fillRect(px, y * cellSize + 1, cellSize - 1, cellSize - 1);
        }
    }

    durationDraw = clock_cast_microsec(clock_now() - t);
    auto now = clock_now();
    fps = 1000000 / clock_cast_microsec(now - lastDraw);
    lastDraw = now;
}


void GameCanvas::resized() {
    resizeMap(getWidth() / cellSize, getHeight() / cellSize);
    newGame();
}
