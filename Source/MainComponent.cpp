#include "MainComponent.h"

MainComponent::MainComponent() : guiPlayer(audioPlayer) {
    addAndMakeVisible(guiPlayer);
    setSize(650, 300); 
    setAudioChannels(0, 2); 
}

MainComponent::~MainComponent() {
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    audioPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    audioPlayer.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources() {
    audioPlayer.releaseResources();
}

void MainComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::darkgrey); 
} 

void MainComponent::resized() 
{
    guiPlayer.setBounds(getLocalBounds());
}
