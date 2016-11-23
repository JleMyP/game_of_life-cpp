#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"

#include "sizeWindow.h"
#include "colorWindow.h"
#include "agingWindow.h"
#include "rulesWindow.h"



class MainContentComponent :
  public Component,
  public Timer,
  public ButtonListener {
public:
  unsigned int gameMapWidth = 300;
  unsigned int gameMapHeight = 220;
  unsigned char gameCellSize = 3;

  unsigned int bar = 130;


  Label* labelMapSize;

  Label* labelFrame;
  Label* labelAlive;
  Label* labelHistory;
  
  Label* labelDStep;
  Label* labelDDraw;
  
  Label* labelMouseX;
  Label* labelMouseY;
  
  Label* labelPenWidth;

  CustomButton* buttonNewGame;
  CustomButton* buttonPlay;
  CustomButton* buttonClear;
  CustomButton* buttonDraw;

  CustomButton* buttonCellSize;
  CustomButton* buttonCellColor;
  CustomButton* buttonCellAging;
  CustomButton* buttonGameRules;

  GameCanvas canvas;


  SizeQueryWindow* sizeW;
  ColorQueryWindow* colorW;
  AgingQueryWindow* agingW;
  RulesQueryWindow* rulesW;


  MainContentComponent();
  ~MainContentComponent();


  void initMainW();

  void playCallback();
  void newGameCallback();
  void clearCallback();
  void drawCallback();

  void timerCallback() override;
  void buttonClicked(Button* button) override;
  bool keyPressed(const KeyPress& key) override;
  void resized() override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


#endif
