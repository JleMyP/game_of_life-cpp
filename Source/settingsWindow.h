#ifndef SETTINGSWINDOW_H_INCLUDED
#define SETTINGSWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "customButton.h"
#include "querySize.h"
#include "queryColor.h"
#include "queryAging.h"
#include "queryHistory.h"
#include "queryRules.h"


class SettingsWindow: public Component, public ButtonListener {
public:
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

    SettingsWindow(GameCanvas& canvas);
    ~SettingsWindow();

    void show();
    void hideAll();
    void buttonClicked(Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsWindow)
};

#endif
