#include "colorWindow.h"



ColorQueryWindow::ColorQueryWindow(GameCanvas& canvas) : canvas(&canvas) {
  setSize(300, 350);

  selector = new ColourSelector(
    ColourSelector::showColourAtTop |
    ColourSelector::showColourspace
  );

  selector->setBounds(0, 0, 300, 300);
  selector->setColour(ColourSelector::backgroundColourId, Colours::black);

  buttonOk = new CustomButton("color ok", "ok");
  buttonOk->setBounds(30, 310, 110, 30);
  buttonOk->addListener(this);

  buttonCancle = new CustomButton("color cancle", "cancle");
  buttonCancle->setBounds(160, 310, 110, 30);
  buttonCancle->addListener(this);

  addAndMakeVisible(selector);
  addAndMakeVisible(buttonOk);
  addAndMakeVisible(buttonCancle);
}


ColorQueryWindow::~ColorQueryWindow() {
  deleteAllChildren();
}


void ColorQueryWindow::show() {
  selector->setCurrentColour(canvas->penColor);

  int result = DialogWindow::showModalDialog("cell size", this, nullptr, Colours::black, true);

  if (result != 0) {
    Colour color = selector->getCurrentColour();
    canvas->penColor = color;
    canvas->repaint();
  }
}


void ColorQueryWindow::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(0);
  } else if (button == buttonOk) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(1);
  }
}