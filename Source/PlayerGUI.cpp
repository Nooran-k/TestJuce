#include "PlayerGUI.h"
#include "PlayerAudio.h"

PlayerGUI::PlayerGUI(PlayerAudio& audioPlayer) : playerAudio(audioPlayer)
{

    for (auto* btn : { &loadButton, &restartButton, &stopButton, &PlayButton,&pauseButton,&GoToStartButton,&GoToEndButton , &muteButton, &loopButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }


    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
    startTimerHz(10);
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 60, 40);
    restartButton.setBounds(90, y, 60, 40);
    stopButton.setBounds(160, y, 60, 40);
    pauseButton.setBounds(230, y, 60, 40);
    PlayButton.setBounds(300, y, 60, 40);
    GoToStartButton.setBounds(370, y, 70, 40);
    GoToEndButton.setBounds(450, y, 70, 40);
    volumeSlider.setBounds(20, y + 50, getWidth() - 120, 30);
    muteButton.setBounds(volumeSlider.getRight() + 10, 100, 80, 40);
    loopButton.setBounds(540, y, 70, 40);


}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    if (playerAudio.loadFile(file))
                    {
                        playerAudio.play();
                    }
                }
            });
    }

    if (button == &PlayButton)
    {
        playerAudio.play();
    }
    if (button == &stopButton)
    {
        playerAudio.stop();
    }
    if (button == &restartButton || button == &GoToStartButton)
    {
        playerAudio.setPosition(0.0);
        playerAudio.play();
    }
    if (button == &pauseButton)
    {
        playerAudio.pause();
    }
    if (button == &GoToEndButton)
    {
        playerAudio.setPosition(playerAudio.getLength() - 1);
    }
    if (button == &muteButton)
    {
        isMuted = !isMuted;
        if (isMuted)
        {
            playerAudio.setGain(0);
            muteButton.setButtonText("Unmute");
        }
        else
        {
            playerAudio.setGain(volumeSlider.getValue());
            muteButton.setButtonText("Mute");
        }
    }
    if (button == &loopButton)
    {
        isLooping = !isLooping;
        playerAudio.setLooping(isLooping);
        loopButton.setButtonText(isLooping ? "Loop: ON" : "Loop: OFF");
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());
}
void PlayerGUI::timerCallback()
{
    if (isLooping)
    {
        double pos = playerAudio.getPosition();
        double len = playerAudio.getLength();

        if (len > 0.0 && pos >= len - 0.1)
        {
            playerAudio.setPosition(0.0);
            playerAudio.play();
        }
    }
}


