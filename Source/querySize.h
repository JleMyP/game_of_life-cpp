#ifndef QUERYSIZE_H_INCLUDED
#define QUERYSIZE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QuerySize: public Component, public Button::Listener, public Slider::Listener {
public:
    Slider* slider;
    CustomButton* buttonOk;
    CustomButton* buttonCancel;
    GameCanvas* canvas;

    explicit QuerySize(GameCanvas& canvas);
    ~QuerySize() override;

    void show();
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider *slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuerySize)
};

#endif
