#ifndef QUERYCOLOR_H_INCLUDED
#define QUERYCOLOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "gameCanvas.h"
#include "customButton.h"


class QueryColor: public Component, public Button::Listener, ChangeListener {
public:
    explicit QueryColor(GameCanvas& canvas);
    ~QueryColor() override;

    void show();
    void buttonClicked(Button* button) override;
    void changeListenerCallback(ChangeBroadcaster* sender) override;

private:
    ColourSelector* selector;
    CustomButton* buttonOk;
    CustomButton* buttonCancel;
    GameCanvas* canvas;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryColor)
};

#endif
