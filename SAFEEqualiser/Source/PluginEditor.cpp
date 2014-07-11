/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#ifndef IMAGE_DIRECTORY
#define IMAGE_DIRECTORY File::getSpecialLocation (File::currentExecutableFile)
#endif

//==============================================================================
SafeequaliserAudioProcessorEditor::SafeequaliserAudioProcessorEditor (SafeequaliserAudioProcessor* ownerFilter)
    : SAFEAudioProcessorEditor (ownerFilter),
      display (5)
{
    setSize (810, 600);
    
    File imageDirectory (IMAGE_DIRECTORY);

//    File backgroundFile = imageDirectory.getChildFile ("Images/EQ_background2.png");
//    backgroundImage = ImageCache::getFromFile (backgroundFile);
    backgroundImage = ImageCache::getFromMemory(SAFEImages::eq_background_png, SAFEImages::eq_background_pngSize);

    
    int filterGraphVerticalOffset = 201;
    int col1X = 30;
    int col2X = 140;
    int col3X = 250;
    int col4X = 360;
    int col5X = 470;
    
    int row1Y = 80 + filterGraphVerticalOffset;
    int row2Y = 182 + filterGraphVerticalOffset;
    int row3Y = 285 + filterGraphVerticalOffset;

    
    addAndMakeVisible (&recordButton);
    recordButton.setBounds (580, 358 + filterGraphVerticalOffset, 100, 22);
    
    addAndMakeVisible (&loadButton);
    loadButton.setBounds (690, 358 + filterGraphVerticalOffset, 100, 22);
    
    addAndMakeVisible (&descriptorBox);
    descriptorBox.setBounds (580, 254 + filterGraphVerticalOffset, 210, 94);
    
    addAndMakeVisible (&metaDataButton);
    metaDataButton.setBounds (721, 214 + filterGraphVerticalOffset, 30, 30);
    
    addAndMakeVisible (&infoButton);
    infoButton.setBounds (680, 214 + filterGraphVerticalOffset,	 30, 30);
    
    addAndMakeVisible (&fileAccessButton);
    fileAccessButton.setBounds (760, 214 + filterGraphVerticalOffset, 30, 30);
    
    setExtraScreenPosition (210, 251);
    
    // first band
    SAFESlider* gain0Slider = sliders [SafeequaliserAudioProcessor::PARAMgain0];
    addAndMakeVisible (gain0Slider);
    gain0Slider->setBounds (col1X, row1Y, 80, 100);
    gain0Slider->setColour (SAFEColours::green);
    gain0Slider->setText ("G");
    
    SAFESlider* freq0Slider = sliders [SafeequaliserAudioProcessor::PARAMfreq0];
    addAndMakeVisible (freq0Slider);
    freq0Slider->setBounds (col1X, row2Y, 80, 100);
    freq0Slider->setColour (SAFEColours::yellow);
    freq0Slider->setText ("F");
    
    // second band
    SAFESlider* gain1Slider = sliders [SafeequaliserAudioProcessor::PARAMgain1];
    addAndMakeVisible (gain1Slider);
    gain1Slider->setBounds (col2X, row1Y, 80, 100);
    gain1Slider->setColour (SAFEColours::green);
    gain1Slider->setText ("G");
    
    SAFESlider* freq1Slider = sliders [SafeequaliserAudioProcessor::PARAMfreq1];
    addAndMakeVisible (freq1Slider);
    freq1Slider->setBounds (col2X, row2Y, 80, 100);
    freq1Slider->setColour (SAFEColours::yellow);
    freq1Slider->setText ("F");
    
    SAFESlider* qFactor1Slider = sliders [SafeequaliserAudioProcessor::PARAMqFactor1];
    addAndMakeVisible (qFactor1Slider);
    qFactor1Slider->setBounds (col2X, row3Y, 80, 100);
    qFactor1Slider->setColour (SAFEColours::red);
    qFactor1Slider->setText ("Q");
    
    // third band
    SAFESlider* gain2Slider = sliders [SafeequaliserAudioProcessor::PARAMgain2];
    addAndMakeVisible (gain2Slider);
    gain2Slider->setBounds (col3X, row1Y, 80, 100);
    gain2Slider->setColour (SAFEColours::green);
    gain2Slider->setText ("G");
    
    SAFESlider* freq2Slider = sliders [SafeequaliserAudioProcessor::PARAMfreq2];
    addAndMakeVisible (freq2Slider);
    freq2Slider->setBounds (col3X, row2Y, 80, 100);
    freq2Slider->setColour (SAFEColours::yellow);
    freq2Slider->setText ("F");
    
    SAFESlider* qFactor2Slider = sliders [SafeequaliserAudioProcessor::PARAMqFactor2];
    addAndMakeVisible (qFactor2Slider);
    qFactor2Slider->setBounds (col3X, row3Y, 80, 100);
    qFactor2Slider->setColour (SAFEColours::red);
    qFactor2Slider->setText ("Q");

    // fourth band
    SAFESlider* gain3Slider = sliders [SafeequaliserAudioProcessor::PARAMgain3];
    addAndMakeVisible (gain3Slider);
    gain3Slider->setBounds (col4X, row1Y, 80, 100);
    gain3Slider->setColour (SAFEColours::green);
    gain3Slider->setText ("G");
    
    SAFESlider* freq3Slider = sliders [SafeequaliserAudioProcessor::PARAMfreq3];
    addAndMakeVisible (freq3Slider);
    freq3Slider->setBounds (col4X, row2Y, 80, 100);
    freq3Slider->setColour (SAFEColours::yellow);
    freq3Slider->setText ("F");
    
    SAFESlider* qFactor3Slider = sliders [SafeequaliserAudioProcessor::PARAMqFactor3];
    addAndMakeVisible (qFactor3Slider);
    qFactor3Slider->setBounds (col4X, row3Y, 80, 100);
    qFactor3Slider->setColour (SAFEColours::red);
    qFactor3Slider->setText ("Q");
    
    // fifth band
    SAFESlider* gain4Slider = sliders [SafeequaliserAudioProcessor::PARAMgain4];
    addAndMakeVisible (gain4Slider);
    gain4Slider->setBounds (col5X, row1Y, 80, 100);
    gain4Slider->setColour (SAFEColours::green);
    gain4Slider->setText ("G");
    
    SAFESlider* freq4Slider = sliders [SafeequaliserAudioProcessor::PARAMfreq4];
    addAndMakeVisible (freq4Slider);
    freq4Slider->setBounds (col5X, row2Y, 80, 100);
    freq4Slider->setColour (SAFEColours::yellow);
    freq4Slider->setText ("F");
    
    // frequncy display
    addAndMakeVisible (&display);
    display.setBounds (20, 20, 770, 180);
    display.setMaxDecibels (20);
    display.addListener (this);
    
    display.setControlColour (0, Colours::red);
    display.setControlColour (1, Colours::green);
    display.setControlColour (2, Colours::yellow);
    display.setControlColour (3, Colours::blue);
    display.setControlColour (4, Colours::skyblue);
    
    display.setControlLimits (0, 22, 1000, -12, 12);
    display.setControlLimits (1, 82, 3900, -12, 12);
    display.setControlLimits (2, 180, 4700, -12, 12);
    display.setControlLimits (3, 220, 10000, -12, 12);
    display.setControlLimits (4, 580, 20000, -12, 12);
    
    display.setControlQLimits (0, 0.1, 10, 0.5);
    display.setControlQLimits (1, 0.1, 10, 0.5);
    display.setControlQLimits (2, 0.1, 10, 0.5);
    display.setControlQLimits (3, 0.1, 10, 0.5);
    display.setControlQLimits (4, 0.1, 10, 0.5);
    
    display.setControlParameters (0, 150, 0, 0.71);
    display.setControlParameters (1, 560, 0, 0.71);
    display.setControlParameters (2, 1000, 0, 0.71);
    display.setControlParameters (3, 3300, 0, 0.71);
    display.setControlParameters (4, 8200, 0, 0.71);
}

