#ifndef QUERYCOLOR_H_INCLUDED
#define QUERYCOLOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "gameCanvas.h"
#include "customButton.h"



class QueryColor: public Component, public ButtonListener, juce::ChangeListener {
public:
  ColourSelector* selector;
  CustomButton* buttonOk;
  CustomButton* buttonCancle;
  GameCanvas* canvas;

  QueryColor(GameCanvas& canvas);
  ~QueryColor();

  void show();
  void buttonClicked(Button* button) override;
  void changeListenerCallback(ChangeBroadcaster* sender);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryColor)
};

#endif