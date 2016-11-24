#ifndef SETTINGSWINDOW_H_INCLUDED
#define SETTINGSWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "customButton.h"

#include "sizeWindow.h"
#include "colorWindow.h"
#include "agingWindow.h"
#include "rulesWindow.h"



class SettingsWindow : public Component, public ButtonListener {
public:
  CustomButton* buttonCellSize;
  CustomButton* buttonCellColor;
  CustomButton* buttonCellAging;
  CustomButton* buttonGameRules;
  CustomButton* buttonCancle;

  enum Buttons {
    cancle,
    cellSize,
    cellColor,
    cellAging,
    gameRules
  };


  SizeQueryWindow* sizeW;
  ColorQueryWindow* colorW;
  AgingQueryWindow* agingW;
  RulesQueryWindow* rulesW;

  SettingsWindow(GameCanvas& canvas);

  ~SettingsWindow();

  void show();

  void buttonClicked(Button* button) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsWindow)
};

#endif