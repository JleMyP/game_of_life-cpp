#include "queryRules.h"


QueryRules::QueryRules(GameCanvas& canvas): canvas(&canvas) {
    setSize(300, 300);

    buttonOk = new CustomButton("rules ok", "ok");
    buttonOk->setBounds(30, 160, 110, 30);
    buttonOk->addListener(this);

    buttonCancel = new CustomButton("rules cancel", "cancel");
    buttonCancel->setBounds(160, 160, 110, 30);
    buttonCancel->addListener(this);

    addAndMakeVisible(buttonOk);
    addAndMakeVisible(buttonCancel);
}


QueryRules::~QueryRules() {
    deleteAllChildren();
}


void QueryRules::show() {
    setVisible(true);
}


void QueryRules::buttonClicked(Button* button) {
    if (button == buttonCancel) {

    } else if (button == buttonOk) {

    }
}
