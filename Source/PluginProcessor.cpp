/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StackathonpluginAudioProcessor::StackathonpluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
	 ), tree(*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
	//NormalisableRange<float> gainRange(-48.0f, 0.0f);

	//NormalisableRange<float> cutoffRange(20.0f, 20000.0f);
	//NormalisableRange<float> resRange(1.0f, 5.0f);
	//NormalisableRange<float> filterMenuRange(0, 2);


	//tree.createAndAddParameter("cutoff", "Cutoff", "cutoff", cutoffRange, 600.0f, nullptr, nullptr);
	//tree.createAndAddParameter("resonance", "Resonance", "resonance", resRange, 1.0f, nullptr, nullptr);

	//tree.createAndAddParameter("filterMenu", "FilterMenu", "filterMenu", filterMenuRange, 0, nullptr, nullptr);
}

StackathonpluginAudioProcessor::~StackathonpluginAudioProcessor()
{
}

//==============================================================================

AudioProcessorValueTreeState::ParameterLayout StackathonpluginAudioProcessor::createParameterLayout()
{

	std::vector <std::unique_ptr<RangedAudioParameter>> params;

	auto cutOffParam = std::make_unique<AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 1000.0f);
	auto resonanceParam = std::make_unique<AudioParameterFloat>("resonance", "Resonance", 1.0f, 5.0f, 1.0f);
	auto filterParam = std::make_unique<AudioParameterFloat>("filterMenu", "FilterMenu", 0, 2, 0);

	params.push_back(std::move(cutOffParam));
	params.push_back(std::move(resonanceParam));
	params.push_back(std::move(filterParam));

	return { params.begin(), params.end() };

}
/*
//from the attempted second filter:

std::make_unique<AudioParameterFloat>("cutoff2","Cutoff2",1000.0f,7500.0f,3500.0f), std::make_unique<AudioParameterFloat>("resonance2", "Resonance2", 1.0f, 5.0f, 1.0f), std::make_unique<AudioParameterFloat>("filterMenu2", "FilterMenu2", 0,2,0

}
*/



const String StackathonpluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StackathonpluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StackathonpluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StackathonpluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StackathonpluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StackathonpluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StackathonpluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StackathonpluginAudioProcessor::setCurrentProgram (int index)
{
}

const String StackathonpluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void StackathonpluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StackathonpluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	//Preparing to play when the audio is stopped... Clears everything out
	lastSampleRate = sampleRate;

	
	dsp::ProcessSpec spec;
	spec.sampleRate = lastSampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getMainBusNumOutputChannels();

	stateVariableFilter.reset();
	//stateVariableFilter2.reset();
	updateFilter();
	stateVariableFilter.prepare(spec);
	//stateVariableFilter2.prepare(spec);

	
}

void StackathonpluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}
void StackathonpluginAudioProcessor::updateFilter()
{

	
	int menuChoice = *tree.getRawParameterValue("filterMenu");
	int cutoff = *tree.getRawParameterValue("cutoff");
	int res = *tree.getRawParameterValue("resonance");

	/*
	int menuChoice2 = *tree.getRawParameterValue("filterMenu2");
	int cutoff2 = *tree.getRawParameterValue("cutoff2");
	int res2 = *tree.getRawParameterValue("resonance2");

	*/

	if (menuChoice == 0)
	{
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;

		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff, res);
	}
	if (menuChoice == 1)
	{
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;

		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff, res);
	}
	if (menuChoice == 2)
	{
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;

		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff, res);
	}


	/*
	if (menuChoice2 == 0)
	{
		stateVariableFilter2.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;

		stateVariableFilter2.state->setCutOffFrequency(lastSampleRate, cutoff2, res2);
	}
	if (menuChoice2 == 1)
	{
		stateVariableFilter2.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;

		stateVariableFilter2.state->setCutOffFrequency(lastSampleRate, cutoff2, res2);
	}
	if (menuChoice2 == 2)
	{
		stateVariableFilter2.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;

		stateVariableFilter2.state->setCutOffFrequency(lastSampleRate, cutoff2, res2);
	}
	*/
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StackathonpluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void StackathonpluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	//where the audio gets called, don't do memory allocation here 
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


	//Clearing if there are more output channels than input channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


	dsp::AudioBlock<float> block(buffer);

	updateFilter();

	stateVariableFilter.process(dsp::ProcessContextReplacing<float> (block));

	int menuChoice = *tree.getRawParameterValue("filterMenu");

	std::cout << "Filter Choice:" << menuChoice << std::endl;
	
	//stateVariableFilter2.process(dsp::ProcessContextReplacing<float>(block));
    
	//const auto readPointer = buffer.getReadPointer (channel)  helps re-paint the meters if you're using them



	/*
	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto channelData = buffer.getWritePointer(channel);
		auto sliderGainValue = tree.getRawParameterValue(GAIN_ID);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			channelData [sample] = buffer.getSample(channel, sample) * Decibels::decibelsToGain(*sliderGainValue);
		}
	}
	*/
}

//==============================================================================
bool StackathonpluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StackathonpluginAudioProcessor::createEditor()
{
    return new StackathonpluginAudioProcessorEditor (*this);
}
 
//==============================================================================
void StackathonpluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StackathonpluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StackathonpluginAudioProcessor();
}
