/*
 * DrumKit.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "DrumKit.h"

using namespace libconfig;
using namespace std;

DrumKit::DrumKit() {
	// TODO Auto-generated constructor stub
	m_reverbDelay=0;
	m_lastTriggerHit=NULL;
	m_numTriggerInput=0;
	m_audioEngine =NULL;
	m_lastHitVelocity=0;
}

DrumKit::~DrumKit() {
	// TODO Auto-generated destructor stub
}

bool DrumKit::loadDrumKitFromConfigFile(std::string configFileName){
	Config m_cfg;

	try {
		m_cfg.readFile(configFileName.c_str());
	} catch (const FileIOException &fioex) {
		cerr << "I/O error while reading file " << configFileName << endl;
		return (false);
	} catch (const ParseException &pex) {
		cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
				<< " - " << pex.getError() << endl;
		return (false);
	}

	Setting &root = m_cfg.getRoot();

	// Get Drum Kit  Name :
	root.lookupValue("DrumKitName", m_kitName);

	// TODO : load the drumkit components from the config file

	return true;
}


int DrumKit::getNumTriggerInput() const {
	return m_numTriggerInput;
}

void DrumKit::setNumTriggerInput(int numTriggerInput) {
	m_numTriggerInput = numTriggerInput;
	Trigger *tmpTrigger;
	DrumKitComponent *DKComp;

	// Generate a list of triggers and add it to the current Trigger List
	m_DKComponentList.clear();
	for (unsigned int i=0; i<m_numTriggerInput; i++){
		DKComp = new DrumKitComponent;
		tmpTrigger = new Trigger;
		tmpTrigger->setInputNumber(i);

		DKComp->setAssociatedTrigger(tmpTrigger);

		m_DKComponentList.push_back(DKComp);
	}
}

void DrumKit::setAudioEngine(SoLoud::Soloud* audioEngine) {
	m_audioEngine = audioEngine;
}


void DrumKit::playInstrumentForTriggerInput(unsigned char TriggerNumber, unsigned char TriggerVelocity, unsigned char TriggerPosition){
	// Search for the trigger in the current list of Triggers :
	unsigned int i;
	unsigned char newVelocity;
	Trigger *tmpTrigger;
	Instrument *tmpInst;
	SoLoud::Wav tmpWave;
	int playingSampleID;
	float soVolume;

	for (i=0; i<m_DKComponentList.size(); i++){
		// Get the trigger associated with this DK Component :
		tmpTrigger = m_DKComponentList[i]->getAssociatedTrigger();

		if (tmpTrigger->getInputNumber() == TriggerNumber){
			// TODO : handle signal curve remapping ...
			// TODO : add reverb and EQ.

			newVelocity=TriggerVelocity;
			tmpTrigger->setLastVelocity(newVelocity);

			// Assign our last trigger hit
			this->m_lastTriggerHit = tmpTrigger;

			soVolume=(float)newVelocity/127;

			// Get the associated instrument :
			tmpInst = m_DKComponentList[i]->getChoosenInstrument();
			tmpInst->setControllerValue(TriggerPosition);

			// Finally, get the pointer to audio sample to play.
			tmpWave = tmpInst->getSampleForVelocity(newVelocity);
			// Don't forget to apply to it the panning, volume, pitch, etc...

			playingSampleID= m_audioEngine->play(tmpWave,soVolume, m_DKComponentList[i]->getBalance() );

			tmpInst->setCurrentPlayingSample(playingSampleID);


			// We've found our instrument, so exit the search.
			// Perhaps in a future version, we'll be able to manage multiple instruments for one trigger....
			break;
		}
	}
}

void DrumKit::setNewControllerValue(unsigned char TriggerNumber, unsigned char TriggerPosition){
	// Search for the trigger in the current list of Triggers :
	unsigned int i;
	unsigned char newPosition;
	Trigger *tmpTrigger;
	Instrument *tmpInst;

	for (i=0; i<m_DKComponentList.size(); i++){
		// Get the trigger associated with this DK Component :
		tmpTrigger = m_DKComponentList[i]->getAssociatedTrigger();

		if (tmpTrigger->getInputNumber() == TriggerNumber){
			// TODO : handle signal curve remapping ...
			newPosition=TriggerPosition;
			tmpTrigger->setLastVelocity(newPosition);

			// Get the associated instrument :
			tmpInst = m_DKComponentList[i]->getChoosenInstrument();
			tmpInst->setControllerValue(TriggerPosition);
		}
	}
}


void DrumKit::setAfterTouchValue(unsigned char TriggerNumber, unsigned char TriggerPosition){
	// Search for the trigger in the current list of Triggers :
	unsigned int i;
	unsigned char newPosition;
	Trigger *tmpTrigger;
	Instrument *tmpInst;

	for (i=0; i<m_DKComponentList.size(); i++){
		// Get the trigger associated with this DK Component :
		tmpTrigger = m_DKComponentList[i]->getAssociatedTrigger();

		if (tmpTrigger->getInputNumber() == TriggerNumber){
			// TODO : handle signal curve remapping ...
			newPosition=TriggerPosition;
			tmpTrigger->setLastVelocity(newPosition);

			// Get the associated instrument :
			tmpInst = m_DKComponentList[i]->getChoosenInstrument();
			tmpInst->setControllerValue(TriggerPosition);

			// TODO : should we do something better than this ??
			// TODO : we should allow to change the fadeout time ?
			m_audioEngine->fadeVolume(tmpInst->getCurrentPlayingSample(), 0, (float)0.5);
		}
	}
}

unsigned int DrumKit::getLastHitVelocity() const {
	return m_lastHitVelocity;
}

