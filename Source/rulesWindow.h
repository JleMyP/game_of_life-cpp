#ifndef RULESWINDOW_H_INCLUDED
#define RULESWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "gameCanvas.h"
#include "customButton.h"



class RulesQueryWindow : public Component, public ButtonListener {
public:
  CustomButton* buttonOk;
  CustomButton* buttonCancle;
  GameCanvas* canvas;

  RulesQueryWindow(GameCanvas& canvas);

  ~RulesQueryWindow();

  void show();

  void buttonClicked(Button* button) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RulesQueryWindow)
};

#endif