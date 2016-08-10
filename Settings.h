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

// Reference the DrumKit Class :
class DrumKit;

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
	Instrument* getNextInstrument(Instrument *currentInstrument);
	Instrument* getPreviousInstrument(Instrument *currentInstrument);

	void loadDrumKitList();

	bool loadDrumKit(DrumKit *drumKit);
	DrumKit *GetDrumKitFromName(std::string drumKitName);

	bool checkIfFileExists(const std::string& filePath);

	std::string getUserDirectory();
	std::vector<Instrument*> *getInstrumentList();
	unsigned int getNumTriggerInputs() const;
	const std::string& getSerialPort() const;
	void setSerialPort(const std::string& serialPort);
	std::vector<DrumKit*> *getDrumKitList();


	Trigger *getLastHitTrigger() ;
	void setLastHitTrigger(Trigger *lastHitTrigger);
	float getGlobalFadeOutTime() const;
	void setGlobalFadeOutTime(float globalFadeOutTime);

private:
	SoLoud::Soloud *m_AudioEngine;
	SoLoud::EchoFilter *m_Echofilter;

	// Current global Volume
	int m_Volume;

	// Global Delay
	int m_ReverbDelay;

	// Global Equalizer
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

	// This list contains all available instruments (loaded or not)
	std::vector<Instrument*> *m_instrumentList;

	// This list contains all available drumkits
	std::vector<DrumKit*> *m_drumKitList;

	// Pointer to currently loaded drumkit.
	DrumKit *m_currentDrumKit;

	// Pointer to the last hit trigger (or the trigger being setup)
	Trigger *m_LastHitTrigger;


	float m_GlobalFadeOutTime;

};

void fillBackground();

#endif /* INCLUDE_SETTINGS_H_ */