SafeequaliserAudioProcessorEditor::~SafeequaliserAudioProcessorEditor()
{
}

//==============================================================================
void SafeequaliserAudioProcessorEditor::paint (Graphics& g)
{
    int width = getWidth();
    int height = getHeight();
    int imageWidth = backgroundImage.getWidth();
    int imageHeight = backgroundImage.getHeight();
    
    g.drawImage (backgroundImage, 0, 0, width, height, 0, 0, imageWidth, imageHeight);
}

void SafeequaliserAudioProcessorEditor::sliderUpdate (Slider* slider)
{
    if (slider == sliders [SafeequaliserAudioProcessor::PARAMgain0]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMfreq0]->getSliderPointer())
    {
        double fc = sliders [SafeequaliserAudioProcessor::PARAMfreq0]->getValue();
        double gain = sliders [SafeequaliserAudioProcessor::PARAMgain0]->getValue();
        display.setFilter (0, 44100, IIRCoefficients::makeLowShelf (44100, fc, 0.71, Decibels::decibelsToGain (gain)));
        display.setControlParameters (0, fc, gain, 1);
    }
    
    if (slider == sliders [SafeequaliserAudioProcessor::PARAMgain1]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMfreq1]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMqFactor1]->getSliderPointer())
    {
        double fc = sliders [SafeequaliserAudioProcessor::PARAMfreq1]->getValue();
        double gain = sliders [SafeequaliserAudioProcessor::PARAMgain1]->getValue();
        double q = sliders [SafeequaliserAudioProcessor::PARAMqFactor1]->getValue();
        display.setFilter (1, 44100, IIRCoefficients::makePeakFilter (44100, fc, q, Decibels::decibelsToGain (gain)));
        display.setControlParameters (1, fc, gain, q);
    }
    
    if (slider == sliders [SafeequaliserAudioProcessor::PARAMgain2]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMfreq2]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMqFactor2]->getSliderPointer())
    {
        double fc = sliders [SafeequaliserAudioProcessor::PARAMfreq2]->getValue();
        double gain = sliders [SafeequaliserAudioProcessor::PARAMgain2]->getValue();
        double q = sliders [SafeequaliserAudioProcessor::PARAMqFactor2]->getValue();
        display.setFilter (2, 44100, IIRCoefficients::makePeakFilter (44100, fc, q, Decibels::decibelsToGain (gain)));
        display.setControlParameters (2, fc, gain, q);
    }
    
    if (slider == sliders [SafeequaliserAudioProcessor::PARAMgain3]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMfreq3]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMqFactor3]->getSliderPointer())
    {
        double fc = sliders [SafeequaliserAudioProcessor::PARAMfreq3]->getValue();
        double gain = sliders [SafeequaliserAudioProcessor::PARAMgain3]->getValue();
        double q = sliders [SafeequaliserAudioProcessor::PARAMqFactor3]->getValue();
        display.setFilter (3, 44100, IIRCoefficients::makePeakFilter (44100, fc, q, Decibels::decibelsToGain (gain)));
        display.setControlParameters (3, fc, gain, q);
    }
    
    if (slider == sliders [SafeequaliserAudioProcessor::PARAMgain4]->getSliderPointer() || slider == sliders [SafeequaliserAudioProcessor::PARAMfreq4]->getSliderPointer())
    {
        double fc = sliders [SafeequaliserAudioProcessor::PARAMfreq4]->getValue();
        double gain = sliders [SafeequaliserAudioProcessor::PARAMgain4]->getValue();
        display.setFilter (4, 44100, IIRCoefficients::makeHighShelf (44100, fc, 0.71, Decibels::decibelsToGain (gain)));
        display.setControlParameters (4, fc, gain, 1);
    }
}

