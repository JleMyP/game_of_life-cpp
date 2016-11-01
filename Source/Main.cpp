#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"



class jucegui2Application : public JUCEApplication {
public:
  jucegui2Application() {}

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

  void anotherInstanceStarted(const String& commandLine) override {
    
  }

  class MainWindow : public DocumentWindow {
  public:
    MainWindow(String name) : DocumentWindow(name, Colours::black, DocumentWindow::allButtons) {
      setResizable(true, true);
//      setResizeLimits();
      setUsingNativeTitleBar(true);
      setContentOwned(new MainContentComponent(), true);

      centreWithSize(getWidth(), getHeight());
      setVisible(true);
    }

    void closeButtonPressed() override {
      JUCEApplication::getInstance()->systemRequestedQuit();
    }

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  };

private:
  ScopedPointer<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(jucegui2Application)
