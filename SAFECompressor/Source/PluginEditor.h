/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class SafecompressorAudioProcessorEditor  : public SAFEAudioProcessorEditor
{
public:
    SafecompressorAudioProcessorEditor (SafecompressorAudioProcessor* ownerFilter);
    ~SafecompressorAudioProcessorEditor();

    //==============================================================================
    // This is just a standard Juce paint method...
    void paint (Graphics& g);    
    
    void sliderUpdate (Slider* slider);
    
    void updateDisplay();
    
    void updateUI();
    
    void updateMeters();
    
private:
    Image backgroundImage;
    
    DynamicProcessorGraph display;
    
    LevelMeter meter;
    Array <float> meterInputs;
    
    SafecompressorAudioProcessor* getProcessor()
    {
        return static_cast <SafecompressorAudioProcessor*> (getAudioProcessor());
    }
};

#endif  // PLUGINEDITOR_H_INCLUDED
