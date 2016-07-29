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
	m_reverbDelay=0;
	m_lastTriggerHit=NULL;
	m_numTriggerInput=0;
	m_lastHitVelocity=0;
}

DrumKit::~DrumKit() {

}


void DrumKit::addComponent(DrumKitComponent* drumKitComponent){
	m_DKComponentList.push_back(drumKitComponent);
}

void DrumKit::addComponent(Instrument* instrument, Trigger* trigger){
	DrumKitComponent *newDK;

	newDK=new DrumKitComponent();
	newDK->setChoosenInstrument(instrument);
	newDK->setAssociatedTrigger(trigger);

	m_DKComponentList.push_back(newDK);
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



const std::string DrumKit::getKitName() const {
	return m_kitName;
}

void DrumKit::setKitName(const std::string kitName) {
	m_kitName = kitName;
}

unsigned int DrumKit::getReverbDelay() const {
	return m_reverbDelay;
}

void DrumKit::setReverbDelay(unsigned int reverbDelay) {
	m_reverbDelay = reverbDelay;
}

int DrumKit::getNumTriggerInput() const {
	return m_numTriggerInput;
}

void DrumKit::setNumTriggerInput(int numTriggerInput) {
	m_numTriggerInput = numTriggerInput;
	Trigger *tmpTrigger;
	DrumKitComponent *DKComp;
	std::stringstream triggerName;

	// Generate a list of triggers and add it to the current Trigger List
	m_DKComponentList.clear();
	for (unsigned int i=0; i<m_numTriggerInput; i++){
		DKComp = new DrumKitComponent;
		tmpTrigger = new Trigger;

		triggerName.str("");
		triggerName << "Trigger " << (i+1);

		tmpTrigger->setInputNumber(i);
		tmpTrigger->setTriggerName(triggerName.str());

		DKComp->setAssociatedTrigger(tmpTrigger);

		m_DKComponentList.push_back(DKComp);
	}
}


void DrumKit::playInstrumentForTriggerInput(unsigned char TriggerNumber, unsigned char TriggerVelocity, unsigned char TriggerPosition){
	// Search for the trigger in the current list of Triggers :
	unsigned int i;
	unsigned char newVelocity;
	Trigger *tmpTrigger;
	Instrument *tmpInst;
	SoLoud::Wav *tmpWave;
	int playingSampleID;
	float soVolume;

	for (i=0; i<m_DKComponentList.size(); i++){
		// Get the trigger associated with this DK Component :
		tmpTrigger = m_DKComponentList[i]->getAssociatedTrigger();

		if (tmpTrigger->getInputNumber() == TriggerNumber){

			// Remap signal with curve :
			newVelocity=tmpTrigger->getSignalCurve()->getValueForX(TriggerVelocity);

			// TODO : add reverb and EQ.
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

			playingSampleID= myAudioEngine.play(*tmpWave,soVolume, m_DKComponentList[i]->getBalance() );

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
			newPosition=TriggerPosition;
			tmpTrigger->setLastVelocity(newPosition);

			// Get the associated instrument :
			tmpInst = m_DKComponentList[i]->getChoosenInstrument();
			tmpInst->setControllerValue(TriggerPosition);

			// TODO : we should allow to change the fadeout time in advanced settings.
			myAudioEngine.fadeVolume(tmpInst->getCurrentPlayingSample(), 0, (float)0.5);
		}
	}
}

unsigned int DrumKit::getLastHitVelocity() const {
	return m_lastHitVelocity;
}

std::vector<DrumKitComponent*> DrumKit::getDkComponentList() {
	return m_DKComponentList;
}

unsigned int DrumKit::getHowManyTimeInstrumentUsed(Instrument* whichInstrument) {


		unsigned int instrFound;
		DrumKitComponent *DK;


		// First ,  Scan the current drumkit for instruments that are not needed anymore (not included in current drumkit)
		for (unsigned int o=0; o<m_DKComponentList.size();o++){
			DK=m_DKComponentList[o];
			if (DK->getChoosenInstrument()==whichInstrument){
				instrFound++;
			}
		}

		return instrFound;

}
