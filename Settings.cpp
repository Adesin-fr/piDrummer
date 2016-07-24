/*
 * Settings.cpp
 *
 *  Created on: 12 juil. 2016
 *      Author: ludovic
 */

#include "Settings.h"

using namespace std;
using namespace libconfig;

Settings::Settings() {

	m_SettingsFileName=getUserDirectory() + "/.urDrummer/GlobalSettings.cfg";

	m_AlsaBufferSize=2048; // Default value for buffer size .
	m_Volume=32;

	m_MetronomeBCount=4;
	m_MetronomeBPM=120;
	m_MetronomeVolume=16;
	m_MetronomeOn=false;



}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
}


bool Settings::LoadSettings(){

	Config m_cfg;

	  try{
	    m_cfg.readFile(m_SettingsFileName.c_str());
	  }
	  catch(const FileIOException &fioex){
	    cerr << "I/O error while reading file "<< m_SettingsFileName << endl;
	    cerr << "Check if the file and path exist ! " << endl;
	    return(EXIT_FAILURE);
	  }
	  catch(const ParseException &pex){
	    cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
	              << " - " << pex.getError() << endl;
	    return(EXIT_FAILURE);
	  }

	 // Init the setting Object with the config from file :
	 Setting &root = m_cfg.getRoot();

	 // Init the values from the config values :
	 if(! root.exists("numTriggerInput")){
		    root.add("numTriggerInput", Setting::TypeInt) = (int)m_numTriggerInputs;
	 }else{
		 root.lookupValue("numTriggerInput", m_numTriggerInputs);
	 }


	 if(! root.exists("AlsaBufferSize")){
		    root.add("AlsaBufferSize", Setting::TypeInt) = m_AlsaBufferSize;
	 }else{
		 root.lookupValue("AlsaBufferSize", m_AlsaBufferSize);
	 }


	 if(! root.exists("GlobalVolume")){
		    root.add("GlobalVolume", Setting::TypeInt) = m_Volume;
	 }else{
		 root.lookupValue("GlobalVolume", m_Volume);
	 }

	 if(! root.exists("AutoPowerOffDelay")){
		    root.add("AutoPowerOffDelay", Setting::TypeInt) = (int)m_AutoPowerOffDelay;
	 }else{
		 root.lookupValue("AutoPowerOffDelay", m_AutoPowerOffDelay);
	 }

	 if(! root.exists("ReverbDelay")){
		    root.add("ReverbDelay", Setting::TypeInt) = m_ReverbDelay;
	 }else{
		 root.lookupValue("ReverbDelay", m_ReverbDelay);
	 }

	 // Drum kit loaded on startup :
	 if(! root.exists("PowerOnKitName")){
		    root.add("PowerOnKitName", Setting::TypeString) = m_PowerOnKitName;
	 }else{
		 root.lookupValue("PowerOnKitName", m_PowerOnKitName);
	 }

	 if(! root.exists("SerialDevice")){
		    root.add("SerialDevice", Setting::TypeString) = m_serialPort;
	 }else{
		 root.lookupValue("SerialDevice", m_serialPort);
	 }




	 // EQ Frequencies :
	 if(! root.exists("EQLowFrequency")){
		    root.add("EQLowFrequency", Setting::TypeInt) = m_EQLowFrequency;
	 }else{
		 root.lookupValue("EQLowFrequency", m_EQLowFrequency);
	 }

	 if(! root.exists("EQMidFrequency")){
		    root.add("EQMidFrequency", Setting::TypeInt) = m_EQMidFrequency;
	 }else{
		 root.lookupValue("EQMidFrequency", m_EQMidFrequency);
	 }

	 if(! root.exists("EQHiFrequency")){
		    root.add("EQHiFrequency", Setting::TypeInt) = m_EQHiFrequency;
	 }else{
		 root.lookupValue("EQHiFrequency", m_EQHiFrequency);
	 }


	 // EQ Gains :
	 if(! root.exists("EQLowGain")){
		    root.add("EQLowGain", Setting::TypeFloat) = m_EQLowGain;
	 }else{
		 root.lookupValue("EQLowGain", m_EQLowGain);
	 }

	 if(! root.exists("EQMidGain")){
		    root.add("EQMidGain", Setting::TypeFloat) = m_EQMidGain;
	 }else{
		 root.lookupValue("EQMidGain", m_EQMidGain);
	 }

	 if(! root.exists("EQHiGain")){
		    root.add("EQHiGain", Setting::TypeFloat) = m_EQHiGain;
	 }else{
		 root.lookupValue("EQHiGain", m_EQHiGain);
	 }

	  return true;

}

bool Settings::LoadSettings(string settingsFile){
	m_SettingsFileName=settingsFile;
	return LoadSettings();
}

