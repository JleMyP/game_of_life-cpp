#ifndef SIZEWINDOW_H_INCLUDED
#define SIZEWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "gameCanvas.h"
#include "customButton.h"



class SizeQueryWindow : public Component, public ButtonListener {
public:
  Slider* slider;
  CustomButton* buttonOk;
  CustomButton* buttonCancle;
  GameCanvas* canvas;

  SizeQueryWindow(GameCanvas& canvas);

  ~SizeQueryWindow();

  void show();

  void buttonClicked(Button* button) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SizeQueryWindow)
};

#endif