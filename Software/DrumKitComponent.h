/*
 * DrumKitComponent.h
 *
 *  Created on: 13 juil. 2016
 *      Author: ludovic
 */

#ifndef DRUMKITCOMPONENT_H_
#define DRUMKITCOMPONENT_H_

#include "Instrument.h"
#include "Trigger.h"
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"

extern SoLoud::Soloud myAudioEngine;



class DrumKitComponent {
public:
	DrumKitComponent();
	virtual ~DrumKitComponent();

	float getPitch() const {
		return m_pitch;
	}

	void setPitch(float pitch) {
		m_pitch = pitch;
	}

	float getReplayGain() const {
		return m_replayGain;
	}

	void setReplayGain(float replayGain) {
		m_replayGain = replayGain;
	}


	float getBalance() const {
		return m_balance;
	}

	void setBalance(float balance) {
		m_balance = balance;
	}

	Instrument *getChoosenInstrument() {
		return m_choosenInstrument;
	}

	void setChoosenInstrument( Instrument *choosenInstrument) {
		m_choosenInstrument = choosenInstrument;
	}

	Trigger* getAssociatedTrigger() {
		return m_associatedTrigger;
	}

	void setAssociatedTrigger(Trigger *associatedTrigger) {
		m_associatedTrigger = associatedTrigger;
	}

	void playInstrument(unsigned int controllerValue, unsigned int velocity);

private:
	float m_replayGain;
	float m_pitch;
	float m_balance;
	Instrument *m_choosenInstrument;
	Trigger *m_associatedTrigger;


	// TODO : add REVERB and LO/HI/BANDPASS filter

};

#endif /* DRUMKITCOMPONENT_H_ */
