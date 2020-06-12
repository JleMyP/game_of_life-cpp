#include "queryAging.h"


QueryAging::QueryAging(GameCanvas& canvas): canvas(&canvas) {
    setSize(300, 210);

    labelRate = new Label("rate label", "Rate:");
    labelRate->setBounds(20, 30, 100, 50);
    labelRate->setColour(Label::textColourId, Colours::white);

    labelGradations = new Label("gradations label", "Gradations:");
    labelGradations->setBounds(20, 90, 100, 50);
    labelGradations->setColour(Label::textColourId, Colours::white);

    sliderRate = new Slider();
    sliderRate->setRange(1, 100, 1);
    sliderRate->setBounds(100, 30, 180, 50);
    sliderRate->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 50);
    sliderRate->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
    sliderRate->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
    sliderRate->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);
    sliderRate->addListener(this);

    sliderGradations = new Slider();
    sliderGradations->setRange(1, 10, 1);
    sliderGradations->setBounds(100, 90, 180, 50);
    sliderGradations->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 50);
    sliderGradations->setColour(Slider::ColourIds::textBoxBackgroundColourId, Colours::black);
    sliderGradations->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
    sliderGradations->setColour(Slider::ColourIds::textBoxTextColourId, Colours::lime);
    sliderGradations->addListener(this);

    buttonOk = new CustomButton("aging ok", "ok");
    buttonOk->setBounds(30, 160, 110, 30);
    buttonOk->addListener(this);

    buttonCancel = new CustomButton("aging cancel", "cancel");
    buttonCancel->setBounds(160, 160, 110, 30);
    buttonCancel->addListener(this);

    addAndMakeVisible(labelRate);
    addAndMakeVisible(labelGradations);

    addAndMakeVisible(sliderRate);
    addAndMakeVisible(sliderGradations);

    addAndMakeVisible(buttonOk);
    addAndMakeVisible(buttonCancel);
}


QueryAging::~QueryAging() {
    deleteAllChildren();
}


void QueryAging::show() {
    sliderRate->setValue(canvas->rateAging);
    sliderGradations->setValue(canvas->maxAge / canvas->rateAging);

    setVisible(true);
    buttonOk->setEnabled(false);
    buttonCancel->setEnabled(false);
}


void QueryAging::buttonClicked(Button* button) {
    if (button == buttonCancel) {
        sliderRate->setValue(canvas->rateAging);
        sliderGradations->setValue(canvas->maxAge / canvas->rateAging);
        buttonOk->setEnabled(false);
        buttonCancel->setEnabled(false);
    } else if (button == buttonOk) {
        canvas->rateAging = (int)sliderRate->getValue();
        canvas->maxAge = (cellType)(sliderRate->getValue() * sliderGradations->getValue());
        buttonOk->setEnabled(false);
        buttonCancel->setEnabled(false);
    }
}


void QueryAging::sliderValueChanged(Slider *slider) {
    int rate = int(sliderRate->getValue());
    int gradations = int(sliderGradations->getValue());

    if (slider == sliderGradations) {
        if (gradations == 1)
            sliderRate->setEnabled(false);
        else if (!sliderRate->isEnabled())
            sliderRate->setEnabled(true);
    }

    bool enabled = rate != canvas->rateAging || gradations * rate != canvas->maxAge;

    buttonOk->setEnabled(enabled);
    buttonCancel->setEnabled(enabled);
}
