#ifndef INITGUI_H_INCLUDED
#define INITGUI_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"



void MainContentComponent::initMainW() {
  Colour colorLabel = Colours::white;

  labelMapWidth = new Label("map width", "Width");
  labelMapWidth->setBounds(0, 0, bar, 25);
  labelMapWidth->setColour(Label::textColourId, colorLabel);

  labelMapHeight = new Label("map height", "Height");
  labelMapHeight->setBounds(0, 25, bar, 25);
  labelMapHeight->setColour(Label::textColourId, colorLabel);

  labelFrame = new Label("frame", "Frame");
  labelFrame->setBounds(0, 80, bar, 25);
  labelFrame->setColour(Label::textColourId, colorLabel);

  labelAlive = new Label("alive", "Alive");
  labelAlive->setBounds(0, 105, bar, 25);
  labelAlive->setColour(Label::textColourId, colorLabel);

  labelDStep = new Label("duration step", "Step");
  labelDStep->setBounds(0, 150, bar, 25);
  labelDStep->setColour(Label::textColourId, colorLabel);

  labelDDraw = new Label("duration darw", "Draw");
  labelDDraw->setBounds(0, 175, bar, 25);
  labelDDraw->setColour(Label::textColourId, colorLabel);

  labelMouseX = new Label("mouse x", "X:");
  labelMouseX->setBounds(0, 220, bar, 25);
  labelMouseX->setColour(Label::textColourId, colorLabel);

  labelMouseY = new Label("mouse y", "Y:");
  labelMouseY->setBounds(0, 245, bar, 25);
  labelMouseY->setColour(Label::textColourId, colorLabel);

  labelPenWidth = new Label("pen width", "pen width: " + String(canvas.penWidth));
  labelPenWidth->setBounds(0, 270, bar, 25);
  labelPenWidth->setColour(Label::textColourId, colorLabel);

  buttonNewGame = new CustomButton("new game", "new game");
  buttonNewGame->setBounds(10, 310, 110, 30);
  buttonNewGame->addListener(this);

  buttonPlay = new CustomButton("play", "play");
  buttonPlay->setBounds(10, 350, 110, 30);
  buttonPlay->addListener(this);

  buttonClear = new CustomButton("clear", "clear");
  buttonClear->setBounds(10, 390, 110, 30);
  buttonClear->addListener(this);

  buttonDraw = new CustomButton("draw", "draw");
  buttonDraw->setBounds(10, 440, 110, 30);
  buttonDraw->addListener(this);

  buttonCellSize = new CustomButton("cell size", "cell size");
  buttonCellSize->setBounds(10, 490, 110, 30);
  buttonCellSize->addListener(this);

  buttonColor = new CustomButton("cell color", "cell color");
  buttonColor->setBounds(10, 530, 110, 30);
  buttonColor->addListener(this);


  addAndMakeVisible(canvas);

  addAndMakeVisible(labelMapWidth);
  addAndMakeVisible(labelMapHeight);

  addAndMakeVisible(labelFrame);
  addAndMakeVisible(labelAlive);

  addAndMakeVisible(labelDStep);
  addAndMakeVisible(labelDDraw);

  addAndMakeVisible(labelMouseX);
  addAndMakeVisible(labelMouseY);
  addAndMakeVisible(labelPenWidth);

  addAndMakeVisible(buttonNewGame);
  addAndMakeVisible(buttonPlay);
  addAndMakeVisible(buttonClear);
  addAndMakeVisible(buttonDraw);
  addAndMakeVisible(buttonCellSize);
  addAndMakeVisible(buttonColor);


  setSize(bar + gameMapWidth * gameCellSize, gameMapHeight * gameCellSize);
  setWantsKeyboardFocus(true);
  grabKeyboardFocus();
}


void MainContentComponent::initSizeW() {
  sizeMain = new Component("size main");
  sizeMain->setSize(300, 150);

  sizeSlider = new Slider();
  sizeSlider->setRange(2, 10, 1);
  sizeSlider->setBounds(50, 30, 200, 50);
  sizeSlider->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
  sizeSlider->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
  sizeSlider->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);

  sizeBtnOk = new CustomButton("size ok", "ok");
  sizeBtnOk->setBounds(30, 100, 110, 30);
  sizeBtnOk->addListener(this);

  sizeBtnCancle = new CustomButton("size cancle", "cancle");
  sizeBtnCancle->setBounds(160, 100, 110, 30);
  sizeBtnCancle->addListener(this);

  sizeMain->addAndMakeVisible(sizeSlider);
  sizeMain->addAndMakeVisible(sizeBtnOk);
  sizeMain->addAndMakeVisible(sizeBtnCancle);
}


void MainContentComponent::initRulesW() {
  
}


void MainContentComponent::initColorW() {
  colorMain = new Component("color window");
  colorMain->setBounds(0, 0, 300, 350);

  selector = new ColourSelector(
    ColourSelector::showColourAtTop |
    ColourSelector::showColourspace
  );

  selector->setBounds(0, 0, 300, 300);
  selector->setColour(ColourSelector::backgroundColourId, Colours::black);

  colorBtnOk = new CustomButton("color ok", "ok");
  colorBtnOk->setBounds(30, 310, 110, 30);
  colorBtnOk->addListener(this);

  colorBtnCancle = new CustomButton("color cancle", "cancle");
  colorBtnCancle->setBounds(160, 310, 110, 30);
  colorBtnCancle->addListener(this);

  colorMain->addAndMakeVisible(selector);
  colorMain->addAndMakeVisible(colorBtnOk);
  colorMain->addAndMakeVisible(colorBtnCancle);
}


#endif