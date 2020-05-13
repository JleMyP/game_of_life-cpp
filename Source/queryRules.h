#ifndef QUERYRULES_H_INCLUDED
#define QUERYRULES_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QueryRules: public Component, public ButtonListener {
public:
    CustomButton* buttonOk;
    CustomButton* buttonCancle;
    GameCanvas* canvas;

    QueryRules(GameCanvas& canvas);
    ~QueryRules();

    void show();
    void buttonClicked(Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryRules)
};

#endif
