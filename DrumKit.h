/*
 * DrumKit.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#ifndef DRUMKIT_H_
#define DRUMKIT_H_

#include <vector>
#include <string>
#include <libconfig.h++>
#include <iostream>
#include <sstream>

#include "soloud.h"
#include "soloud_wav.h"
#include "Trigger.h"
#include "DrumKitComponent.h"
#include "SignalCurve.h"
#include "Settings.h"


// Reference the Settings Class :
class Settings;


extern SoLoud::Soloud myAudioEngine;
extern Settings myglobalSettings;

class DrumKit {
	public:
		DrumKit();
		virtual ~DrumKit();

		void addComponent(DrumKitComponent* drumKitComponent);
		void addComponent(Instrument* instrument, Trigger* trigger);

		const std::string getKitName() const ;
		void setKitName(const std::string kitName) ;
		unsigned int getReverbDelay() const ;
		void setReverbDelay(unsigned int reverbDelay);
		int getNumTriggerInput() const;
		void setNumTriggerInput(int numTriggerInput);

		bool loadDrumKitFromConfigFile(std::string configFileName);
		bool saveDrumKitToConfigFile();

		void playInstrumentForTriggerInput(unsigned char TriggerNumber, unsigned char TriggerVelocity, unsigned char TriggerPosition);
		void setNewControllerValue(unsigned char TriggerNumber, unsigned char TriggerPosition);
		void setAfterTouchValue(unsigned char TriggerNumber, unsigned char TriggerPosition);

		std::vector<DrumKitComponent*> *getDkComponentList();

		unsigned int getHowManyTimeInstrumentUsed(Instrument *whichInstrument);
		Trigger* getLastTriggerHit();

		void cleanUpInstrumentSamples();

	private:
		std::vector<DrumKitComponent*> *m_DKComponentList;
		std::string m_kitName;
		unsigned int m_reverbDelay;
		Trigger *m_lastTriggerHit;
		
		unsigned int m_numTriggerInput;

};

#endif /* DRUMKIT_H_ */
