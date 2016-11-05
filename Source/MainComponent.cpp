#include "MainComponent.h"
#include "initGUI.h"
#include "colorWindow.h"



MainContentComponent::MainContentComponent() : canvas(gameCellSize) {
  initMainW();
  initSizeW();
  initColorW();
}


MainContentComponent::~MainContentComponent() {
  removeChildComponent(0);
  deleteAllChildren();

  sizeMain->deleteAllChildren();
  delete sizeMain;

  colorMain->deleteAllChildren();
  delete colorMain;
}


void MainContentComponent::timerCallback() {
  repaint();

  labelFrame->setText(String::formatted("Frame: %i", canvas.frame), NotificationType::dontSendNotification);
  labelAlive->setText(String::formatted("Alive: %i", canvas.alive), NotificationType::dontSendNotification);
  labelDStep->setText(String::formatted("Step per: %i", canvas.durationStep), NotificationType::dontSendNotification);
  labelDDraw->setText(String::formatted("Draw per: %i", canvas.durationDraw), NotificationType::dontSendNotification);
}


void MainContentComponent::resized() {
  canvas.setBounds(bar, 0, getWidth() - bar, getHeight());

  labelMapWidth->setText(String::formatted("Width: %i", canvas.mapWidth), NotificationType::dontSendNotification);
  labelMapHeight->setText(String::formatted("height: %i", canvas.mapHeight), NotificationType::dontSendNotification);
}


void MainContentComponent::newGameCallback() {
  canvas.newGame();
  repaint();
}


void MainContentComponent::playCallback() {
  if (isTimerRunning()) {
    stopTimer();
    canvas.running = false;
    buttonPlay->setText("start");
  } else {
    startTimer(1);
    canvas.running = true;
    buttonPlay->setText("pause");
  }
}


void MainContentComponent::clearCallback() {
  canvas.running = false;
  canvas.newGame(true);

  labelFrame->setText("Frame: 0", NotificationType::dontSendNotification);
  labelAlive->setText("Alive: 0", NotificationType::dontSendNotification);
  buttonPlay->setText("start");

  stopTimer();
  repaint();
}


void MainContentComponent::drawCallback() {
  canvas.draw = !canvas.draw;
  buttonDraw->setText(canvas.draw ? "draw" : "erase");
}


void MainContentComponent::sizeCallback() {
  sizeSlider->setValue(canvas.cellSize);

  unsigned char cell = DialogWindow::showModalDialog("cell size", sizeMain, nullptr, Colours::black, true);

  if (cell != 0) {
    unsigned int mapWidth = canvas.getWidth() / cell;
    unsigned int mapHeight = canvas.getHeight() / cell;

    labelMapWidth->setText(String::formatted("Width: %i", mapWidth), NotificationType::dontSendNotification);
    labelMapHeight->setText(String::formatted("height: %i", mapHeight), NotificationType::dontSendNotification);

    canvas.cellSize = cell;
    canvas.resizeMap(mapWidth, mapHeight);
    canvas.newGame();
    repaint();
  }
}


void MainContentComponent::colorCallback() {
  selector->setCurrentColour(canvas.penColor);

  int result = DialogWindow::showModalDialog("cell size", colorMain, nullptr, Colours::black, true);

  if (result != 0) {
    Colour color = selector->getCurrentColour();
    canvas.penColor = color;
    repaint();
  }
}


void MainContentComponent::buttonClicked(Button* button) {
  DialogWindow* dw;

  if (button == buttonNewGame) newGameCallback();
  else if (button == buttonPlay) playCallback();
  else if (button == buttonClear) clearCallback();
  else if (button == buttonDraw) drawCallback();
  else if (button == buttonCellSize) sizeCallback();
  else if (button == buttonColor) colorCallback();
  else if (button == sizeBtnCancle) {
    if (dw = sizeMain->findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(0);
  } else if (button == sizeBtnOk) {
    if (dw = sizeMain->findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(sizeSlider->getValue());
  } else if (button == colorBtnCancle) {
    if (dw = colorMain->findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(0);
  } else if (button == colorBtnOk) {
    if (dw = colorMain->findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(1);
  }
}


bool MainContentComponent::keyPressed(const KeyPress& key) {
  int keyCode = key.getKeyCode();
  juce_wchar keyChar = key.getTextCharacter();

  if (keyCode == key.returnKey) newGameCallback();
  else if (keyCode == key.spaceKey) playCallback();
  else if (keyCode == key.escapeKey) JUCEApplication::getInstance()->systemRequestedQuit();
  else if (keyChar == 'c') clearCallback();
  else if (keyCode == key.rightKey) {
    canvas.step();
    timerCallback();
  }

  return false;
}
