#include <memory>

#include "../JuceLibraryCode/JuceHeader.h"

#include "mainComponent.h"


class lifeApplication: public JUCEApplication {
public:
    lifeApplication() = default;

    const String getApplicationName() override { return "Life"; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const String& commandLine) override {
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override {
        quit();
    }

    class MainWindow: public DocumentWindow {
    public:
        explicit MainWindow(const String& name): DocumentWindow(name, Colours::black, DocumentWindow::allButtons) {
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

    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(lifeApplication)