void SafeequaliserAudioProcessorEditor::filterControlChanged (int controlNum)
{
    SafeequaliserAudioProcessor* ourProcessor = getProcessor();
    float freq, gain, qFactor;
    
    switch (controlNum)
    {
        case 0:
            freq = display.getControlFrequency (0);
            gain = display.getControlGain (0);
            ourProcessor->setScaledParameterNotifyingHost (1, freq);
            ourProcessor->setScaledParameterNotifyingHost  (0, gain);
            display.setFilter (0, 44100, IIRCoefficients::makeLowShelf (44100, freq, 0.71, Decibels::decibelsToGain (gain)));
            sliders [0]->setValue (gain, dontSendNotification);
            sliders [1]->setValue (freq, dontSendNotification);
            break;  
            
        case 1:
            freq = display.getControlFrequency (1);
            gain = display.getControlGain (1);
            qFactor = display.getControlQ (1);
            ourProcessor->setScaledParameterNotifyingHost  (3, freq);
            ourProcessor->setScaledParameterNotifyingHost  (2, gain);
            ourProcessor->setScaledParameterNotifyingHost  (4, qFactor);
            display.setFilter (1, 44100, IIRCoefficients::makePeakFilter (44100, freq, qFactor, Decibels::decibelsToGain (gain)));
            sliders [2]->setValue (gain, dontSendNotification);
            sliders [3]->setValue (freq, dontSendNotification);
            sliders [4]->setValue (qFactor, dontSendNotification);
            break; 
            
        case 2:
            freq = display.getControlFrequency (2);
            gain = display.getControlGain (2);
            qFactor = display.getControlQ (2);
            ourProcessor->setScaledParameterNotifyingHost  (6, freq);
            ourProcessor->setScaledParameterNotifyingHost  (5, gain);
            ourProcessor->setScaledParameterNotifyingHost  (7, qFactor);
            display.setFilter (2, 44100, IIRCoefficients::makePeakFilter (44100, freq, qFactor, Decibels::decibelsToGain (gain)));
            sliders [5]->setValue (gain, dontSendNotification);
            sliders [6]->setValue (freq, dontSendNotification);
            sliders [7]->setValue (qFactor, dontSendNotification);
            break; 
            
        case 3:
            freq = display.getControlFrequency (3);
            gain = display.getControlGain (3);
            qFactor = display.getControlQ (3);
            ourProcessor->setScaledParameterNotifyingHost  (9, freq);
            ourProcessor->setScaledParameterNotifyingHost  (8, gain);
            ourProcessor->setScaledParameterNotifyingHost  (10, qFactor);
            display.setFilter (3, 44100, IIRCoefficients::makePeakFilter (44100, freq, qFactor, Decibels::decibelsToGain (gain)));
            sliders [8]->setValue (gain, dontSendNotification);
            sliders [9]->setValue (freq, dontSendNotification);
            sliders [10]->setValue (qFactor, dontSendNotification);
            break; 
            
        case 4:
            freq = display.getControlFrequency (4);
            gain = display.getControlGain (4);
            ourProcessor->setScaledParameterNotifyingHost (12, freq);
            ourProcessor->setScaledParameterNotifyingHost  (11, gain);
            display.setFilter (4, 44100, IIRCoefficients::makeHighShelf (44100, freq, 0.71, Decibels::decibelsToGain (gain)));
            sliders [11]->setValue (gain, dontSendNotification);
            sliders [12]->setValue (freq, dontSendNotification);
            break; 
    }
}

