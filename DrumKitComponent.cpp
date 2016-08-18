/*
 * DrumKitComponent.cpp
 *
 *  Created on: 13 juil. 2016
 *      Author: ludovic
 */

#include "DrumKitComponent.h"

DrumKitComponent::DrumKitComponent() {

	m_associatedTrigger=NULL;
	m_choosenInstrument=NULL;
	m_balance=0;
	m_pitch=1;
	m_replayGain=1;

}

DrumKitComponent::~DrumKitComponent() {

}

void DrumKitComponent::playInstrument(unsigned int controllerValue, unsigned int velocity){
	float soVolume;
	Instrument *tmpInst;
	SoLoud::Wav *tmpWave;
	int playingSampleID;


	// apply gain :
	soVolume=((float)velocity /127) * this->getReplayGain();

	// Get the associated instrument :
	tmpInst = this->getChoosenInstrument();
	tmpInst->setControllerValue(controllerValue);

	// Finally, get the pointer to audio sample to play.
	tmpWave = tmpInst->getSampleForVelocity(velocity);
	if (tmpWave ==NULL ){
		// No layer found !?
		return ;
	}
	// Don't forget to apply to it the panning, volume, pitch, etc...


	playingSampleID=myAudioEngine.play(*tmpWave,soVolume, this->getBalance() );
	myAudioEngine.setRelativePlaySpeed(playingSampleID, this->getPitch() );

}
