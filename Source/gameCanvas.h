#ifndef GAMECANVAS_H_INCLUDED
#define GAMECANVAS_H_INCLUDED

#include <chrono>
#include <cmath>

#include "../JuceLibraryCode/JuceHeader.h"

#include "life.h"

// TODO
/*
    ������� ����� �� ����� ���������
    ��������� ������� ������
    ���������
*/


class GameCanvas: public Component, public Life {
public:
    enum PenModes { ERASE, DRAW, _length };
    String penStr[2] = { "erase", "draw" };

    Colour penColor;
    PenModes penMode = PenModes::DRAW;
    int penWidth = 2;
    int maxPenWidth = 30;

    Point<int> mousePos;

    unsigned char cellSize;
    unsigned int rateAging = 5;

    unsigned long durationDraw = 0;
    unsigned long fps = 0;
    bool running = false;

    explicit GameCanvas(char cellSize, Colour color=Colours::lime);

    void mouseMove(const MouseEvent & event) override;
    void mouseDown(const MouseEvent & event) override;
    void mouseDrag(const MouseEvent & event) override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

    void drawRect(int x, int y);

    void paint(Graphics& g) override;
    void resized() override;

private:
    std::chrono::high_resolution_clock::time_point lastDraw;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GameCanvas)
};

#endif
