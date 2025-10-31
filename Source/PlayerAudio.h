#pragma once
#include <JuceHeader.h>

class PlayerAudio : public juce::AudioSource
{
public:
    PlayerAudio();
    ~PlayerAudio() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    bool loadFile(const juce::File& file);
    void play();
    void stop();
    void pause();
    void setGain(float gain);
    void setPosition(double posInSeconds);
    double getPosition() const;
    double getLength() const;
    void setLooping(bool loop);
    bool isLooping() const;

private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    double lastPosition = 0.0;
    bool shouldLoop = false;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)
};
