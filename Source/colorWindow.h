#ifndef COLORWINDOW_H_INCLUDED
#define COLORWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"



class ColourSelectorWindow: public DocumentWindow, private ChangeListener {
public:
  ColourSelector selector;

  ColourSelectorWindow(const String& name, Colour backgroundColour, int buttonsNeeded) :
    DocumentWindow(name, backgroundColour, buttonsNeeded),
    selector(
      ColourSelector::showColourAtTop |
      ColourSelector::showSliders |
      ColourSelector::showColourspace
    ) {
      selector.setCurrentColour(backgroundColour);
      selector.setColour(ColourSelector::backgroundColourId, Colours::transparentWhite);
      setContentOwned(&selector, false);
  }

  ~ColourSelectorWindow() { }

  void closeButtonPressed() {
    delete this;
  }

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColourSelectorWindow)
};

#endif