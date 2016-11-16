#include "sizeWindow.h"
#include "MainComponent.h"



SizeQueryWindow::SizeQueryWindow(GameCanvas& canvas) : canvas(&canvas) {
  setSize(300, 150);

  slider = new Slider();
  slider->setRange(2, 10, 1);
  slider->setBounds(50, 30, 200, 50);
  slider->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
  slider->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
  slider->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);

  buttonOk = new CustomButton("size ok", "ok");
  buttonOk->setBounds(30, 100, 110, 30);
  buttonOk->addListener(this);

  buttonCancle = new CustomButton("size cancle", "cancle");
  buttonCancle->setBounds(160, 100, 110, 30);
  buttonCancle->addListener(this);

  addAndMakeVisible(slider);
  addAndMakeVisible(buttonOk);
  addAndMakeVisible(buttonCancle);
}


SizeQueryWindow::~SizeQueryWindow() {
  deleteAllChildren();
}


void SizeQueryWindow::show() {
  slider->setValue(canvas->cellSize);

  int cell = DialogWindow::showModalDialog("cell size", this, nullptr, Colours::black, true);

  if (cell != 0) {
    unsigned int mapWidth = canvas->getWidth() / cell;
    unsigned int mapHeight = canvas->getHeight() / cell;

    MainContentComponent* parent = canvas->findParentComponentOfClass<MainContentComponent>();
    parent->labelMapWidth->setText(String::formatted("Width: %i", mapWidth), NotificationType::dontSendNotification);
    parent->labelMapHeight->setText(String::formatted("height: %i", mapHeight), NotificationType::dontSendNotification);

    canvas->cellSize = (unsigned char)cell;
    canvas->resizeMap(mapWidth, mapHeight);
    canvas->newGame();
    canvas->repaint();
  }
}


void SizeQueryWindow::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(0);
  } else if (button == buttonOk) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(int(slider->getValue()));
  }
}