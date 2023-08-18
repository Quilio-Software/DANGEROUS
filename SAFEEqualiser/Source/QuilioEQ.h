/*
  ==============================================================================

    QuilioEQ.h
    Created: 17 Aug 2023 10:53:16am
    Author:  abhis

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


enum FilterType
{
    LOW_SHELF = 0,
    PEAK = 1,
    HIGH_SHELF = 2
};

class EQPoint
{
public:
    
    EQPoint (float newGain, float newFreq, float newQFactor, FilterType newFilterType)
    {
        gain = newGain;
        freq = newFreq;
        qFactor = newQFactor;
        filterType = newFilterType;
    }
    
    float gain;
    float freq;
    float qFactor;
    FilterType filterType;
};

class QuilioEqualizer
{
public:

    int numFilters;
    double fs;
    
    std::vector<EQPoint> eqPoints;
    

    int numChannels = 2;
    int numSamples;

    std::vector <std::unique_ptr<IIRFilter>> eqFilters;
    
    enum CasperakiPreset
    {
        LEAD, BACKING
    };

    QuilioEqualizer ()
    {
        numFilters = 4;
        
//        eqPoints.setSize (numFilters);
        
        eqPoints.clear();
        eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (-10.83), 202.0f, 2.232f, FilterType::LOW_SHELF));
        eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (5.50), 6666.0f, 2.497f, FilterType::PEAK));
        eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (-7.67), 10078.0f, 2.490f, FilterType::PEAK));
        eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (0.0f), 17035.0f, 0.5f, FilterType::HIGH_SHELF));
    }
    
    void setType (CasperakiPreset preset)
    {
        eqPoints.clear();
        if (preset == LEAD)
        {
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (-10.83), 202.0f, 2.232f, FilterType::LOW_SHELF));
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (5.50), 6666.0f, 2.497f, FilterType::PEAK));
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (-7.67), 10078.0f, 2.490f, FilterType::PEAK));
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (0.0f), 17035.0f, 0.5f, FilterType::HIGH_SHELF));
        }
        else if (preset == BACKING)
        {
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (-10.83), 202.0f, 2.232f, FilterType::LOW_SHELF));
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (5.50), 6666.0f, 2.497f, FilterType::PEAK));
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (-7.67), 10078.0f, 2.490f, FilterType::PEAK));
            eqPoints.push_back (EQPoint (juce::Decibels::decibelsToGain (0.0f), 17035.0f, 0.5f, FilterType::HIGH_SHELF));
        }
    }


    void prepare (double sampleRate, int samplesPerBlock) //set number of channels here
    {
        fs = sampleRate;
        eqFilters.clear();
        for (int band = 0; band < numFilters; band++)
        {
            for (int channel = 0; channel < numChannels; channel++)
            {
                eqFilters.push_back (std::make_unique<IIRFilter>());
            }
            updateFilters (band);
        }
    }

    void processBufferReplacing (AudioSampleBuffer& buffer)
    {
        numSamples = buffer.getNumSamples();
        for (int channel = 0; channel < numChannels; channel++)
        {
            float* channelData = buffer.getWritePointer(channel);
            for (int band = 0; band < numFilters; band++)
            {
                eqFilters[band * numChannels + channel]->processSamples (channelData, numSamples);
            }
        }
    }

    void updateLowAndHighFrequencies (float val1, float val2)
    {
        eqPoints[0].gain = val1;
        eqPoints[eqPoints.size() - 1].gain = val2;


        int i = eqPoints.size() - 1;
        while (i > 0)
        {
            updateFilters (i);
            i--;
        }
    }
    
    
    IIRCoefficients makeFilter (double sampleRate, EQPoint eqPoint)
    {
        FilterType filterType = eqPoint.filterType;
        if (filterType == FilterType::LOW_SHELF)
            return IIRCoefficients::makeLowShelf (fs, eqPoint.freq, eqPoint.qFactor, eqPoint.gain);
        else if (filterType == FilterType::PEAK)
            return IIRCoefficients::makePeakFilter (fs, eqPoint.freq, eqPoint.qFactor, eqPoint.gain);
        else if (filterType == FilterType::HIGH_SHELF)
            return IIRCoefficients::makeHighShelf (fs, eqPoint.freq, eqPoint.qFactor, eqPoint.gain);
    }

    void updateFilters (int band)
    {
        IIRCoefficients filterCoefficients;

        if (band == 0) // Lowest band (low shelf)
        {
            filterCoefficients = makeFilter (fs, eqPoints[0]);
        }
        else if (band == numFilters - 1) // Highest band (high shelf)
        {
            filterCoefficients = makeFilter (fs, eqPoints[numFilters - 1]);
        }
        else // Other bands (peaking filter)
        {
            filterCoefficients = makeFilter (fs, eqPoints[band]);
        }

        for (int channel = 0; channel < numChannels; channel++)
        {
            eqFilters[band * numChannels + channel]->setCoefficients(filterCoefficients);
        }
    }
};

