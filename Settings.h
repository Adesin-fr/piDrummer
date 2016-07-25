/*
 * Settings.h
 *
 *  Created on: 12 juil. 2016
 *      Author: ludovic
 */

#ifndef INCLUDE_SETTINGS_H_
#define INCLUDE_SETTINGS_H_

#include <string>
#include <libconfig.h++>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <exception>
#include "dirent.h"
#include "unistd.h"
#include "sys/types.h"
#include "pwd.h"
#include <vector>
#include <sys/stat.h>

#include "soloud.h"
#include "soloud_echofilter.h"
#include "DrumKit.h"
#include "Instrument.h"


class Settings {
public:
	Settings();

	virtual ~Settings();

	bool LoadSettings();
	bool LoadSettings(std::string settingsFile);

	bool SaveSettings();
	bool SaveSettings(std::string settingsFile);


	// Initialize the Setting object with the audio Engine
	void SetAudioEngine(SoLoud::Soloud &audioEngine);

	unsigned int getAutoPowerOffDelay() const;
	void setAutoPowerOffDelay(unsigned int autoPowerOffDelay);
	int getEqHiFrequency() const;
	void setEqHiFrequency(int eqHiFrequency);
	float getEqHiGain() const;
	void setEqHiGain(float eqHiGain);
	int getEqLowFrequency() const;
	void setEqLowFrequency(int eqLowFrequency);
	float getEqLowGain() const;
	void setEqLowGain(float eqLowGain);
	int getEqMidFrequency() const;
	void setEqMidFrequency(int eqMidFrequency);
	float getEqMidGain() const;
	void setEqMidGain(float eqMidGain);
	const std::string& getPowerOnKitName() const;
	void setPowerOnKitName(const std::string& powerOnKitName);
	int getReverbDelay() const;
	void setReverbDelay(int reverbDelay);
	int getVolume() const;
	void setVolume(int volume);
	void setAlsaBufferSize(int bufferSize);
	int getAlsaBufferSize() const;
	const std::string& getLanguage() const;
	void setLanguage(const std::string& language);
	DrumKit* getCurrentDrumKit() const;
	void setCurrentDrumKit(DrumKit* currentDrumKit);

	void loadInstrumentList();
	void loadDrumKitList();

	bool loadDrumKit(DrumKit *drumKit);
	bool loadDrumKitFromName(std::string drumKitName);

	bool checkIfFileExists(const std::string& filePath);

	std::string getUserDirectory();
	const std::vector<Instrument*>& getInstrumentList() const;
	unsigned int getNumTriggerInputs() const;
	const std::string& getSerialPort() const;
	void setSerialPort(const std::string& serialPort);
	const std::vector<DrumKit*>& getDrumKitList() const;

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


	void IncMetronomeBpm(unsigned int HowMuch) {
		m_MetronomeBPM += HowMuch;
		if (m_MetronomeBPM>240) m_MetronomeBPM=240;
	}

	void DecMetronomeBpm(unsigned int HowMuch) {
		m_MetronomeBPM -= HowMuch;
		if (m_MetronomeBPM<20) m_MetronomeBPM=20;
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
	}

private:
	SoLoud::Soloud *m_AudioEngine;
	SoLoud::EchoFilter m_Echofilter;


	int m_Volume;
	int m_ReverbDelay;

	int m_EQLowFrequency;
	float m_EQLowGain;
	int m_EQMidFrequency;
	float m_EQMidGain;
	int m_EQHiFrequency;
	float m_EQHiGain;

	unsigned int m_AutoPowerOffDelay;
	int m_AlsaBufferSize;
	unsigned int m_numTriggerInputs;

	std::string m_Language;
	std::string m_PowerOnKitName;
	std::string m_SettingsFileName;
	std::string m_serialPort;

	std::vector<Instrument*> m_instrumentList;
	std::vector<DrumKit*> m_drumKitList;
	// This list is kept up-to-date with loaded instruments.
	// So, when we load a drumkit, we can ask unloaded instruments to load samples,
	// and unload loaded ones that are not needed anymore!
	std::vector<Instrument*> m_LoadedinstrumentList;

	DrumKit *m_currentDrumKit;

	unsigned int m_MetronomeBPM;
	unsigned int m_MetronomeVolume;
	unsigned int m_MetronomeBCount;
	bool m_MetronomeOn;

};

#endif /* INCLUDE_SETTINGS_H_ */
