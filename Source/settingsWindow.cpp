#include "settingsWindow.h"


SettingsWindow::SettingsWindow(GameCanvas& _canvas) {
    setSize(500, 300);

    sizeW =  new QuerySize(_canvas);
    colorW = new QueryColor(_canvas);
    agingW = new QueryAging(_canvas);
    historyW = new QueryHistory(_canvas);
    rulesW = new QueryRules(_canvas);

    buttonCellSize = new CustomButton("cell size", "cell size");
    buttonCellSize->setBounds(40, 10, 120, 30);
    buttonCellSize->addListener(this);

    buttonCellColor = new CustomButton("cell color", "cell color");
    buttonCellColor->setBounds(40, 50, 120, 30);
    buttonCellColor->addListener(this);

    buttonCellAging = new CustomButton("cell aging", "cell aging");
    buttonCellAging->setBounds(40, 90, 120, 30);
    buttonCellAging->addListener(this);

    buttonHistory = new CustomButton("history", "history");
    buttonHistory->setBounds(40, 130, 120, 30);
    buttonHistory->addListener(this);

    buttonGameRules = new CustomButton("rules", "rules");
    buttonGameRules->setBounds(40, 170, 120, 30);
    buttonGameRules->addListener(this);

    buttonClose = new CustomButton("close", "close");
    buttonClose->setBounds(40, 230, 120, 30);
    buttonClose->addListener(this);

    addAndMakeVisible(buttonCellSize);
    addAndMakeVisible(buttonCellColor);
    addAndMakeVisible(buttonCellAging);
    addAndMakeVisible(buttonHistory);
    addAndMakeVisible(buttonGameRules);
    addAndMakeVisible(buttonClose);

    sizeW->setTopLeftPosition(200, 0);
    colorW->setTopLeftPosition(200, 0);
    agingW->setTopLeftPosition(200, 0);
    historyW->setTopLeftPosition(200, 0);
    rulesW->setTopLeftPosition(200, 0);

    addChildComponent(sizeW);
    addChildComponent(colorW);
    addChildComponent(agingW);
    addChildComponent(historyW);
    addChildComponent(rulesW);
}


SettingsWindow::~SettingsWindow() {
    deleteAllChildren();
}


void SettingsWindow::show() {
    DialogWindow::showModalDialog("settings", this, nullptr, Colours::black, true);
}


void SettingsWindow::hideAll() {
    sizeW->setVisible(false);
    colorW->setVisible(false);
    agingW->setVisible(false);
    historyW->setVisible(false);
    rulesW->setVisible(false);
}


void SettingsWindow::buttonClicked(Button* button) {
    hideAll();

    if (button == buttonClose) {
        if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
            dw->exitModalState(0);
    } else if (button == buttonCellSize)
        sizeW->show();
    else if (button == buttonCellColor)
        colorW->show();
    else if (button == buttonCellAging)
        agingW->show();
    else if (button == buttonHistory)
        historyW->show();
    else if (button == buttonGameRules)
        rulesW->show();
}
