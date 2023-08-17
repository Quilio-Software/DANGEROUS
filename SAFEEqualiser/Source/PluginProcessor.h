/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class SafeequaliserAudioProcessor  : public juce::AudioProcessor
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

    AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        float frequencySkewFactor = 1.0f;
        float qSkewFactor = 1.0f;


        std::vector<std::unique_ptr<RangedAudioParameter>> params;

        for (int i = 0; i < 5; ++i)
        {
            String bandNumber = String(i + 1);

            params.push_back(std::make_unique<AudioParameterFloat>(
                "Band " + bandNumber + " Gain",                // parameterID
                "Band " + bandNumber + " Gain",                // parameter name
                NormalisableRange<float>(-12.0f, 12.0f),       // range
                0.0f                                           // default value
            ));

            DBG ("Initializing Parameter: Band " + bandNumber + " Gain");

            float defaultFreq = (i == 0) ? 150.0f : (i == 1) ? 560.0f : (i == 2) ? 1000.0f : (i == 3) ? 3300.0f : 8200.0f;
            float minFreq = (i == 0) ? 22.0f : (i == 1) ? 82.0f : (i == 2) ? 180.0f : (i == 3) ? 220.0f : 580.0f;
            float maxFreq = (i == 0) ? 1000.0f : (i == 1) ? 3900.0f : (i == 2) ? 4700.0f : (i == 3) ? 10000.0f : 20000.0f;

            params.push_back(std::make_unique<AudioParameterFloat>(
                "Band " + bandNumber + " Frequency",            // parameterID
                "Band " + bandNumber + " Frequency",            // parameter name
                NormalisableRange<float>(minFreq, maxFreq, 1.0f, frequencySkewFactor),
                defaultFreq
            ));

            if (i == 1 || i == 2 || i == 3)
            {
                params.push_back(std::make_unique<AudioParameterFloat>(
                    "Band " + bandNumber + " Q Factor",         // parameterID
                    "Band " + bandNumber + " Q Factor",         // parameter name
                    NormalisableRange<float>(0.1f, 10.0f, 0.1f, qSkewFactor),
                    0.71f
                ));
            }
        }

        return { params.begin(), params.end() };
    }


    AudioProcessorValueTreeState apvts;
    UndoManager um;
    
private:
    int numFilters;
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
