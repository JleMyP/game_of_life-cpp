#include "MainComponent.h"
#include "initGUI.cpp"



MainContentComponent::MainContentComponent() : canvas(gameCellSize) {
  initMainW();
  settingsW = new SettingsWindow(canvas);
}


MainContentComponent::~MainContentComponent() {
  removeChildComponent(0);
  deleteAllChildren();

  delete settingsW;
}


void MainContentComponent::timerCallback() {
  repaint();

  labelFrame->setText(String::formatted("Frame: %i", canvas.frame), NotificationType::dontSendNotification);
  labelAlive->setText(String::formatted("Alive: %i", canvas.alive), NotificationType::dontSendNotification);
  labelHistory->setText(String::formatted("History: %i", canvas.history.size()), NotificationType::dontSendNotification);
  labelDStep->setText(String::formatted("Step per: %i", canvas.durationStep), NotificationType::dontSendNotification);
  labelDDraw->setText(String::formatted("Draw per: %i", canvas.durationDraw), NotificationType::dontSendNotification);
}


void MainContentComponent::resized() {
  canvas.setBounds(bar, 0, getWidth() - bar, getHeight());

  labelMapSize->setText(String::formatted("Size: %ix%i", canvas.mapWidth, canvas.mapHeight), NotificationType::dontSendNotification);
}


/*
    Buttons callbacks
*/

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
  canvas.penMode = (GameCanvas::penModes)((canvas.penMode + 1) % GameCanvas::penModes::length);
  buttonDraw->setText(canvas.penStr[canvas.penMode]);
}


void MainContentComponent::buttonClicked(Button* button) {
  if (button == buttonNewGame) newGameCallback();
  else if (button == buttonPlay) playCallback();
  else if (button == buttonClear) clearCallback();
  else if (button == buttonDraw) drawCallback();
  else if (button == buttonSettings) settingsW->show();
}


bool MainContentComponent::keyPressed(const KeyPress& key) {
  int keyCode = key.getKeyCode();

  if (keyCode == key.returnKey) newGameCallback();
  else if (keyCode == key.spaceKey) playCallback();
  else if (keyCode == key.escapeKey) JUCEApplication::getInstance()->systemRequestedQuit();
  else if (keyCode == 67) clearCallback(); // key c
  else if (keyCode == key.rightKey && !canvas.running) {
    canvas.step();
    timerCallback();
  } else if (keyCode == key.leftKey && !canvas.running) {
    canvas.back();
    timerCallback();
  }

  return false;
}
