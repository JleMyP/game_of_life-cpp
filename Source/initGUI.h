#ifndef INITGUI_H_INCLUDED
#define INITGUI_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "mainComponent.h"

// TODO: to move .cpp


void MainContentComponent::initMainW() {
    Colour colorLabel = Colours::white;
    int buttonsStart = 360;

    labelMapSize = new Label("map size", String::formatted("Size: %ix%i", gameMapWidth, gameMapHeight));
    labelMapSize->setBounds(0, 0, bar, 25);
    labelMapSize->setColour(Label::textColourId, colorLabel);

    labelFrame = new Label("frame", "Frame: 0");
    labelFrame->setBounds(0, 65, bar, 25);
    labelFrame->setColour(Label::textColourId, colorLabel);

    labelFps = new Label("fps", "FPS: 0");
    labelFps->setBounds(0, 90, bar, 25);
    labelFps->setColour(Label::textColourId, colorLabel);

    labelAlive = new Label("alive", "Alive: -");
    labelAlive->setBounds(0, 115, bar, 25);
    labelAlive->setColour(Label::textColourId, colorLabel);

    labelHistory = new Label("history", "History: 0");
    labelHistory->setBounds(0, 140, bar, 25);
    labelHistory->setColour(Label::textColourId, colorLabel);

    labelRam = new Label("ram", "Free ram: -");
    labelRam->setBounds(0, 175, bar, 25);
    labelRam->setColour(Label::textColourId, colorLabel);

    labelDStep = new Label("duration step", "Step: -");
    labelDStep->setBounds(0, 200, bar, 25);
    labelDStep->setColour(Label::textColourId, colorLabel);

    labelDDraw = new Label("duration draw", "Draw: -");
    labelDDraw->setBounds(0, 225, bar, 25);
    labelDDraw->setColour(Label::textColourId, colorLabel);

    labelMouseX = new Label("mouse x", "X: -");
    labelMouseX->setBounds(0, 270, bar, 25);
    labelMouseX->setColour(Label::textColourId, colorLabel);

    labelMouseY = new Label("mouse y", "Y: -");
    labelMouseY->setBounds(0, 295, bar, 25);
    labelMouseY->setColour(Label::textColourId, colorLabel);

    labelPenWidth = new Label("pen width", "pen width: " + String(canvas.penWidth));
    labelPenWidth->setBounds(0, 320, bar, 25);
    labelPenWidth->setColour(Label::textColourId, colorLabel);

    buttonNewGame = new CustomButton("new game", "new game");
    buttonNewGame->setBounds(10, buttonsStart, 110, 30);
    buttonNewGame->addListener(this);

    buttonPlay = new CustomButton("play", "play");
    buttonPlay->setBounds(10, buttonsStart + 40, 110, 30);
    buttonPlay->addListener(this);

    buttonClear = new CustomButton("clear", "clear");
    buttonClear->setBounds(10, buttonsStart + 80, 110, 30);
    buttonClear->addListener(this);

    buttonDraw = new CustomButton("draw", "draw");
    buttonDraw->setBounds(10, buttonsStart + 130, 110, 30);
    buttonDraw->addListener(this);

    buttonSettings = new CustomButton("settings", "settings");
    buttonSettings->setBounds(10, buttonsStart + 180, 110, 30);
    buttonSettings->addListener(this);

    addAndMakeVisible(canvas);

    addAndMakeVisible(labelMapSize);

    addAndMakeVisible(labelFrame);
    addAndMakeVisible(labelFps);
    addAndMakeVisible(labelAlive);
    addAndMakeVisible(labelHistory);
    addAndMakeVisible(labelRam);

    addAndMakeVisible(labelDStep);
    addAndMakeVisible(labelDDraw);

    addAndMakeVisible(labelMouseX);
    addAndMakeVisible(labelMouseY);
    addAndMakeVisible(labelPenWidth);

    addAndMakeVisible(buttonNewGame);
    addAndMakeVisible(buttonPlay);
    addAndMakeVisible(buttonClear);
    addAndMakeVisible(buttonDraw);
    addAndMakeVisible(buttonSettings);

    setSize(bar + gameMapWidth * gameCellSize, gameMapHeight * gameCellSize);
    setWantsKeyboardFocus(true);
}

#endif
