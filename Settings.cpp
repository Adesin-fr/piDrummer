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

	m_GlobalFadeOutTime=0.5f;
	m_instrumentList=new vector<Instrument*>;

	m_drumKitList = new vector<DrumKit*>;

	m_TriggerList = new vector<Trigger*>;

	m_playSampleOnSettingChange=true;

}

Settings::~Settings() {
}

bool Settings::checkIfFileExists(const std::string& filePath){
	 struct stat buffer;
	 std::string compFile=getUserDirectory() + "/.urDrummer/" + filePath;
	 if (stat (compFile.c_str(), &buffer) != 0){
		 // relative path doesnt exist, Test for absolute path :
		 return (stat (filePath.c_str(), &buffer) == 0);
	 }else{
		 return true;
	 }

}

bool Settings::LoadSettings(){

	Config m_cfg;
	Trigger *trig;
	int tmpInt;
	string tmpString;

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

	 if( root.exists("RotaryKnobAction")){
		 root.lookupValue("RotaryKnobAction", m_RotaryAction);
	 }

	 // Set the trigger List :
	 fillTriggerList();



	 if(root.exists("Triggers")){
		 Setting &TrigList=root["Triggers"];
		 unsigned int nbTriggers = TrigList.getLength();

		 for (unsigned int i=0; i<nbTriggers && i<m_numTriggerInputs ; i++){
			trig=(*m_TriggerList)[i];
			Setting &TriggerSetting=TrigList[i];

			TriggerSetting.lookupValue("InputNumber",tmpInt);
			trig->setInputNumber(tmpInt);
			TriggerSetting.lookupValue("Name",tmpString);
			trig->setTriggerName(tmpString);
			TriggerSetting.lookupValue("TriggerType",tmpInt);
			trig->setTriggerType(tmpInt);
			TriggerSetting.lookupValue("Threshold",tmpInt);
			trig->setThreshold(tmpInt);
			TriggerSetting.lookupValue("DynamicTriggerPercent",tmpInt);
			trig->setDynamicTriggerPercent(tmpInt);
			TriggerSetting.lookupValue("ControllerResolution",tmpInt);
			trig->setControllerResolution(tmpInt);
			TriggerSetting.lookupValue("PositionalSensing",tmpInt);
			trig->setHasController(tmpInt);
			TriggerSetting.lookupValue("MuteGroup",tmpInt);
			trig->setMuteGroup(tmpInt);
			TriggerSetting.lookupValue("CrossTalkGroup",tmpInt);
			trig->setCrossTalkGroup(tmpInt);
			TriggerSetting.lookupValue("FixedMaskTime",tmpInt);
			trig->setFixedMaskTime(tmpInt);
			TriggerSetting.lookupValue("MaxValue",tmpInt);
			trig->setMaxValue(tmpInt);
			TriggerSetting.lookupValue("FootSplashSensitivity",tmpInt);
			trig->setFootSplashSensitivity(tmpInt);
			TriggerSetting.lookupValue("SignalCurveType",tmpInt);
			trig->getSignalCurve()->setCurveType(tmpInt);


			if (trig->getSignalCurve()->getCurveType() == SignalCurve::Curve_Custom ){
				// Get the Points list :
				Setting &CurvePointList=TriggerSetting["CurvePoints"];
				std::vector<CurvePoint*> *m_curvePoints;

				m_curvePoints=trig->getSignalCurve()->getAllCurvePoints();

				for (unsigned int c=0; c < m_curvePoints->size(); c++){
					(*m_curvePoints)[c]->yValue= CurvePointList[c];
				}
			}
		 }

	}



	  return true;

}

bool Settings::LoadSettings(string settingsFile){
	m_SettingsFileName=settingsFile;
	return LoadSettings();
}

