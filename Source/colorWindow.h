#ifndef COLORWINDOW_H_INCLUDED
#define COLORWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "gameCanvas.h"
#include "customButton.h"



class ColorQueryWindow: public Component, public ButtonListener {
public:
  ColourSelector* selector;
  CustomButton* buttonOk;
  CustomButton* buttonCancle;
  GameCanvas* canvas;

  ColorQueryWindow(GameCanvas& canvas);

  ~ColorQueryWindow();

  void show();

  void buttonClicked(Button* button) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorQueryWindow)
};

#endif