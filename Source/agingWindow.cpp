#include "agingWindow.h"



AgingQueryWindow::AgingQueryWindow(GameCanvas& canvas) : canvas(&canvas) {
  setSize(300, 210);

  labelRate = new Label("rate label", "Rate:");
  labelRate->setBounds(20, 30, 100, 50);
  labelRate->setColour(Label::textColourId, Colours::white);

  labelGradations = new Label("gradations label", "Gradations:");
  labelGradations->setBounds(20, 90, 100, 50);
  labelGradations->setColour(Label::textColourId, Colours::white);

  sliderRate = new Slider();
  sliderRate->setRange(1, 10, 1);
  sliderRate->setBounds(100, 30, 180, 50);
  sliderRate->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 50);
  sliderRate->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
  sliderRate->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
  sliderRate->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);

  sliderGradations = new Slider();
  sliderGradations->setRange(1, 10, 1);
  sliderGradations->setBounds(100, 90, 180, 50);
  sliderGradations->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 50);
  sliderGradations->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
  sliderGradations->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
  sliderGradations->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);

  buttonOk = new CustomButton("aging ok", "ok");
  buttonOk->setBounds(30, 160, 110, 30);
  buttonOk->addListener(this);

  buttonCancle = new CustomButton("aging cancle", "cancle");
  buttonCancle->setBounds(160, 160, 110, 30);
  buttonCancle->addListener(this);


  addAndMakeVisible(labelRate);
  addAndMakeVisible(labelGradations);

  addAndMakeVisible(sliderRate);
  addAndMakeVisible(sliderGradations);
  
  addAndMakeVisible(buttonOk);
  addAndMakeVisible(buttonCancle);
}


AgingQueryWindow::~AgingQueryWindow() {
  deleteAllChildren();
}


void AgingQueryWindow::show() {
  sliderRate->setValue(canvas->rateAging);
  sliderGradations->setValue(canvas->maxAge / canvas->rateAging);

  int result = DialogWindow::showModalDialog("cell size", this, nullptr, Colours::black, true);

  if (result != 0) {
    canvas->rateAging = (float)sliderRate->getValue();
    canvas->maxAge = (cellType)(sliderRate->getValue() * sliderGradations->getValue());
  }
}


void AgingQueryWindow::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(0);
  } else if (button == buttonOk) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(1);
  }
}