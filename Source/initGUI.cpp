#ifndef INITGUI_H_INCLUDED
#define INITGUI_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"



void MainContentComponent::initMainW() {
  Colour colorLabel = Colours::white;

  labelMapSize = new Label("map size", String::formatted("Size: %ix%i", gameMapWidth, gameMapHeight));
  labelMapSize->setBounds(0, 0, bar, 25);
  labelMapSize->setColour(Label::textColourId, colorLabel);

  labelFrame = new Label("frame", "Frame: 0");
  labelFrame->setBounds(0, 65, bar, 25);
  labelFrame->setColour(Label::textColourId, colorLabel);

  labelAlive = new Label("alive", "Alive: -");
  labelAlive->setBounds(0, 90, bar, 25);
  labelAlive->setColour(Label::textColourId, colorLabel);

  labelHistory = new Label("history", "History: 0");
  labelHistory->setBounds(0, 115, bar, 25);
  labelHistory->setColour(Label::textColourId, colorLabel);

  labelDStep = new Label("duration step", "Step: -");
  labelDStep->setBounds(0, 150, bar, 25);
  labelDStep->setColour(Label::textColourId, colorLabel);

  labelDDraw = new Label("duration darw", "Draw: -");
  labelDDraw->setBounds(0, 175, bar, 25);
  labelDDraw->setColour(Label::textColourId, colorLabel);

  labelMouseX = new Label("mouse x", "X: -");
  labelMouseX->setBounds(0, 220, bar, 25);
  labelMouseX->setColour(Label::textColourId, colorLabel);

  labelMouseY = new Label("mouse y", "Y: -");
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

  buttonCellColor = new CustomButton("cell color", "cell color");
  buttonCellColor->setBounds(10, 530, 110, 30);
  buttonCellColor->addListener(this);

  buttonCellAging = new CustomButton("cell aging", "cell aging");
  buttonCellAging->setBounds(10, 570, 110, 30);
  buttonCellAging->addListener(this);

  buttonGameRules = new CustomButton("rules", "rules");
  buttonGameRules->setBounds(10, 610, 110, 30);
  buttonGameRules->addListener(this);


  addAndMakeVisible(canvas);

  addAndMakeVisible(labelMapSize);

  addAndMakeVisible(labelFrame);
  addAndMakeVisible(labelAlive);
  addAndMakeVisible(labelHistory);

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
  addAndMakeVisible(buttonCellColor);
  addAndMakeVisible(buttonCellAging);
  addAndMakeVisible(buttonGameRules);


  setSize(bar + gameMapWidth * gameCellSize, gameMapHeight * gameCellSize);
  setWantsKeyboardFocus(true);
  grabKeyboardFocus();
}


#endif