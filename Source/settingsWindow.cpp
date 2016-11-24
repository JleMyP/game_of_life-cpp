#include "settingsWindow.h"
#include "MainComponent.h"



SettingsWindow::SettingsWindow(GameCanvas& _canvas) {
  setSize(200, 250);

  sizeW =  new SizeQueryWindow(_canvas);
  colorW = new ColorQueryWindow(_canvas);
  agingW = new AgingQueryWindow(_canvas);
  rulesW = new RulesQueryWindow(_canvas);

  buttonCellSize = new CustomButton("cell size", "cell size");
  buttonCellSize->setBounds(40, 10, 120, 30);
  buttonCellSize->addListener(this);

  buttonCellColor = new CustomButton("cell color", "cell color");
  buttonCellColor->setBounds(40, 50, 120, 30);
  buttonCellColor->addListener(this);

  buttonCellAging = new CustomButton("cell aging", "cell aging");
  buttonCellAging->setBounds(40, 90, 120, 30);
  buttonCellAging->addListener(this);

  buttonGameRules = new CustomButton("rules", "rules");
  buttonGameRules->setBounds(40, 130, 120, 30);
  buttonGameRules->addListener(this);
  
  buttonCancle = new CustomButton("cancle", "cancle");
  buttonCancle->setBounds(40, 190, 120, 30);
  buttonCancle->addListener(this);


  addAndMakeVisible(buttonCellSize);
  addAndMakeVisible(buttonCellColor);
  addAndMakeVisible(buttonCellAging);
  addAndMakeVisible(buttonGameRules);
  addAndMakeVisible(buttonCancle);
}


SettingsWindow::~SettingsWindow() {
  deleteAllChildren();

  delete sizeW;
  delete colorW;
  delete agingW;
  delete rulesW;
}


void SettingsWindow::show() {
  int btn = DialogWindow::showModalDialog("settings", this, nullptr, Colours::black, true);

  switch (btn) {
    case Buttons::cellSize:  sizeW->show();  break;
    case Buttons::cellColor: colorW->show(); break;
    case Buttons::cellAging: agingW->show(); break;
    case Buttons::gameRules: rulesW->show(); break;
    default: break;
  }
}


void SettingsWindow::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(Buttons::cancle);
  } else if (button == buttonCellSize) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(Buttons::cellSize);
  } else if (button == buttonCellColor) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(Buttons::cellColor);
  } else if (button == buttonCellAging) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(Buttons::cellAging);
  } else if (button == buttonGameRules) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(Buttons::gameRules);
  }
}