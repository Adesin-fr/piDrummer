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

#include "soloud.h"
#include "soloud_wav.h"
#include "Trigger.h"
#include "DrumKitComponent.h"


class DrumKit {
	public:
		DrumKit();
		virtual ~DrumKit();

		void addComponent(DrumKitComponent* drumKitComponent);

		void addComponent(Instrument* instrument, Trigger* trigger);

	const std::string getKitName() const {
		return m_kitName;
	}

	void setKitName(const std::string kitName) {
		m_kitName = kitName;
	}

	unsigned int getReverbDelay() const {
		return m_reverbDelay;
	}

	void setReverbDelay(unsigned int reverbDelay) {
		m_reverbDelay = reverbDelay;
	}

	int getNumTriggerInput() const;
	void setNumTriggerInput(int numTriggerInput);


	bool loadDrumKitFromConfigFile(std::string configFileName);

	void playInstrumentForTriggerInput(unsigned char TriggerNumber, unsigned char TriggerVelocity, unsigned char TriggerPosition);
	void setNewControllerValue(unsigned char TriggerNumber, unsigned char TriggerPosition);
	void setAfterTouchValue(unsigned char TriggerNumber, unsigned char TriggerPosition);


	unsigned int getLastHitVelocity() const;
	void setAudioEngine(SoLoud::Soloud* audioEngine);

	private:
		std::vector<DrumKitComponent*> m_DKComponentList;
		std::string m_kitName;
		unsigned int m_reverbDelay;
		Trigger *m_lastTriggerHit;
		
		unsigned int m_lastHitVelocity;
		unsigned int m_numTriggerInput;
		SoLoud::Soloud *m_audioEngine;

};

#endif /* DRUMKIT_H_ */
