#include "rulesWindow.h"
#include "MainComponent.h"



RulesQueryWindow::RulesQueryWindow(GameCanvas& canvas) : canvas(&canvas) {
  setSize(400, 150);

  buttonOk = new CustomButton("rules ok", "ok");
  buttonOk->setBounds(60, 100, 110, 30);
  buttonOk->addListener(this);

  buttonCancle = new CustomButton("rules cancle", "cancle");
  buttonCancle->setBounds(230, 100, 110, 30);
  buttonCancle->addListener(this);

  addAndMakeVisible(buttonOk);
  addAndMakeVisible(buttonCancle);
}


RulesQueryWindow::~RulesQueryWindow() {
  deleteAllChildren();
}


void RulesQueryWindow::show() {
  int result = DialogWindow::showModalDialog("rules", this, nullptr, Colours::black, true);

  if (result != 0) {
    
  }
}


void RulesQueryWindow::buttonClicked(Button* button) {
  if (button == buttonCancle) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(0);
  } else if (button == buttonOk) {
    if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
      dw->exitModalState(1);
  }
}