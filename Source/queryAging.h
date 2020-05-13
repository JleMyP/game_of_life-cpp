#ifndef QUERYAGING_H_INCLUDED
#define QUERYAGING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QueryAging: public Component, public ButtonListener, public SliderListener {
public:
    Label* labelRate;
    Label* labelGradations;

    Slider* sliderRate;
    Slider* sliderGradations;

    CustomButton* buttonOk;
    CustomButton* buttonCancle;

    GameCanvas* canvas;

    QueryAging(GameCanvas& canvas);
    ~QueryAging();

    void show();
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider *slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryAging)
};

#endif
