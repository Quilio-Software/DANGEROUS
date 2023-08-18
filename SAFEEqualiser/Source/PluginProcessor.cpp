/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SafeequaliserAudioProcessor::SafeequaliserAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, &um, "Parameters", createParameterLayout())
#endif
{
    numFilters = 5;
    gains.allocate (numFilters, true);
    freqs.allocate (numFilters, true);
    qFactors.allocate (numFilters, true);
    
    float frequencySkewFactor = 0.25;
    float qSkewFactor = 0.5;
    
        
    fs = 44100;
    
    numChannels = 0;
}

SafeequaliserAudioProcessor::~SafeequaliserAudioProcessor()
{
}

//==============================================================================
const juce::String SafeequaliserAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SafeequaliserAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SafeequaliserAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SafeequaliserAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SafeequaliserAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SafeequaliserAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SafeequaliserAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SafeequaliserAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SafeequaliserAudioProcessor::getProgramName (int index)
{
    return {};
}

void SafeequaliserAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

void SafeequaliserAudioProcessor::updateFilters (int band)
{     
    IIRCoefficients filterCoefficients;
    
    if (band == 0) // Lowest band (low shelf)
	{
		filterCoefficients = IIRCoefficients::makeLowShelf(fs,
                                                           freqs [0],
                                                           qFactors [0],
                                                           gains [0]);
	}
	else if (band == numFilters - 1) // Highest band (high shelf)
	{
		filterCoefficients = IIRCoefficients::makeHighShelf(fs,
                                                            freqs [numFilters - 1],
                                                            qFactors [numFilters - 1],
                                                            gains [numFilters - 1]);
	}
	else // Other bands (peaking filter)
	{
		filterCoefficients = IIRCoefficients::makePeakFilter(fs,
                                                             freqs [band],
                                                             qFactors [band],
                                                             gains [band]);
	}
	
	for (int channel = 0; channel < numChannels; ++channel)
    {
	    eqFilters [band * numChannels + channel]->setCoefficients (filterCoefficients);
    }
}

AudioProcessorValueTreeState::ParameterLayout SafeequaliserAudioProcessor::createParameterLayout ()
{
    float frequencySkewFactor = 1.0f;
    float qSkewFactor = 1.0f;

    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    const float minFreq = 20.0f; // starting frequency
    const float maxFreq = 20000.0f; // ending frequency

    // Calculate the ratio for the geometric progression
    float ratio = powf(maxFreq / minFreq, 1.0f / (numBands - 1));

    for (int i = 0; i < numBands; ++i)
    {
        String bandNumber = String(i + 1);

        params.push_back(std::make_unique<AudioParameterFloat>(
            "Band " + bandNumber + " Gain",                // parameterID
            "Band " + bandNumber + " Gain",                // parameter name
            NormalisableRange<float>(-12.0f, 12.0f),       // range
            0.0f                                           // default value
        ));

        DBG ("Initializing Parameter: Band " + bandNumber + " Gain");

        float defaultFreq = minFreq * powf(ratio, i);
        float nextFreq = (i < numBands - 1) ? minFreq * powf(ratio, i + 1) : maxFreq;

        params.push_back(std::make_unique<AudioParameterFloat>(
            "Band " + bandNumber + " Frequency",                // parameterID
            "Band " + bandNumber + " Frequency",                // parameter name
            NormalisableRange<float>(defaultFreq, nextFreq, 1.0f, frequencySkewFactor),
            defaultFreq
        ));

        params.push_back(std::make_unique<AudioParameterFloat>(
            "Band " + bandNumber + " Q Factor",                 // parameterID
            "Band " + bandNumber + " Q Factor",                 // parameter name
            NormalisableRange<float>(0.1f, 10.0f, 0.1f, qSkewFactor),
            0.71f
        ));
    }

    return { params.begin(), params.end() };
}



//==============================================================================

void SafeequaliserAudioProcessor::releaseResources()
{
}

void SafeequaliserAudioProcessor::prepareToPlay (double sampleRate, int maximumExpectedSamplesPerBlock)
{
    fs = sampleRate;
    numChannels = getNumInputChannels();
    
    eqFilters.clear();
    for (int band = 0; band < numFilters; ++band)
    {
        for (int channel = 0; channel < numChannels; ++channel)
        {
            eqFilters.add (new IIRFilter);
        }
        
//        updateFilters (band);
    }
}

void SafeequaliserAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{    
    int numSamples = buffer.getNumSamples();
    
    for (int channel = 0; channel < numChannels; ++channel)
    {    
        float* channelData = buffer.getWritePointer (channel);
        
        for (int band = 0; band < numFilters; ++band)
        {
            eqFilters [band * numChannels + channel]->processSamples (channelData, numSamples);
        }
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SafeequaliserAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
bool SafeequaliserAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SafeequaliserAudioProcessor::createEditor()
{
    return new SafeequaliserAudioProcessorEditor (*this, apvts);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SafeequaliserAudioProcessor ();
}