bool Settings::SaveSettings(){
	Config m_cfg;
	Trigger *trig;

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
	root.add("GlobalFadeOutTime", Setting::TypeFloat) = m_GlobalFadeOutTime;
	root.add("PlaySampleOnSettingChange", Setting::TypeBoolean) = m_playSampleOnSettingChange;
	root.add("RotaryKnobInversion", Setting::TypeBoolean) = m_rotaryKnobReversed;
	root.add("RotaryKnobAction", Setting::TypeInt) = m_RotaryAction;

	// EQ Frequencies :
	root.add("EQLowFrequency", Setting::TypeInt) = m_EQLowFrequency;
	root.add("EQMidFrequency", Setting::TypeInt) = m_EQMidFrequency;
	root.add("EQHiFrequency", Setting::TypeInt) = m_EQHiFrequency;

	// EQ Gains :
	root.add("EQLowGain", Setting::TypeFloat) = m_EQLowGain;
	root.add("EQMidGain", Setting::TypeFloat) = m_EQMidGain;
	root.add("EQHiGain", Setting::TypeFloat) = m_EQHiGain;

	// Save the trigger list & settings to the file :
	root.add("Triggers", Setting::TypeList) ;

	// Add the Trigger list :
	Setting &TrigList=root["Triggers"];

	for (unsigned int i=0; i<m_TriggerList->size(); i++){
		trig=(*m_TriggerList)[i];

		Setting &SetTrigger =TrigList.add(Setting::TypeGroup);

		SetTrigger.add("InputNumber", Setting::TypeInt) = (int)trig->getInputNumber();
		SetTrigger.add("Name", Setting::TypeString) = trig->getTriggerName();
		SetTrigger.add("TriggerType", Setting::TypeInt) = (int)trig->getTriggerType();
		SetTrigger.add("Threshold", Setting::TypeInt) = (int)trig->getThreshold();
		SetTrigger.add("DynamicTriggerPercent", Setting::TypeInt) = (int)trig->getDynamicTriggerPercent();
		SetTrigger.add("ControllerResolution", Setting::TypeInt) = (int)trig->getControllerResolution();
		SetTrigger.add("PositionalSensing", Setting::TypeInt) = (int)trig->HasController();
		SetTrigger.add("MuteGroup", Setting::TypeInt) = (int)trig->getMuteGroup();
		SetTrigger.add("CrossTalkGroup", Setting::TypeInt) = (int)trig->getCrossTalkGroup();
		SetTrigger.add("FixedMaskTime", Setting::TypeInt) = (int)trig->getFixedMaskTime();
		SetTrigger.add("MaxValue", Setting::TypeInt) = (int)trig->getMaxValue();
		SetTrigger.add("FootSplashSensitivity", Setting::TypeInt) = (int)trig->getFootSplashSensitivity();
		SetTrigger.add("SignalCurveType", Setting::TypeInt) = (int)trig->getSignalCurve()->getCurveType();

		if (trig->getSignalCurve()->getCurveType() == SignalCurve::Curve_Custom ){
			SetTrigger.add("CurvePoints", Setting::TypeList) ;

			// Add the Points list :
			Setting &CurvePointList=SetTrigger["CurvePoints"];
			std::vector<CurvePoint*> *m_curvePoints;

			m_curvePoints=trig->getSignalCurve()->getAllCurvePoints();

			for (unsigned int c=0; c < m_curvePoints->size(); c++){
				CurvePointList.add(Setting::TypeInt) = (int)(*m_curvePoints)[c]->yValue;
			}
		}

	}

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
		m_Echofilter->setParams(tmpDelay , 0.1f);
		myAudioEngine.setGlobalFilter(0, m_Echofilter);
	}else{
		myAudioEngine.setGlobalFilter(0, NULL);
	}
}

int Settings::getVolume() const {
	return m_Volume;
}

void Settings::setVolume(int volume) {
	if (volume>32) volume=32;
	if (volume<0) volume=0;
	float tmpVolume=(float)volume/32;
	m_Volume = volume;
	myAudioEngine.setGlobalVolume(tmpVolume);
}

