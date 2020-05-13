#ifndef GAMECANVAS_H_INCLUDED
#define GAMECANVAS_H_INCLUDED

#include <chrono>

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
    enum penModes { erase, draw, select, length };
    char* penStr[3] = { "erase", "draw", "select" };

    Colour penColor;
    penModes penMode = penModes::draw;
    int penWidth = 2;
    int maxPenWidth = 10;

    Point<int> selectStart;
    Point<int> selectEnd;
    Point<int> mousePos;

    char cellSize;
    float rateAging = 5;

    unsigned long durationDraw;
    std::chrono::high_resolution_clock::time_point last_draw;
    unsigned long fps;
    bool running = false;

    GameCanvas(char cellSize, Colour color=Colours::lime);
    ~GameCanvas();

    void mouseMove(const MouseEvent & event) override;
    void mouseDown(const MouseEvent & event) override;
    void mouseDrag(const MouseEvent & event) override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

    void drawRect(int x, int y);

    void paint(Graphics& g) override;
    void resized() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GameCanvas)
};

#endif
