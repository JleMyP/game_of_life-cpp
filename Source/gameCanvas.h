#ifndef GAMECANVAS_H_INCLUDED
#define GAMECANVAS_H_INCLUDED

#include <ctime>
#include "../JuceLibraryCode/JuceHeader.h"
#include "life.h"



class GameCanvas : public Component, public Life {
public:
  //MainContentComponent* parent;
  enum penModes { draw, erase, select };
  char* penStr[3] = { "draw", "erase", "select" };

  Colour penColor;
  penModes penMode = penModes::draw;
  int mouseX, mouseY;
  unsigned char cellSize;

  int durationDraw;
  bool running = false;

  GameCanvas(unsigned char cellSize, Colour color = Colours::lime);
  ~GameCanvas();

  void mouseMove(const MouseEvent & event) override;
  void mouseDown(const MouseEvent & event) override;
  void mouseDrag(const MouseEvent & event) override;
  
  void paint(Graphics& g) override;
  void resized() override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GameCanvas)
};

#endif