int Settings::getAlsaBufferSize() const {
	return m_AlsaBufferSize;
}


void Settings::setAlsaBufferSize(int bufferSize) {
	m_AlsaBufferSize=bufferSize;

	// Deinit the audio engine :
	myAudioEngine.deinit();

	// Reinit the audio engine :
	myAudioEngine.init(1, 0,0, m_AlsaBufferSize);

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

				loadKit->setNumTriggerInput(m_numTriggerInputs);

				if (loadKit->loadDrumKitFromConfigFile(KitDir + fileName)){
					// add the drumkit to the list
					m_drumKitList->push_back(loadKit);
				}
				else{
					// Delete the drumkit : it is not valid !
					delete loadKit;
				}
			}
		}
		closedir(dir);
	}else{
		cout << "Error opening folder " + KitDir << endl;
	}

	// Finished : debug some info about instrument loaded count :
	cerr << "Finished scanning folder. " << m_drumKitList->size() << " Drum kits successfully loaded." << endl << endl;

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
				if (loadInstr->loadInstrumentFromConfig(instrumentDir + folderName + "/", "instrument.cfg")){
					// add the instrument to the list
					m_instrumentList->push_back(loadInstr);
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

	// Sort the Instrument List :
	std::sort(m_instrumentList->begin(), m_instrumentList->end(), InstrumentCompare());

	// Finished : debug some info about instrument loaded count :
	cerr << "Finished scanning folder. " << m_instrumentList->size() << " instrument successfully loaded." << endl << endl;

}


Instrument* Settings::getNextInstrument(Instrument *currentInstrument){
	string currentInstrName;
	if (currentInstrument==NULL){
		return (*m_instrumentList)[0];
	}
	currentInstrName=currentInstrument->getInstrumentName();
	// Scroll the list from the begining, when we find our current instrument, returns the next one if exist
	for(unsigned int i=0 ; i<m_instrumentList->size() ; i++){
		if ((*m_instrumentList)[i]->getInstrumentName() == currentInstrName){
			if (i<m_instrumentList->size()-1){
				return (*m_instrumentList)[i+1];
			}
		}
	}
	return NULL;
}

Instrument* Settings::getPreviousInstrument(Instrument *currentInstrument){
	string currentInstrName;
	if (currentInstrument==NULL){
		return (*m_instrumentList)[0];
	}
	currentInstrName=currentInstrument->getInstrumentName();
	// Scroll the list from the begining, when we find our current instrument, returns the previous one if exist
	for(unsigned int i=0 ; i<m_instrumentList->size() ; i++){
		if ((*m_instrumentList)[i]->getInstrumentName() == currentInstrName){
			if (i>0){
				return (*m_instrumentList)[i-1];
			}
		}
	}
	return NULL;

}


DrumKit *Settings::getNextDrumKit(DrumKit *currentDrumKit){
	string currentDrumKitName;
	if (currentDrumKit==NULL){
		if (m_drumKitList->size()>0){
			return (*m_drumKitList)[0];
		}else{
			return NULL;
		}
	}
	currentDrumKitName=currentDrumKit->getKitName();
	// Scroll the list from the begining, when we find our current instrument, returns the next one if exist
	for(unsigned int i=0 ; i<m_drumKitList->size() ; i++){
		if ((*m_drumKitList)[i]->getKitName() == currentDrumKitName){
			if (i<m_drumKitList->size()-1){
				return (*m_drumKitList)[i+1];
			}
		}
	}
	return NULL;
}

DrumKit *Settings::getPreviousDrumKit(DrumKit *currentDrumKit){
	string currentDrumKitName;
	if (currentDrumKit==NULL){
		return (*m_drumKitList)[0];
	}
	currentDrumKitName=currentDrumKit->getKitName();
	// Scroll the list from the begining, when we find our drumkit, returns the previous one if exist
	for(unsigned int i=0 ; i<m_drumKitList->size() ; i++){
		if ((*m_drumKitList)[i]->getKitName() == currentDrumKitName){
			if (i>0){
				return (*m_drumKitList)[i-1];
			}
		}
	}
	return NULL;

}