bool Settings::SaveSettings(){
	Config m_cfg;
	 // Init the setting Object with the config from file :
	 Setting &root = m_cfg.getRoot();

	 // Init the values from the config values :
    root.add("AlsaBufferSize", Setting::TypeInt) = m_AlsaBufferSize;
    root.add("numTriggerInput", Setting::TypeInt) = (int)m_numTriggerInputs;
    root.add("GlobalVolume", Setting::TypeInt) = m_Volume;
	root.add("AutoPowerOffDelay", Setting::TypeInt) = (int)m_AutoPowerOffDelay;
	root.add("ReverbDelay", Setting::TypeInt) = m_ReverbDelay;
	root.add("PowerOnKitName", Setting::TypeString) = m_PowerOnKitName;
    root.add("SerialDevice", Setting::TypeString) = m_serialPort;

	// EQ Frequencies :
	root.add("EQLowFrequency", Setting::TypeInt) = m_EQLowFrequency;
	root.add("EQMidFrequency", Setting::TypeInt) = m_EQMidFrequency;
	root.add("EQHiFrequency", Setting::TypeInt) = m_EQHiFrequency;

	// EQ Gains :
	root.add("EQLowGain", Setting::TypeFloat) = m_EQLowGain;
	root.add("EQMidGain", Setting::TypeFloat) = m_EQMidGain;
	root.add("EQHiGain", Setting::TypeFloat) = m_EQHiGain;

    try{
    	m_cfg.writeFile(m_SettingsFileName.c_str());
    	cerr << "Updated configuration successfully written to: " << m_SettingsFileName << endl;
    }
    catch(const FileIOException &fioex){
      cerr << "I/O error while writing file: " << m_SettingsFileName << endl;
      return(false);
    }

	return true;
}

bool Settings::SaveSettings(string settingsFile){
	m_SettingsFileName=settingsFile;
	return SaveSettings();
}



void Settings::SetAudioEngine(SoLoud::Soloud &audioEngine){
	m_AudioEngine=&audioEngine;
}


unsigned int Settings::getAutoPowerOffDelay() const {
	return m_AutoPowerOffDelay;
}

void Settings::setAutoPowerOffDelay(unsigned int autoPowerOffDelay) {
	m_AutoPowerOffDelay = autoPowerOffDelay;
}

int Settings::getEqHiFrequency() const {
	return m_EQHiFrequency;
}

void Settings::setEqHiFrequency(int eqHiFrequency) {
	m_EQHiFrequency = eqHiFrequency;
}

float Settings::getEqHiGain() const {
	return m_EQHiGain;
}

void Settings::setEqHiGain(float eqHiGain) {
	m_EQHiGain = eqHiGain;
}

int Settings::getEqLowFrequency() const {
	return m_EQLowFrequency;
}

void Settings::setEqLowFrequency(int eqLowFrequency) {
	m_EQLowFrequency = eqLowFrequency;
}

float Settings::getEqLowGain() const {
	return m_EQLowGain;
}

void Settings::setEqLowGain(float eqLowGain) {
	m_EQLowGain = eqLowGain;
}

int Settings::getEqMidFrequency() const {
	return m_EQMidFrequency;
}

void Settings::setEqMidFrequency(int eqMidFrequency) {
	m_EQMidFrequency = eqMidFrequency;
}

float Settings::getEqMidGain() const {
	return m_EQMidGain;
}

void Settings::setEqMidGain(float eqMidGain) {
	m_EQMidGain = eqMidGain;
}

const string& Settings::getPowerOnKitName() const {
	return m_PowerOnKitName;
}

void Settings::setPowerOnKitName(const string& powerOnKitName) {
	m_PowerOnKitName = powerOnKitName;
}

int Settings::getReverbDelay() const {
	return m_ReverbDelay;
}

void Settings::setReverbDelay(int reverbDelay) {
	float tmpDelay = reverbDelay/1000;

	m_ReverbDelay = reverbDelay;
	if (reverbDelay>0){
		m_Echofilter.setParams(tmpDelay , 0.1f);
		m_AudioEngine->setGlobalFilter(0, &m_Echofilter);
	}else{
		m_AudioEngine->setGlobalFilter(0, NULL);
	}
}

int Settings::getVolume() const {
	return m_Volume;
}

void Settings::setVolume(int volume) {
	float tmpVolume=volume/100;
	m_Volume = volume;
	m_AudioEngine->setGlobalVolume(tmpVolume);
}

int Settings::getAlsaBufferSize() const {
	return m_AlsaBufferSize;
}


void Settings::setAlsaBufferSize(int bufferSize) {
	m_AlsaBufferSize=bufferSize;

	// Deinit the audio engine :
	m_AudioEngine->deinit();

	// Reinit the audio engine :
	m_AudioEngine->init(1, 0,0, m_AlsaBufferSize);

}

const std::string& Settings::getLanguage() const {
	return m_Language;
}

void Settings::setLanguage(const std::string& language) {
	m_Language = language;
}

