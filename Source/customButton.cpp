#include "customButton.h"


CustomButton::CustomButton(const char* name, const char* text, Colour color) : TextButton(name) {
  _text = String(text);
  font = new Font(20, Font::FontStyleFlags::bold | Font::FontStyleFlags::italic);

  TextButton::setButtonText("");
  setColour(buttonColourId, color);
  setMouseClickGrabsKeyboardFocus(false);
}

CustomButton::~CustomButton() {
  delete font;
}


void CustomButton::setText(char* text) {
  _text = String(text);
}


void CustomButton::paint(Graphics& g) {
  TextButton::paint(g);

  g.setFont(*font);
  g.setColour(Colours::black);
  g.drawText(_text, getLocalBounds(), Justification::centred);
}
