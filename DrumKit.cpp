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
	m_DKComponentList = new vector<DrumKitComponent*>;
}

DrumKit::~DrumKit() {
	// empty the comp list:
	for (unsigned int i=0; i<m_DKComponentList->size(); i++){
		delete (*m_DKComponentList)[i];
	}
	delete m_DKComponentList;
}

DrumKit *DrumKit::CopyDrumKit(){
	DrumKit *newDrumKit;
	newDrumKit = new DrumKit();

	// Set new name :
	newDrumKit->setKitName("Copy Of " + m_kitName);

	// Copy components :
	for (unsigned int i=0; i < m_DKComponentList->size(); i++){
		DrumKitComponent *newDKC, *thisDKC;

		thisDKC= (*m_DKComponentList)[i];
		// Create a new component :
		newDKC=new DrumKitComponent();

		newDKC->setAssociatedTrigger(thisDKC->getAssociatedTrigger());
		newDKC->setChoosenInstrument(thisDKC->getChoosenInstrument());
		newDKC->setBalance(thisDKC->getBalance());
		newDKC->setPitch(thisDKC->getPitch());
		newDKC->setReplayGain(thisDKC->getReplayGain());

		// Add the component to the new DK component's list :
		newDrumKit->addComponent(newDKC);
	}

	// Save the drumkit :
	newDrumKit->saveDrumKitToConfigFile();

	return newDrumKit;
}


void DrumKit::addComponent(DrumKitComponent* drumKitComponent){
	m_DKComponentList->push_back(drumKitComponent);
}

void DrumKit::addComponent(Instrument* instrument, Trigger* trigger){
	DrumKitComponent *newDK;

	newDK=new DrumKitComponent();
	newDK->setChoosenInstrument(instrument);
	newDK->setAssociatedTrigger(trigger);

	m_DKComponentList->push_back(newDK);
}


bool DrumKit::loadDrumKitFromConfigFile(std::string configFileName){
	Config m_cfg;
	vector<Instrument*> *instList;
	instList=myglobalSettings.getInstrumentList();


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

	if (root.exists("Components")){
		Setting &DKComps = root["Components"];
		unsigned int nbComps = DKComps.getLength();
		if (nbComps > myglobalSettings.getNumTriggerInputs()){
			nbComps = myglobalSettings.getNumTriggerInputs();
		}
		// iterate throught components :

		for (unsigned int i =0; i<nbComps; i++){
			unsigned int triggerNumber;
			string instrumentName;
			Instrument *choosenInstrument;
			float replayGain;
			float pitch;
			float balance;

			DKComps[i].lookupValue("triggerNumber",triggerNumber);
			DKComps[i].lookupValue("instrumentName",instrumentName);
			DKComps[i].lookupValue("replayGain",replayGain);
			DKComps[i].lookupValue("pitch",pitch);
			DKComps[i].lookupValue("balance",balance);

			if (instrumentName==""){
				choosenInstrument=NULL;
			}else{
				// Get instrument from list :
				choosenInstrument=NULL;
				for (unsigned int instrI=0; instrI< instList->size(); instrI++){
					if ((*instList)[instrI]->getInstrumentName()==instrumentName){
						choosenInstrument=(*instList)[instrI];
						break;
					}
				}
			}

			// put the instrument on the drumkit component.
			(*m_DKComponentList)[triggerNumber]->setChoosenInstrument(choosenInstrument);

			// put the other settings :
			(*m_DKComponentList)[triggerNumber]->setReplayGain(replayGain);
			(*m_DKComponentList)[triggerNumber]->setPitch(pitch);
			(*m_DKComponentList)[triggerNumber]->setBalance(balance);

		}
	}


	return true;
}