DrumKit* Settings::getCurrentDrumKit() const {
	return m_currentDrumKit;
}

void Settings::setCurrentDrumKit(DrumKit* currentDrumKit) {
	m_currentDrumKit = currentDrumKit;
}

void Settings::loadDrumKitList(){
	string KitDir;
	string fileName;
	DrumKit* loadKit;
	DIR *dir;
	struct dirent *ent;

	KitDir=getUserDirectory() + "/.urDrummer/DrumKits/";

	cerr << "Loading drumkits from folder " + KitDir << endl;

	dir = opendir(KitDir.c_str());

	if (dir != NULL){
		while((ent = readdir(dir))!=NULL){
			fileName=ent->d_name;
			if (fileName!="." && fileName!=".."){
				loadKit= new DrumKit();
				if (loadKit->loadDrumKitFromConfigFile(KitDir + fileName)){
					// add the instrument to the list
					m_drumKitList.push_back(loadKit);
				}
				else{
					// Delete the instrument : it is not valid !
					delete loadKit;
				}
			}
		}
		closedir(dir);
	}else{
		cout << "Error opening folder " + KitDir << endl;
	}

	// Finished : debug some info about instrument loaded count :
	cerr << "Finished scanning folder. " << m_drumKitList.size() << " Drum kits successfully loaded." << endl << endl;

}

void Settings::loadInstrumentList(){
	string instrumentDir;
	string folderName;
	Instrument* loadInstr;
	DIR *dir;
	struct dirent *ent;

	instrumentDir=getUserDirectory() + "/.urDrummer/Instruments/";

	cerr << "Loading instruments from folder " + instrumentDir << endl;

	dir = opendir(instrumentDir.c_str());

	if (dir != NULL){
		while((ent = readdir(dir))!=NULL){
			folderName=ent->d_name;

			if (folderName!="." && folderName!=".."){
				loadInstr= new Instrument();
				if (loadInstr->loadInstrumentFromConfig(instrumentDir + folderName + "/instrument.cfg")){
					// add the instrument to the list
					m_instrumentList.push_back(loadInstr);
				}
				else{
					// Delete the instrument : it is not valid !
					delete loadInstr;
				}
			}
		}
		closedir(dir);
	}else{
		cout << "Error opening folder " + instrumentDir << endl;
	}

	// Finished : debug some info about instrument loaded count :
	cerr << "Finished scanning folder. " << m_instrumentList.size() << " instrument successfully loaded." << endl << endl;

}


bool Settings::loadDrumKit(DrumKit *drumKit){

	std::vector<DrumKitComponent*> newDKCL, oldDKCL;
	bool instrFound;
	DrumKitComponent *oDK, *nDK;

	oldDKCL=drumKit->getDkComponentList();
	newDKCL=m_currentDrumKit->getDkComponentList();

	// First ,  Scan the current drumkit for instruments that are not needed anymore (not included in current drumkit)
	for (unsigned int o=0; o<oldDKCL.size();o++){
		instrFound=false;
		oDK=oldDKCL[o];
		for (unsigned int n=0; n<newDKCL.size();n++){
			nDK=newDKCL[n];
			if (oDK->getChoosenInstrument()==nDK->getChoosenInstrument()){
				instrFound=true;
				break;
			}
		}
		if (!instrFound){
			// Instr was in the previous drumkit but not the new one, no more needed !
			oDK->getChoosenInstrument()->unloadInstrumentSamples();
		}
	}
	// Then load missing instruments :
	for (unsigned int n=0; n<newDKCL.size();n++){
		// Get a pointer to the DrumKitComponent :
		nDK=newDKCL[n];
		if (!nDK->getChoosenInstrument()->isLoaded()){
			// Load only if the instrument is not already loaded !
			nDK->getChoosenInstrument()->loadInstrumentSamples();
		}
	}

	m_currentDrumKit=drumKit;

	return true;
}


bool Settings::loadDrumKitFromName(std::string drumKitName){
	// search for the drumkit in loaded kits, and assign it to the current one :

	for (unsigned int i=0; i<m_drumKitList.size(); i++){
		if (m_drumKitList[i]->getKitName() == drumKitName){
			m_currentDrumKit=m_drumKitList[i];
			return true;
		}
	}
	return false;
}

std::string Settings::getUserDirectory(){
	string userDir;

	struct passwd *pw = getpwuid(getuid());

	userDir = pw->pw_dir;
	return userDir;
}

const std::vector<Instrument*>& Settings::getInstrumentList() const {
	return m_instrumentList;
}

unsigned int Settings::getNumTriggerInputs() const {
	return m_numTriggerInputs;
}

const std::string& Settings::getSerialPort() const {
	return m_serialPort;
}

void Settings::setSerialPort(const std::string& serialPort) {
	m_serialPort = serialPort;
}

const std::vector<DrumKit*>& Settings::getDrumKitList() const {
	return m_drumKitList;
}
