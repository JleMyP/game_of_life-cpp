#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"



class lifeApplication: public JUCEApplication {
public:
  lifeApplication() {}

  const String getApplicationName() override { return "Life"; }
  const String getApplicationVersion() override { return ProjectInfo::versionString; }
  bool moreThanOneInstanceAllowed() override { return true; }

  void initialise(const String& commandLine) override {
    mainWindow = new MainWindow(getApplicationName());
  }

  void shutdown() override {
    mainWindow = nullptr;
  }

  void systemRequestedQuit() override {
    quit();
  }

  class MainWindow: public DocumentWindow {
  public:
    MainWindow(String name): DocumentWindow(name, Colours::black, DocumentWindow::allButtons) {
      setResizable(true, true);

      juce::Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
      setResizeLimits(200, 600, area.getWidth(), area.getHeight());

      setUsingNativeTitleBar(true);
      setContentOwned(new MainContentComponent(), true);

      centreWithSize(getWidth(), getHeight());
      setTopLeftPosition(200, 200);
      setVisible(true);
    }

    void closeButtonPressed() override {
      JUCEApplication::getInstance()->systemRequestedQuit();
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  };

  ScopedPointer<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(lifeApplication)
