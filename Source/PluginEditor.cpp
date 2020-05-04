/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StackathonpluginAudioProcessorEditor::StackathonpluginAudioProcessorEditor (StackathonpluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	/*
	sliderValue = std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "gain", gainSlider);

	gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	gainSlider.setRange(-48.0f, 0.0f);
	gainSlider.setValue(-15.0f);
	addAndMakeVisible(&gainSlider);
	*/
	
	
	filterMenu1.setJustificationType(Justification::centred);
	filterMenu1.addItem("Low Pass", 1);
	filterMenu1.addItem("Band Pass", 2);
	filterMenu1.addItem("High Pass", 3);
	addAndMakeVisible(&filterMenu1);

	filterCutoffDial1.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	filterCutoffDial1.setRange(20.0f, 20000.0f);
	filterCutoffDial1.setValue(1000.0f);
	filterCutoffDial1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterCutoffDial1.setPopupDisplayEnabled(true, true, this);
	addAndMakeVisible(&filterCutoffDial1);

	filterResDial1.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	filterResDial1.setRange(1.0f, 5.0f);
	filterResDial1.setValue(2.0f);
	filterResDial1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterResDial1.setPopupDisplayEnabled(true, true, this);
	addAndMakeVisible(&filterResDial1);


	/*
	//filterMenu2.setJustificationType(Justification::centredRight);
	filterMenu2.addItem("Low Pass", 1);
	filterMenu2.addItem("Band Pass", 2);
	filterMenu2.addItem("High Pass", 3);
	addAndMakeVisible(&filterMenu2);

	filterCutoffDial2.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	filterCutoffDial2.setRange(1000.0f, 7000.0f);
	filterCutoffDial2.setValue(3500.0f);
	filterCutoffDial2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterCutoffDial2.setPopupDisplayEnabled(true, true, this);
	addAndMakeVisible(&filterCutoffDial2);

	filterResDial2.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	filterResDial2.setRange(1.0f, 5.0f);
	filterResDial2.setValue(2.0f);
	filterResDial2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterResDial2.setPopupDisplayEnabled(true, true, this);
	addAndMakeVisible(&filterResDial2);

	*/

	filterCutoffValue = std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "cutoff", filterCutoffDial1);
	filterResValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "resonance", filterResDial1);

	filterMenuChoice = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, "FilterMenu", filterMenu1);

	/*

	filterCutoffValue2 = std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "cutoff2", filterCutoffDial2);
	filterResValue2 = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "resonance2", filterResDial2);

	filterMenuChoice2 = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, "FilterMenu2", filterMenu2);

	*/

	filterCutoffDial1.setSkewFactorFromMidPoint(500.0f);
	
	
	/*
	eqDial1.setSliderStyle(Slider::SliderStyle::Rotary);
	eqDial1.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	eqDial1.setRange(20.0f, 500.0f, 1.0f);
	eqDial1.setValue(250.0f);
	eqDial1.addListener(this);
	addAndMakeVisible(eqDial1);

	eqDial2.setSliderStyle(Slider::SliderStyle::Rotary);
	eqDial2.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	eqDial2.setRange(500.0f, 3500.0f, 1.0f);
	eqDial2.setValue(2000.0f);
	eqDial2.addListener(this);
	addAndMakeVisible(eqDial2);

	eqDial3.setSliderStyle(Slider::SliderStyle::Rotary);
	eqDial3.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	eqDial3.setRange(3500.0f, 10000.0f, 1.0f);
	eqDial3.setValue(6750.0f);
	eqDial3.addListener(this);
	addAndMakeVisible(eqDial3);

	*/

    setSize (200, 200);
}

StackathonpluginAudioProcessorEditor::~StackathonpluginAudioProcessorEditor()
{
}

//==============================================================================
void StackathonpluginAudioProcessorEditor::paint (Graphics& g)
{

	Rectangle<int> titleArea(0, 10, getWidth(), 20);
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	
	g.drawText("Filter", titleArea, Justification::centredTop);
	g.drawText("Cutoff", 46, 70, 50, 25, Justification::centredLeft);
	g.drawText("Resonance", 107,70,70,25, Justification::centredLeft);
	
	Rectangle <float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void StackathonpluginAudioProcessorEditor::resized()
{
	//gainSlider.setBounds(10, getHeight() /2 - 20, 100, 150);

	
	Rectangle<int> area = getLocalBounds().reduced(40);

	filterMenu1.setBounds(area.removeFromTop(20));
	filterCutoffDial1.setBounds(30, 90, 70, 70);
	filterResDial1.setBounds(100, 90, 70, 70);


	/*
	filterMenu2.setBounds(350, 100, 150, 100);
	filterCutoffDial2.setBounds(350, 90, 70, 70);
	filterResDial2.setBounds(420, 90, 70, 70);
	*/

	/*
	eqDial1.setBounds(200, getHeight() / 2, 100, 150);
	eqDial2.setBounds(350, getHeight() / 2, 100, 150);
	eqDial3.setBounds(500, getHeight() / 2, 100, 150);
	*/

}
/*
void StackathonpluginAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
	if (slider == &gainSlider)
	{
		processor.mGain = gainSlider.getValue();
	}
}
*/