#include "queryColor.h"


QueryColor::QueryColor(GameCanvas& canvas): canvas(&canvas) {
    setSize(300, 300);

    selector = new ColourSelector(
        ColourSelector::showColourAtTop |
        ColourSelector::showColourspace
    );

    selector->setBounds(0, 0, 300, 250);
    selector->setColour(ColourSelector::backgroundColourId, Colours::black);
    selector->addChangeListener(this);

    buttonOk = new CustomButton("color ok", "ok");
    buttonOk->setBounds(30, 260, 110, 30);
    buttonOk->addListener(this);

    buttonCancel = new CustomButton("color cancel", "cancel");
    buttonCancel->setBounds(160, 260, 110, 30);
    buttonCancel->addListener(this);

    addAndMakeVisible(selector);
    addAndMakeVisible(buttonOk);
    addAndMakeVisible(buttonCancel);
}


QueryColor::~QueryColor() {
    deleteAllChildren();
}


void QueryColor::show() {
    selector->setCurrentColour(canvas->penColor);
    setVisible(true);
    buttonOk->setEnabled(false);
    buttonCancel->setEnabled(false);
}


void QueryColor::buttonClicked(Button* button) {
    if (button == buttonCancel) {
        selector->setCurrentColour(canvas->penColor);
        buttonOk->setEnabled(false);
        buttonCancel->setEnabled(false);
    } else if (button == buttonOk) {
        Colour color = selector->getCurrentColour();
        canvas->penColor = color;
        canvas->repaint();
        buttonOk->setEnabled(false);
        buttonCancel->setEnabled(false);
    }
}


void QueryColor::changeListenerCallback(ChangeBroadcaster* sender) {
    bool enabled = selector->getCurrentColour() != canvas->penColor;
    buttonOk->setEnabled(enabled);
    buttonCancel->setEnabled(enabled);
}
