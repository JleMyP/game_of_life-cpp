#include "querySize.h"
#include "mainComponent.h"


QuerySize::QuerySize(GameCanvas& canvas): canvas(&canvas) {
    setSize(300, 300);

    slider = new Slider();
    slider->setRange(2, 10, 1);
    slider->setBounds(50, 60, 200, 50);
    slider->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
    slider->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
    slider->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);
    slider->addListener(this);

    buttonOk = new CustomButton("size ok", "ok");
    buttonOk->setBounds(30, 160, 110, 30);
    buttonOk->addListener(this);

    buttonCancel = new CustomButton("size cancel", "cancel");
    buttonCancel->setBounds(160, 160, 110, 30);
    buttonCancel->addListener(this);

    addAndMakeVisible(slider);
    addAndMakeVisible(buttonOk);
    addAndMakeVisible(buttonCancel);
}


QuerySize::~QuerySize() {
    deleteAllChildren();
}


void QuerySize::show() {
    slider->setValue(canvas->cellSize);
    setVisible(true);
    buttonOk->setEnabled(false);
    buttonCancel->setEnabled(false);
}


void QuerySize::buttonClicked(Button* button) {
    if (button == buttonCancel) {
        slider->setValue(canvas->cellSize);
        buttonOk->setEnabled(false);
        buttonCancel->setEnabled(false);
    } else if (button == buttonOk) {
        int cell = int(slider->getValue());
        unsigned int mapWidth = canvas->getWidth() / cell;
        unsigned int mapHeight = canvas->getHeight() / cell;

        auto* parent = canvas->findParentComponentOfClass<MainContentComponent>();
        parent->labelMapSize->setText(String::formatted("Size: %ix%i", mapWidth, mapHeight), dontSendNotification);

        canvas->cellSize = (unsigned char)cell;
        canvas->resizeMap(mapWidth, mapHeight);
        canvas->newGame();
        canvas->repaint();

        buttonOk->setEnabled(false);
        buttonCancel->setEnabled(false);
    }
}


void QuerySize::sliderValueChanged(Slider *_slider) {
    bool enabled = _slider->getValue() != canvas->cellSize;

    buttonOk->setEnabled(enabled);
    buttonCancel->setEnabled(enabled);
}
