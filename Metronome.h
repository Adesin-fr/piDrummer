/*
 * Metronome.h
 *
 *  Created on: 8 août 2016
 *      Author: ulle0009
 */

#ifndef METRONOME_H_
#define METRONOME_H_

#include <SDL/SDL.h>
#include <string>
#include "soloud.h"
#include "soloud_wav.h"
#include "Settings.h"

extern SoLoud::Soloud myAudioEngine;
extern Settings myglobalSettings;

class Metronome {
public:
	Metronome();
	virtual ~Metronome();

	void doClick();

	unsigned int getMetronomeBCount() const {
		return m_MetronomeBCount;
	}

	void setMetronomeBCount(unsigned int metronomeBCount) {
		m_MetronomeBCount = metronomeBCount;
	}

	unsigned int getMetronomeBpm() const {
		return m_MetronomeBPM;
	}

	void setMetronomeBpm(unsigned int metronomeBpm) {
		m_MetronomeBPM = metronomeBpm;
	}

	bool isMetronomeOn() const {
		return m_MetronomeOn;
	}

	void setMetronomeOn(bool metronomeOn) {
		m_MetronomeOn = metronomeOn;
	}

	unsigned int getMetronomeVolume() const {
		return m_MetronomeVolume;
	}

	void setMetronomeVolume(unsigned int metronomeVolume) {
		m_MetronomeVolume = metronomeVolume;
		m_floatVolume=((float)m_MetronomeVolume/32);
	}

	void IncMetronomeBpm(unsigned int HowMuch) {
		m_MetronomeBPM += HowMuch;
		if (m_MetronomeBPM>240) m_MetronomeBPM=240;
	}

	void DecMetronomeBpm(unsigned int HowMuch) {
		m_MetronomeBPM -= HowMuch;
		if (m_MetronomeBPM<20) m_MetronomeBPM=20;
	}


private:
	int m_MetronomeBPM;
	unsigned int  m_MetronomeVolume;
	float m_floatVolume;
	unsigned int m_MetronomeBCount;
	bool m_MetronomeOn;

	unsigned int m_ClickCount;
	unsigned int m_LastTimeclick;

	SoLoud::Wav m_LoSample;
	SoLoud::Wav m_HiSample;
};

#endif /* METRONOME_H_ */
