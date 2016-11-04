#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "gameCanvas.h"
#include "customButton.h"



class MainContentComponent :
  public Component,
  //public juce::HighResolutionTimer,
  public Timer,
  public ButtonListener {
public:
  unsigned int gameMapWidth = 300;
  unsigned int gameMapHeight = 200;
  unsigned char gameCellSize = 3;

  unsigned int bar = 130;

  Label* labelMapWidth;
  Label* labelMapHeight;
  Label* labelFrame;
  Label* labelAlive;
  Label* labelDStep;
  Label* labelDDraw;
  Label* labelMouseX;
  Label* labelMouseY;

  CustomButton* buttonNewGame;
  CustomButton* buttonPlay;
  CustomButton* buttonClear;
  CustomButton* buttonDraw;

  CustomButton* buttonCellSize;

  GameCanvas* canvas;

  DialogWindow* dw = nullptr;

  MainContentComponent();
  ~MainContentComponent();

// void hiResTimerCallback() override;
  void timerCallback() override;
  void buttonClicked(Button* button) override;
  bool keyPressed(const KeyPress& key) override;
  void resized() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


#endif // MAINCOMPONENT_H_INCLUDED
