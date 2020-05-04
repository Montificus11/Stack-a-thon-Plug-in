/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class StackathonpluginAudioProcessorEditor  : public AudioProcessorEditor
											
												
{
public:
    StackathonpluginAudioProcessorEditor (StackathonpluginAudioProcessor&);
    ~StackathonpluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;




private:
    
    StackathonpluginAudioProcessor& processor;
	//Slider gainSlider;
	

	Slider filterCutoffDial1;
	Slider filterResDial1;
	ComboBox filterMenu1;

	//Slider filterCutoffDial2;
	//Slider filterResDial2;
	//ComboBox filterMenu2;

public: 
	//std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderValue;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterResValue;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuChoice;
	/*
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue2;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterResValue2;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuChoice2;
	*/

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StackathonpluginAudioProcessorEditor)
};
