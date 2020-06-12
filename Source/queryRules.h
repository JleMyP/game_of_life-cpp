#ifndef QUERYRULES_H_INCLUDED
#define QUERYRULES_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QueryRules: public Component, public Button::Listener {
public:
    explicit QueryRules(GameCanvas& canvas);
    ~QueryRules() override;

    void show();
    void buttonClicked(Button* button) override;

private:
    CustomButton* buttonOk;
    CustomButton* buttonCancel;
    GameCanvas* canvas;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryRules)
};

#endif
