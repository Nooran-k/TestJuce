#include "PlayerAudio.h"
#include "PlayerGUI.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio()
{
    releaseResources();
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
    readerSource.reset();
}

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (file.existsAsFile())
    {
        if (auto* reader = formatManager.createReaderFor(file))
        {
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();
            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            if (readerSource)
            {
                transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
                return true;
            }
        }
    }
    return false;
}

void PlayerAudio::play()
{
    transportSource.start();
}

void PlayerAudio::stop()
{
    transportSource.stop();
    transportSource.setPosition(0.0);
}
void PlayerAudio::pause()
{
    lastPosition = transportSource.getCurrentPosition();
    transportSource.stop();
}
void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}

double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}

void PlayerAudio::setPosition(double posInSeconds)
{
    transportSource.setPosition(posInSeconds);
}

double PlayerAudio::getLength() const
{
    auto length = transportSource.getLengthInSeconds();
    return length > 0.0 ? length : 0.0;
}

void PlayerAudio::setLooping(bool loop)
{
    shouldLoop = loop;
    transportSource.setLooping(loop);
    transportSource.setLooping(shouldLoop);

}

bool PlayerAudio::isLooping() const
{
    return shouldLoop;
}
