#ifndef CUSTOMBUTTON_H_INCLUDED
#define CUSTOMBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class CustomButton: public TextButton {
public:
    CustomButton(const char* name, const char* text, Colour color=Colours::lime);
    ~CustomButton() override;

    void setText(char* text);
    void paint(Graphics& g) override;

private:
    String _text;
    Font* font;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomButton)
};

#endif
