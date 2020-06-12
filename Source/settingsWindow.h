#ifndef SETTINGSWINDOW_H_INCLUDED
#define SETTINGSWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "customButton.h"
#include "querySize.h"
#include "queryColor.h"
#include "queryAging.h"
#include "queryHistory.h"
#include "queryRules.h"


class SettingsWindow: public Component, public Button::Listener {
public:
    explicit SettingsWindow(GameCanvas& canvas);
    ~SettingsWindow() override;

    void show();
    void hideAll() const;
    void buttonClicked(Button* button) override;

private:
    CustomButton* buttonCellSize;
    CustomButton* buttonCellColor;
    CustomButton* buttonCellAging;
    CustomButton* buttonHistory;
    CustomButton* buttonGameRules;
    CustomButton* buttonClose;

    QuerySize* sizeW;
    QueryColor* colorW;
    QueryAging* agingW;
    QueryHistory* historyW;
    QueryRules* rulesW;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsWindow)
};

#endif
