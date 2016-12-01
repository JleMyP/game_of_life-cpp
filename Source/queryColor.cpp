#include "queryColor.h"



QueryColor::QueryColor(GameCanvas& canvas): canvas(&canvas) {
  setSize(300, 300);

  selector = new ColourSelector(
    ColourSelector::showColourAtTop |
    ColourSelector::showColourspace
  );

  selector->setBounds(0, 0, 300, 250);
  selector->setColour(ColourSelector::backgroundColourId, Colours::black);
  selector->addChangeListener(this);

  buttonOk = new CustomButton("color ok", "ok");
  buttonOk->setBounds(30, 260, 110, 30);
  buttonOk->addListener(this);

  buttonCancle = new CustomButton("color cancle", "cancle");
  buttonCancle->setBounds(160, 260, 110, 30);
  buttonCancle->addListener(this);

  addAndMakeVisible(selector);
  addAndMakeVisible(buttonOk);
  addAndMakeVisible(buttonCancle);
}


QueryColor::~QueryColor() {
  deleteAllChildren();
}


void QueryColor::show() {
  selector->setCurrentColour(canvas->penColor);

  setVisible(true);
  buttonOk->setEnabled(false);
  buttonCancle->setEnabled(false);
}


void QueryColor::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    selector->setCurrentColour(canvas->penColor);

    buttonOk->setEnabled(false);
    buttonCancle->setEnabled(false);
  } else if (button == buttonOk) {
    Colour color = selector->getCurrentColour();
    canvas->penColor = color;
    canvas->repaint();

    buttonOk->setEnabled(false);
    buttonCancle->setEnabled(false);
  }
}


void QueryColor::changeListenerCallback(ChangeBroadcaster* sender) {
  bool enabled = selector->getCurrentColour() != canvas->penColor;

  buttonOk->setEnabled(enabled);
  buttonCancle->setEnabled(enabled);
}