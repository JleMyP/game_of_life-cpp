#ifndef SIZEWINDOW_H_INCLUDED
#define SIZEWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SizeWindow : public DocumentWindow {
public:
  SizeWindow(const String& name, Colour backgroundColour, int buttonsNeeded);

  void closeButtonPressed();

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SizeWindow)
};
#endif