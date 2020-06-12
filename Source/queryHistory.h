#ifndef QUERYHISTORY_H_INCLUDED
#define QUERYHISTORY_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QueryHistory: public Component, public Button::Listener, public Slider::Listener {
public:
    explicit QueryHistory(GameCanvas& canvas);
    ~QueryHistory() override;

    void show();
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider *slider) override;

private:
    ToggleButton* checkEnabled;
    Slider* sliderLimit;
    Label* labelWarning;

    CustomButton* buttonOk;
    CustomButton* buttonCancel;

    GameCanvas* canvas;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryHistory)
};

#endif
