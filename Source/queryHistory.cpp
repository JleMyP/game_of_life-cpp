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
  
  labelWarning = new Label("warning", "size of one frame: ");
  labelWarning->setBounds(50, 150, 150, 30);
  labelWarning->setColour(Label::textColourId, Colours::white);

  buttonOk = new CustomButton("history ok", "ok");
  buttonOk->setBounds(30, 200, 110, 30);
  buttonOk->addListener(this);

  buttonCancle = new CustomButton("history cancle", "cancle");
  buttonCancle->setBounds(160, 200, 110, 30);
  buttonCancle->addListener(this);

  addAndMakeVisible(checkEnabled);
  addAndMakeVisible(sliderLimit);
  addAndMakeVisible(labelWarning);
  addAndMakeVisible(buttonOk);
  addAndMakeVisible(buttonCancle);
}


QueryHistory::~QueryHistory() {
  deleteAllChildren();
}


void QueryHistory::show() {
  int size = canvas->mapWidth * canvas->mapHeight * sizeof(cellType) + canvas->mapWidth * sizeof(void*);

  setVisible(true);
  checkEnabled->setToggleState(canvas->historyEnabled, false);
  sliderLimit->setValue(canvas->historySize);
  labelWarning->setText(String::formatted("size of one frame: %ikb", size / 1024), dontSendNotification);

  buttonOk->setEnabled(false);
  buttonCancle->setEnabled(false);
}


void QueryHistory::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    checkEnabled->setToggleState(canvas->historyEnabled, false);
    sliderLimit->setValue(canvas->historySize);

    buttonOk->setEnabled(false);
    buttonCancle->setEnabled(false);
  } else if (button == buttonOk) {
    bool state = checkEnabled->getToggleState();
    unsigned int limit = (unsigned int)(sliderLimit->getValue());

    if (!state && canvas->historyEnabled) canvas->clearHistory();
    canvas->historyEnabled = state;

    if (state) {
      if (canvas->history.size() > limit) canvas->clearHistory(0, canvas->history.size() - limit);

      canvas->historySize = limit;
      canvas->history.reserve(limit);

      MainContentComponent* parent = canvas->findParentComponentOfClass<MainContentComponent>();
      parent->labelHistory->setText(String::formatted("History: %i/%i", canvas->history.size(), limit), dontSendNotification);
    }

    buttonOk->setEnabled(false);
    buttonCancle->setEnabled(false);
  } else if (button == checkEnabled) {
    sliderLimit->setEnabled(checkEnabled->getToggleState());
  }
}



void QueryHistory::sliderValueChanged(Slider *slider) {
  bool enabled = checkEnabled->getToggleState() != canvas->historyEnabled || slider->getValue() != canvas->historySize;

  buttonOk->setEnabled(enabled);
  buttonCancle->setEnabled(enabled);
}