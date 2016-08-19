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
#include <algorithm>	// Sort
#include <sys/stat.h>
#include <sstream>

#include "soloud.h"
#include "soloud_echofilter.h"
#include "DrumKit.h"
#include "Instrument.h"
#include "SignalCurve.h"

extern SoLoud::Soloud myAudioEngine;
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
	bool isPlaySampleOnSettingChange() const;
	void setPlaySampleOnSettingChange(bool playSampleOnSettingChange);
	bool isRotaryKnobReversed() const;
	void setRotaryKnobReversed(bool rotaryKnobReversed);
	std::vector<Trigger*>* getTriggerList();

private:

	// Function to fill trigger list :
	void fillTriggerList();

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

	// This list contains the triggers (with settings)
	std::vector<Trigger*> *m_TriggerList;


	// Pointer to currently loaded drumkit.
	DrumKit *m_currentDrumKit;

	// Pointer to the last hit trigger (or the trigger being setup)
	Trigger *m_LastHitTrigger;


	float m_GlobalFadeOutTime;

	// Shall we play the sample when we change a setting on a drumkit component ?
	bool m_playSampleOnSettingChange;

	// Is the rotary knob rotation reversed ?
	bool m_rotaryKnobReversed;


    struct InstrumentCompare {
      bool operator()(const Instrument* l, const Instrument* r) {
        return l->getInstrumentName() < r->getInstrumentName();
      }
    };

};

void fillBackground();

#endif /* INCLUDE_SETTINGS_H_ */
