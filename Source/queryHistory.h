#ifndef QUERYHISTORY_H_INCLUDED
#define QUERYHISTORY_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QueryHistory: public Component, public ButtonListener, public SliderListener {
public:
    ToggleButton* checkEnabled;
    Slider* sliderLimit;
    Label* labelWarning;

    CustomButton* buttonOk;
    CustomButton* buttonCancle;

    GameCanvas* canvas;

    QueryHistory(GameCanvas& canvas);
    ~QueryHistory();

    void show();
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider *slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryHistory)
};

#endif
