#ifndef CUSTOMBUTTON_H_INCLUDED
#define CUSTOMBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"



class CustomButton: public TextButton {
public:
  String _text;
  Font* font;

  CustomButton(const char* name, const char* text, Colour color = Colours::lime);
  ~CustomButton();

  void setText(char* text);
  void paint(Graphics& g) override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomButton)
};

#endif