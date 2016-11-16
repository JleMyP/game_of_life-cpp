#ifndef AGINGWINDOW_H_INCLUDED
#define AGINGWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "gameCanvas.h"
#include "customButton.h"



class AgingQueryWindow : public Component, public ButtonListener {
public:
  Label* labelRate;
  Label* labelGradations;

  Slider* sliderRate;
  Slider* sliderGradations;

  CustomButton* buttonOk;
  CustomButton* buttonCancle;

  GameCanvas* canvas;

  AgingQueryWindow(GameCanvas& canvas);

  ~AgingQueryWindow();

  void show();

  void buttonClicked(Button* button) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AgingQueryWindow)
};

#endif