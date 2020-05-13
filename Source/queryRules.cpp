#include "queryRules.h"
#include "MainComponent.h"


QueryRules::QueryRules(GameCanvas& canvas): canvas(&canvas) {
    setSize(300, 300);

    buttonOk = new CustomButton("rules ok", "ok");
    buttonOk->setBounds(30, 160, 110, 30);
    buttonOk->addListener(this);

    buttonCancle = new CustomButton("rules cancle", "cancle");
    buttonCancle->setBounds(160, 160, 110, 30);
    buttonCancle->addListener(this);

    addAndMakeVisible(buttonOk);
    addAndMakeVisible(buttonCancle);
}


QueryRules::~QueryRules() {
    deleteAllChildren();
}


void QueryRules::show() {
    setVisible(true);
}


void QueryRules::buttonClicked(Button* button) {
    if (button == buttonCancle) {

    } else if (button == buttonOk) {

    }
}