void SafeequaliserAudioProcessorEditor::updateUI()
{
    SafeequaliserAudioProcessor* ourProcessor = getProcessor();
    float freq, gain, qFactor;
    
    gain = ourProcessor->getScaledParameter (0);
    freq = ourProcessor->getScaledParameter (1);
    display.setFilter (0, 44100, IIRCoefficients::makeLowShelf (44100, freq, 0.71, Decibels::decibelsToGain (gain)));
    display.setControlParameters (0, freq, gain, 1);
    
    gain = ourProcessor->getScaledParameter (2);
    freq = ourProcessor->getScaledParameter (3);
    qFactor = ourProcessor->getScaledParameter (4);
    display.setFilter (1, 44100, IIRCoefficients::makePeakFilter (44100, freq, qFactor, Decibels::decibelsToGain (gain)));
    display.setControlParameters (1, freq, gain, qFactor);
    
    gain = ourProcessor->getScaledParameter (5);
    freq = ourProcessor->getScaledParameter (6);
    qFactor = ourProcessor->getScaledParameter (7);
    display.setFilter (2, 44100, IIRCoefficients::makePeakFilter (44100, freq, qFactor, Decibels::decibelsToGain (gain)));
    display.setControlParameters (2, freq, gain, qFactor);
    
    gain = ourProcessor->getScaledParameter (8);
    freq = ourProcessor->getScaledParameter (9);
    qFactor = ourProcessor->getScaledParameter (10);
    display.setFilter (3, 44100, IIRCoefficients::makePeakFilter (44100, freq, qFactor, Decibels::decibelsToGain (gain)));
    display.setControlParameters (3, freq, gain, qFactor);
    
    gain = ourProcessor->getScaledParameter (11);
    freq = ourProcessor->getScaledParameter (12);
    display.setFilter (4, 44100, IIRCoefficients::makeHighShelf (44100, freq, 0.71, Decibels::decibelsToGain (gain)));
    display.setControlParameters (4, freq, gain, 1);
    
    if (sliders [0]->isMouseOverOrDraggingSlider() || sliders [1]->isMouseOverOrDraggingSlider())
    {
        display.paintSingleFilter (0);
    }
    else if (sliders [2]->isMouseOverOrDraggingSlider() || sliders [3]->isMouseOverOrDraggingSlider() || sliders [4]->isMouseOverOrDraggingSlider())
    {
        display.paintSingleFilter (1);
    }
    else if (sliders [5]->isMouseOverOrDraggingSlider() || sliders [6]->isMouseOverOrDraggingSlider() || sliders [7]->isMouseOverOrDraggingSlider())
    {
        display.paintSingleFilter (2);
    }
    else if (sliders [8]->isMouseOverOrDraggingSlider() || sliders [9]->isMouseOverOrDraggingSlider() || sliders [10]->isMouseOverOrDraggingSlider())
    {
        display.paintSingleFilter (3);
    }
    else if (sliders [11]->isMouseOverOrDraggingSlider() || sliders [12]->isMouseOverOrDraggingSlider())
    {
        display.paintSingleFilter (4);
    }
    else
    {
        display.hideSingleFilter();
    }
}
