#include "queryHistory.h"
#include "MainComponent.h"



QueryHistory::QueryHistory(GameCanvas& canvas): canvas(&canvas) {
  setSize(300, 300);

  checkEnabled = new ToggleButton("enabled");
  checkEnabled->setBounds(75, 40, 150, 30);
  checkEnabled->setColour(ToggleButton::ColourIds::textColourId, Colours::lime);
  checkEnabled->setColour(ToggleButton::ColourIds::tickColourId, Colours::red);
  checkEnabled->addListener(this);

  sliderLimit = new Slider(Slider::SliderStyle::IncDecButtons, Slider::TextEntryBoxPosition::TextBoxRight);
  sliderLimit->setRange(10, (&canvas)->history.max_size(), 10);
  sliderLimit->setBounds(75, 90, 150, 30);
  sliderLimit->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
  sliderLimit->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
  sliderLimit->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);
  sliderLimit->addListener(this);
  
  buttonOk = new CustomButton("history ok", "ok");
  buttonOk->setBounds(30, 160, 110, 30);
  buttonOk->addListener(this);

  buttonCancle = new CustomButton("history cancle", "cancle");
  buttonCancle->setBounds(160, 160, 110, 30);
  buttonCancle->addListener(this);

  addAndMakeVisible(checkEnabled);
  addAndMakeVisible(sliderLimit);
  addAndMakeVisible(buttonOk);
  addAndMakeVisible(buttonCancle);
}


QueryHistory::~QueryHistory() {
  deleteAllChildren();
}


void QueryHistory::show() {
  setVisible(true);
  checkEnabled->setToggleState(canvas->historyEnabled, false);
  sliderLimit->setValue(canvas->historySize);
  buttonOk->setEnabled(false);
}


void QueryHistory::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    checkEnabled->setToggleState(canvas->historyEnabled, false);
    sliderLimit->setValue(canvas->historySize);
    buttonOk->setEnabled(false);
  } else if (button == buttonOk) {
    bool state = checkEnabled->getToggleState();
    int limit = sliderLimit->getValue();

    if (!state && canvas->historyEnabled) canvas->clearHistory();
    canvas->historyEnabled = state;

    if (state) {
      canvas->historySize = limit;
      canvas->history.reserve(limit);
    }

    buttonOk->setEnabled(false);
  } else if (button == checkEnabled) {
    sliderLimit->setEnabled(checkEnabled->getToggleState());
  }
}



void QueryHistory::sliderValueChanged(Slider *slider) {
  buttonOk->setEnabled(checkEnabled->getToggleState() != canvas->historyEnabled || sliderLimit->getValue() != canvas->historySize);
}