bool DrumKit::saveDrumKitToConfigFile(){
	Config m_cfg;
	std::string configFileName;

	configFileName = myglobalSettings.getUserDirectory() + "/.urDrummer/DrumKits/" + m_kitName + ".cfg";

	cerr << "Saving drumKit to file  " << configFileName << endl;

	Setting &root = m_cfg.getRoot();

	// Set Drum Kit Name :
	root.add("DrumKitName", Setting::TypeString)=m_kitName;

	root.add("Components",Setting::TypeList);

	// Add the Components list :
	Setting &compList=root["Components"];

	for (unsigned int i =0; i<m_DKComponentList->size(); i++){
		Instrument *instr;

		Setting &DKComp =compList.add(Setting::TypeGroup);

		DKComp.add("triggerNumber", Setting::TypeInt) = (int)i;
		instr=(*m_DKComponentList)[i]->getChoosenInstrument();
		if (instr!=NULL){
			DKComp.add("instrumentName", Setting::TypeString) = instr->getInstrumentName();
		}else{
			DKComp.add("instrumentName", Setting::TypeString) = "";
		}
		DKComp.add("replayGain", Setting::TypeFloat) = (*m_DKComponentList)[i]->getReplayGain();
		DKComp.add("pitch", Setting::TypeFloat) = (*m_DKComponentList)[i]->getPitch();
		DKComp.add("balance", Setting::TypeFloat) = (*m_DKComponentList)[i]->getBalance();

	}

    try{
    	m_cfg.writeFile(configFileName.c_str());
    	cerr << "Drumkit saved to: " << configFileName << endl;
    }
    catch(const FileIOException &fioex){
      cerr << "I/O error while writing file: " << configFileName << endl;
      return(false);
    }

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

void DrumKit::setNumTriggerInput(int numTriggerInput) {
	DrumKitComponent *DKComp;
	std::vector<Trigger*> *TriggList;

	TriggList=myglobalSettings.getTriggerList();

	// Generate a list of triggers and add it to the current Trigger List
	m_DKComponentList->clear();
	for (unsigned int i=0; i < myglobalSettings.getNumTriggerInputs() ; i++){
		DKComp = new DrumKitComponent;

		DKComp->setAssociatedTrigger((*TriggList)[i]);

		m_DKComponentList->push_back(DKComp);
	}
}


void DrumKit::playInstrumentForTriggerInput(unsigned char TriggerNumber, unsigned char TriggerVelocity, unsigned char TriggerPosition){
	// Search for the trigger in the current list of Triggers :
	unsigned int i;
	unsigned int newVelocity;
	Trigger *tmpTrigger;
	Instrument *tmpInst;
	SoLoud::Wav *tmpWave;
	int playingSampleID;
	float soVolume;

	if (TriggerVelocity>127){
		// Max velocity is 127 !!
		TriggerVelocity=127;
	}

	for (i=0; i < m_DKComponentList->size(); i++){
		// Get the trigger associated with this DK Component :
		tmpTrigger = (*m_DKComponentList)[i]->getAssociatedTrigger();

		// Set Last Trigger Hit
		m_lastTriggerHit=tmpTrigger;

		if (tmpTrigger->getInputNumber() == TriggerNumber){

			if (tmpTrigger->getSignalCurve()!=NULL){
				// unhandled exit here !!Remap signal with curve :
				newVelocity=tmpTrigger->getSignalCurve()->getValueForX(TriggerVelocity);
			}else{
				newVelocity= TriggerVelocity;
			}


			// TODO : add reverb and EQ.
			tmpTrigger->setLastVelocity(newVelocity);

			// Assign our last trigger hit
			this->m_lastTriggerHit = tmpTrigger;

			// apply gain :
			soVolume=((float)newVelocity /127) * (*m_DKComponentList)[i]->getReplayGain();

			// Get the associated instrument :
			tmpInst = (*m_DKComponentList)[i]->getChoosenInstrument();
			tmpInst->setControllerValue(TriggerPosition);

			// Finally, get the pointer to audio sample to play.
			tmpWave = tmpInst->getSampleForVelocity(newVelocity);
			if (tmpWave ==NULL ){
				// No layer found !?
				return ;
			}
			// Don't forget to apply to it the panning, volume, pitch, etc...

			playingSampleID=tmpInst->getCurrentPlayingSample();
			if (playingSampleID!=0){
				//myAudioEngine.stop(playingSampleID);
				myAudioEngine.fadeVolume(playingSampleID, 0, 1.0f);
			}

			playingSampleID= myAudioEngine.play(*tmpWave,soVolume, (*m_DKComponentList)[i]->getBalance() );
			myAudioEngine.setRelativePlaySpeed(playingSampleID,(*m_DKComponentList)[i]->getPitch() );

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

	for (i=0; i<m_DKComponentList->size(); i++){
		// Get the trigger associated with this DK Component :
		tmpTrigger = (*m_DKComponentList)[i]->getAssociatedTrigger();

		if (tmpTrigger->getInputNumber() == TriggerNumber){
			newPosition=TriggerPosition;
			tmpTrigger->setLastVelocity(newPosition);

			// Get the associated instrument :
			tmpInst = (*m_DKComponentList)[i]->getChoosenInstrument();
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

	for (i=0; i<m_DKComponentList->size(); i++){
		// Get the trigger associated with this DK Component :
		tmpTrigger = (*m_DKComponentList)[i]->getAssociatedTrigger();

		if (tmpTrigger->getInputNumber() == TriggerNumber){
			newPosition=TriggerPosition;
			tmpTrigger->setLastVelocity(newPosition);

			// Get the associated instrument :
			tmpInst = (*m_DKComponentList)[i]->getChoosenInstrument();
			tmpInst->setControllerValue(TriggerPosition);

			myAudioEngine.fadeVolume(tmpInst->getCurrentPlayingSample(), 0, myglobalSettings.getGlobalFadeOutTime());
		}
	}
}

std::vector<DrumKitComponent*> *DrumKit::getDkComponentList() {
	return m_DKComponentList;
}

unsigned int DrumKit::getHowManyTimeInstrumentUsed(Instrument* whichInstrument) {

			unsigned int instrFound=0;
			DrumKitComponent *DK;


			// First ,  Scan the current drumkit for instruments that are not needed anymore (not included in current drumkit)
			for (unsigned int o=0; o<m_DKComponentList->size();o++){
				DK=(*m_DKComponentList)[o];
				if (DK->getChoosenInstrument()==whichInstrument){
					instrFound++;
				}
			}

			return instrFound;

	}

Trigger* DrumKit::getLastTriggerHit() {
	return m_lastTriggerHit;
}

void DrumKit::cleanUpInstrumentSamples(){
	// Iterate thru Instrument List and clean those which are not currently used.
	vector<Instrument*> *instrList;

	// Get the instrument list :
	instrList=myglobalSettings.getInstrumentList();

	for (unsigned int i=0; i<instrList->size(); i++){
		unsigned int usedCount;
		usedCount=this->getHowManyTimeInstrumentUsed((*instrList)[i]);
		if (usedCount==0 && (*instrList)[i]->isLoaded()){
			(*instrList)[i]->unloadInstrumentSamples();
		}
	}
}

