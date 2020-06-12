#ifndef QUERYAGING_H_INCLUDED
#define QUERYAGING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QueryAging: public Component, public Button::Listener, public Slider::Listener {
public:
    Label* labelRate;
    Label* labelGradations;

    Slider* sliderRate;
    Slider* sliderGradations;

    CustomButton* buttonOk;
    CustomButton* buttonCancel;

    GameCanvas* canvas;

    explicit QueryAging(GameCanvas& canvas);
    ~QueryAging() override;

    void show();
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider *slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryAging)
};

#endif
