/*
 * Instrument.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "Instrument.h"

using namespace std;
using namespace libconfig;

Instrument::Instrument() {

	m_controllerValue=127;
	m_currentPlayingSample=0;
	loaded=false;

}

Instrument::~Instrument() {
	ControllerLayer *tmpCtl;
	for(unsigned int i(0);i<m_ctlLayers.size();i++) {
		tmpCtl=m_ctlLayers[i];
		delete tmpCtl;
	};
}

 SoLoud::Wav* Instrument::getSampleForVelocity(unsigned int velocity){
	// Call to the ControllerLayer to get the Layer from the current controller Value:
	ControllerLayer *tmpCtl = this->getControllerLayerFromVelocity(m_controllerValue);

	if (tmpCtl==0){
		cerr << "(instr " << m_instrumentName << ") Aucun controlleur trouvé pour la valeur de controleur  " << m_controllerValue << endl;
	}

	Layer* tmpLayer(tmpCtl->getLayerFromVelocity(velocity));

	if (tmpLayer==0){
		cerr << "(instr " << m_instrumentName << ") Aucun Layer trouvé pour la valeur de velocity " << velocity << endl;
		return NULL;
	}


	return tmpLayer->getWavSample();


}

ControllerLayer* Instrument::getControllerLayerFromVelocity(unsigned int &velocity){

	ControllerLayer *tmpCtl;

	for(unsigned int i(0);i<m_ctlLayers.size();i++) {

		tmpCtl=m_ctlLayers[i];

		if (tmpCtl->getMinControllerValue()  <= m_controllerValue  && m_controllerValue  <= tmpCtl->getMaxControllerValue() ){

			return tmpCtl;
		}
	}

	return NULL;
}

bool Instrument::loadInstrumentFromConfig(std::string Path, std::string configFileName){
	Config m_cfg;
	string completePath;
	completePath=Path + configFileName;

	// Check if file exists :
	 struct stat buffer;
	 std::string compFile=Path + configFileName;
	 if (stat (compFile.c_str(), &buffer) != 0){
		 return false;
	 }

	try {
		m_cfg.readFile(completePath.c_str());
	} catch (const FileIOException &fioex) {
		cerr << "I/O error while reading file " << completePath << endl;
		return (false);
	} catch (const ParseException &pex) {
		cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
				<< " - " << pex.getError() << endl;
		return (false);
	}

	Setting &root = m_cfg.getRoot();

	// Get Instrument Name :
	root.lookupValue("InstrumentName", m_instrumentName);

	const Setting &ctlLayers = root["ControllerLayers"];

	int ctlLayerCount = ctlLayers.getLength();

    for(int i = 0; i < ctlLayerCount ; ++i){
    	int tmpMinValue(0);
    	int tmpMaxValue(127);
    	const Setting &cfgControllerLayer = ctlLayers[i];
    	// Instantiate a new ControllerLayer :
    	ControllerLayer *ctlLayer= new ControllerLayer();

    	cfgControllerLayer.lookupValue("minControllerValue", tmpMinValue);
    	cfgControllerLayer.lookupValue("maxControllerValue", tmpMaxValue);


    	ctlLayer->setMinControllerValue(tmpMinValue);
    	ctlLayer->setMaxControllerValue(tmpMaxValue);

    	// Read the layers of this controllerLayer :

    	const Setting &Layers = cfgControllerLayer.lookup("layers");
    	int LayerCount = Layers.getLength();
        for(int l = 0; l < LayerCount ; ++l){
        	int tmpMinVelocity(0);
        	int tmpMaxVelocity(127);
        	string fileName("");

        	Setting &currentLayer = Layers[l];

        	currentLayer.lookupValue("minVelocity", tmpMinVelocity);
        	currentLayer.lookupValue("maxVelocity", tmpMaxVelocity);

        	// if we have multiple filenames, we do support RoundRobin,
        	if (currentLayer.exists("filenames")){
            	const Setting &FileNames = currentLayer.lookup("filenames");
            	std::vector<string> v_FileNames;
            	// add samples file names to vector :
            	for (int fn=0; fn< FileNames.getLength(); fn++){
            		v_FileNames.push_back(FileNames[fn]);
            	}

            	ctlLayer->addLayer(tmpMinVelocity, tmpMaxVelocity, Path , v_FileNames);
        	}else{
            	currentLayer.lookupValue("filename", fileName);

            	ctlLayer->addLayer(tmpMinVelocity, tmpMaxVelocity, Path + fileName);
        	}


        }

        m_ctlLayers.push_back(ctlLayer);

    }

	cerr << "Loaded instrument " << Path << endl;

    return true;

}

bool Instrument::isLoaded() const {
	return loaded;
}

unsigned int Instrument::getControllerValue() const {
	return m_controllerValue;
}

void Instrument::setControllerValue(unsigned int controllerValue) {
	m_controllerValue = controllerValue;
}


unsigned int Instrument::getCurrentPlayingSample() const {
	return m_currentPlayingSample;
}

void Instrument::setCurrentPlayingSample(unsigned int currentPlayingSample) {
	m_currentPlayingSample = currentPlayingSample;
}

const std::string& Instrument::getInstrumentName() const {
	return m_instrumentName;
}

void Instrument::setInstrumentName(const std::string& instrumentName) {
	m_instrumentName = instrumentName;
}

void Instrument::loadInstrumentSamples(){

	cerr << "Loading samples for instrument " << m_instrumentName << endl;
	for (unsigned int i=0; i<m_ctlLayers.size(); i++){
		m_ctlLayers[i]->loadSamples();
	}
	loaded=true;

}

void Instrument::unloadInstrumentSamples(){
	cerr << "Unloading samples for instrument " << m_instrumentName << endl;

	for (unsigned int i=0; i<m_ctlLayers.size(); i++){
		m_ctlLayers[i]->unloadSamples();
	}
	loaded=false;
}