bool Settings::loadDrumKit(DrumKit *drumKit){

	std::vector<DrumKitComponent*> *newDKCL, *oldDKCL;
	bool instrFound;
	DrumKitComponent *oDK, *nDK;

	// Return if given drumkit is null :
	if (drumKit==NULL){
		return false;
	}

	newDKCL=drumKit->getDkComponentList();

	// Go here only if we already loaded a kit.
	if (m_currentDrumKit!=NULL){
		oldDKCL=m_currentDrumKit->getDkComponentList();

		// First ,  Scan the current drumkit for instruments that are not needed anymore (not included in current drumkit)
		for (unsigned int o=0; o<oldDKCL->size();o++){
			instrFound=false;
			oDK=(*oldDKCL)[o];
			for (unsigned int n=0; n<newDKCL->size();n++){
				nDK=(*newDKCL)[n];
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
	}


	// Then load missing instruments :
	for (unsigned int n=0; n<newDKCL->size();n++){
		// Get a pointer to the DrumKitComponent :
		nDK=(*newDKCL)[n];
		if (nDK->getChoosenInstrument()!=NULL && !nDK->getChoosenInstrument()->isLoaded()){
			// Load only if the instrument is not already loaded !
			nDK->getChoosenInstrument()->loadInstrumentSamples();
		}
	}

	m_currentDrumKit=drumKit;

	return true;
}


DrumKit *Settings::GetDrumKitFromName(std::string drumKitName){
	// search for the drumkit in loaded kits, and assign it to the current one :


	for (unsigned int i=0; i<m_drumKitList->size(); i++){
		if ((*m_drumKitList)[i]->getKitName() == drumKitName){
			return (*m_drumKitList)[i];
		}
	}
	return NULL;
}

std::string Settings::getUserDirectory(){
	string userDir;

	struct passwd *pw = getpwuid(getuid());

	userDir = pw->pw_dir;
	return userDir;
}

std::vector<Instrument*>  *Settings::getInstrumentList()  {
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

std::vector<DrumKit*> *Settings::getDrumKitList(){
	return m_drumKitList;
}

Trigger *Settings::getLastHitTrigger(){
	return m_LastHitTrigger;
}

void Settings::setLastHitTrigger(Trigger *lastHitTrigger) {
	m_LastHitTrigger = lastHitTrigger;
}

float Settings::getGlobalFadeOutTime() const {
	return m_GlobalFadeOutTime;
}

void Settings::setGlobalFadeOutTime(float globalFadeOutTime) {
	m_GlobalFadeOutTime = globalFadeOutTime;
}

bool Settings::isPlaySampleOnSettingChange() const {
	return m_playSampleOnSettingChange;
}

void Settings::setPlaySampleOnSettingChange(bool playSampleOnSettingChange) {
	m_playSampleOnSettingChange = playSampleOnSettingChange;
}

bool Settings::isRotaryKnobReversed() const {
	return m_rotaryKnobReversed;
}

void Settings::setRotaryKnobReversed(bool rotaryKnobReversed) {
	m_rotaryKnobReversed = rotaryKnobReversed;
}

void Settings::fillTriggerList(){
	std::stringstream triggerName;

	for (unsigned int i=0; i< m_numTriggerInputs; i++){
		Trigger *newTrig;
		newTrig=new Trigger();

		triggerName.str("");
		triggerName << "Trigger " << (i+1);
		newTrig->setInputNumber(i);

		newTrig->setTriggerName(triggerName.str());
		m_TriggerList->push_back(newTrig);
	}

}

std::vector<Trigger*>* Settings::getTriggerList(){
	return m_TriggerList;
}

int Settings::getRotaryAction() const {
	return m_RotaryAction;
}

void Settings::setRotaryAction(int rotaryAction) {
	m_RotaryAction = rotaryAction;
}
