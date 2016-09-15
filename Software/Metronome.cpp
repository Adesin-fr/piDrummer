/*
 * Metronome.cpp
 *
 *  Created on: 8 août 2016
 *      Author: ulle0009
 */

#include "Metronome.h"

Metronome::Metronome() {
	m_MetronomeBCount=4;
	m_MetronomeBPM=120;
	m_MetronomeVolume=16;
	m_MetronomeOn=false;
	m_LastTimeclick=0;
	m_ClickCount=0;
	m_floatVolume=((float)m_MetronomeVolume/32);

	std::string loSmp=myglobalSettings.getUserDirectory() + "/.piDrummer/res/metronomeLo.wav";
	std::string HiSmp=myglobalSettings.getUserDirectory() + "/.piDrummer/res/metronomeHi.wav";

	// Load Samples :
	m_LoSample.load(loSmp.c_str());
	m_HiSample.load(HiSmp.c_str());

	if (m_LoSample.mSampleCount==0 || m_HiSample.mSampleCount==0){
		std::cerr << "Error loading metronome Samples !" << std::endl;
	}

}

Metronome::~Metronome() {

}

void Metronome::doClick(){
	int sampId;
	if (m_MetronomeOn && SDL_GetTicks() > m_LastTimeclick +	( 60000 /m_MetronomeBPM ) ){
		// It's time to make it sing !
		m_LastTimeclick = SDL_GetTicks();
		m_ClickCount ++;

		if (m_ClickCount == m_MetronomeBCount){
			m_ClickCount =0;
			sampId=myAudioEngine.play(m_HiSample);
		}else{
			sampId=myAudioEngine.play(m_LoSample);
		}

		myAudioEngine.setVolume(sampId, m_floatVolume);

	}
}
