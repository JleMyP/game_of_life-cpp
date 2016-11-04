#include "MainComponent.h"



MainContentComponent::MainContentComponent() {
  Colour colorLabel = Colours::white;

  labelMapWidth = new Label("map width", "Width");
  labelMapWidth->setBounds(0, 0, bar, 25);
  labelMapWidth->setColour(labelFrame->textColourId, colorLabel);

  labelMapHeight = new Label("map height", "Height");
  labelMapHeight->setBounds(0, 25, bar, 25);
  labelMapHeight->setColour(labelFrame->textColourId, colorLabel);

  labelFrame = new Label("frame", "Frame");
  labelFrame->setBounds(0, 80, bar, 25);
  labelFrame->setColour(labelFrame->textColourId, colorLabel);

  labelAlive = new Label("alive", "Alive");
  labelAlive->setBounds(0, 105, bar, 25);
  labelAlive->setColour(labelFrame->textColourId, colorLabel);

  labelDStep = new Label("duration step", "Step");
  labelDStep->setBounds(0, 150, bar, 25);
  labelDStep->setColour(labelFrame->textColourId, colorLabel);

  labelDDraw = new Label("duration darw", "Draw");
  labelDDraw->setBounds(0, 175, bar, 25);
  labelDDraw->setColour(labelFrame->textColourId, colorLabel);

  labelMouseX = new Label("mouse x", "X:");
  labelMouseX->setBounds(0, 200, bar, 25);
  labelMouseX->setColour(labelFrame->textColourId, colorLabel);

  labelMouseY = new Label("mouse y", "Y:");
  labelMouseY->setBounds(0, 225, bar, 25);
  labelMouseY->setColour(labelFrame->textColourId, colorLabel);

  buttonNewGame = new CustomButton("new game", "new game");
  buttonNewGame->setBounds(10, 290, 110, 30);
  buttonNewGame->addListener(this);

  buttonPlay = new CustomButton("play", "play");
  buttonPlay->setBounds(10, 330, 110, 30);
  buttonPlay->addListener(this);

  buttonClear = new CustomButton("clear", "clear");
  buttonClear->setBounds(10, 370, 110, 30);
  buttonClear->addListener(this);

  buttonDraw = new CustomButton("draw", "draw");
  buttonDraw->setBounds(10, 420, 110, 30);
  buttonDraw->addListener(this);

  buttonCellSize = new CustomButton("cell size", "cell size");
  buttonCellSize->setBounds(10, 470, 110, 30);
  buttonCellSize->addListener(this);

  canvas = new GameCanvas(gameCellSize);


  addAndMakeVisible(labelMapWidth);
  addAndMakeVisible(labelMapHeight);

  addAndMakeVisible(labelFrame);
  addAndMakeVisible(labelAlive);

  addAndMakeVisible(labelDStep);
  addAndMakeVisible(labelDDraw);

  addAndMakeVisible(labelMouseX);
  addAndMakeVisible(labelMouseY);
  
  addAndMakeVisible(buttonNewGame);
  addAndMakeVisible(buttonPlay);
  addAndMakeVisible(buttonClear);
  addAndMakeVisible(buttonDraw);
  addAndMakeVisible(buttonCellSize);

  addAndMakeVisible(canvas);


  setSize(bar + gameMapWidth * gameCellSize, gameMapHeight * gameCellSize);
  setWantsKeyboardFocus(true);
  grabKeyboardFocus();
}


MainContentComponent::~MainContentComponent() {
  deleteAllChildren();
}


//void MainContentComponent::hiResTimerCallback() {
void MainContentComponent::timerCallback() {
  repaint();

  labelFrame->setText(String::formatted("Frame: %i", canvas->frame), NotificationType::dontSendNotification);
  labelAlive->setText(String::formatted("Alive: %i", canvas->alive), NotificationType::dontSendNotification);
  labelDStep->setText(String::formatted("Step per: %i", canvas->durationStep), NotificationType::dontSendNotification);
  labelDDraw->setText(String::formatted("Draw per: %i", canvas->durationDraw), NotificationType::dontSendNotification);
}


void MainContentComponent::resized() {
  canvas->setBounds(bar, 0, getWidth() - bar, getHeight());

  labelMapWidth->setText(String::formatted("Width: %i", canvas->mapWidth), NotificationType::dontSendNotification);
  labelMapHeight->setText(String::formatted("height: %i", canvas->mapHeight), NotificationType::dontSendNotification);
}


void MainContentComponent::buttonClicked(Button* button) {
  if (button == buttonPlay) {
    if (isTimerRunning()) {
      stopTimer();
      canvas->running = false;
      buttonPlay->setText("start");
    } else {
      startTimer(1);
      canvas->running = true;
      buttonPlay->setText("pause");
    }
  } else if (button == buttonNewGame) {
    canvas->newGame();
    repaint();
  } else if (button == buttonClear) {
    canvas->running = false;
    canvas->newGame(true);

    labelFrame->setText("Frame: 0", NotificationType::dontSendNotification);
    labelAlive->setText("Alive: 0", NotificationType::dontSendNotification);
    buttonPlay->setText("start");
    
    stopTimer();
    repaint();
  } else if (button == buttonDraw) {
    canvas->draw = !canvas->draw;
    buttonDraw->setText(canvas->draw ? "draw" : "erase");
  } else if (button == buttonCellSize) {
    DialogWindow::LaunchOptions options;

    Component* main = new Component("main");

    CustomButton* btnOk = new CustomButton("ok", "ok");
    btnOk->setBounds(30, 150, 110, 30);

    CustomButton* btnCancle = new CustomButton("cancle", "cancle");
    btnCancle->setBounds(160, 150, 110, 30);
    btnCancle->addListener(this);

    main->addAndMakeVisible(btnOk);
    main->addAndMakeVisible(btnCancle);
    options.content.setOwned(main);

    options.content->setSize(300, 200);

    options.dialogTitle = "cell size";
    options.dialogBackgroundColour = Colours::black;
    options.escapeKeyTriggersCloseButton = true;
    //options.useNativeTitleBar = false;
    //options.resizable = true;

    dw = options.launchAsync();
    dw->centreWithSize(300, 200);
  } else if (button->getName() == "cancle") {
    dw->closeButtonPressed();
    //delete dw;
  }
}


bool MainContentComponent::keyPressed(const KeyPress& key) {
  int keyCode = key.getKeyCode();
  juce_wchar keyChar = key.getTextCharacter();

  if (keyCode == key.spaceKey) buttonClicked(buttonPlay);
  else if (keyCode == key.returnKey) buttonClicked(buttonNewGame);
  else if (keyCode == key.escapeKey) JUCEApplication::getInstance()->systemRequestedQuit();
  else if (keyChar == 'c') buttonClicked(buttonClear);
  else if (keyCode == key.rightKey) {
    canvas->step();
    timerCallback();
  }

  return false;
}
