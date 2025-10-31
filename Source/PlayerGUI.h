#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component, public juce::Button::Listener, public juce::Slider::Listener, public juce::Timer
{
public:
    PlayerGUI(PlayerAudio& audioPlayer);
    ~PlayerGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button*) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;

private:
    PlayerAudio& playerAudio;

    juce::TextButton loadButton{ "Load Files" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton PlayButton{ " Play " };
    juce::TextButton pauseButton{ " Pause " };
    juce::TextButton GoToStartButton{ "  |< Start " };
    juce::TextButton GoToEndButton{ " End |> " };
    juce::TextButton muteButton{ "Mute" };
    juce::TextButton loopButton{ "Loop: OFF" };
    bool isMuted = false;
    juce::Slider volumeSlider;
    bool isLooping = false;


    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};

