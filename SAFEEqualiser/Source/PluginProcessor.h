/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "QuilioEQ.h"


//==============================================================================
/**
*/
class SafeequaliserAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    SafeequaliserAudioProcessor();
    ~SafeequaliserAudioProcessor() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
   #endif
    
    //==============================================================================
    void updateFilters (int band);

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override {}
    void setStateInformation(const void* data, int sizeInBytes) override {}

    int numFilters = 5;

    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void parameterChanged (const String& parameterID, float newValue) override;


    AudioProcessorValueTreeState apvts;
    UndoManager um;
    
private:
    double fs;
    
    HeapBlock <float> gains;
    HeapBlock <float> freqs;
    HeapBlock <float> qFactors;
    
    int numChannels;
    
    OwnedArray <IIRFilter> eqFilters;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SafeequaliserAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
