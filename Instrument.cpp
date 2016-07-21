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
	// TODO Auto-generated destructor stub
}

 SoLoud::Wav& Instrument::getSampleForVelocity(unsigned char &velocity){
	// Call to the ControllerLayer to get the Layer from the current controller Value:
	ControllerLayer *tmpCtl = this->getControllerLayerFromVelocity(m_controllerValue);

	if (tmpCtl==0){
		cerr << "Aucun controlleur trouvé pour la valeur " << m_controllerValue << endl;
	}

	Layer* tmpLayer(tmpCtl->getLayerFromVelocity(velocity));

	if (tmpLayer==0){
		cerr << "Aucun Layer trouvé pour la valeur " << m_controllerValue << endl;
	}

	return tmpLayer->getWavSample();


}

ControllerLayer* Instrument::getControllerLayerFromVelocity(unsigned int &velocity){

	for(unsigned int i(0);i<m_ctlLayers.size();i++) {

		ControllerLayer *tmpCtl;

		tmpCtl=m_ctlLayers[i];

		if (tmpCtl->getMinControllerValue()  <= m_controllerValue  && m_controllerValue  <= tmpCtl->getMaxControllerValue() ){

			return tmpCtl;
		}
	};
	return NULL;
}

bool Instrument::loadInstrumentFromConfig(std::string configFileName){
	Config m_cfg;

	try {
		m_cfg.readFile(configFileName.c_str());
	} catch (const FileIOException &fioex) {
		cerr << "I/O error while reading file " << configFileName << endl;
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
    	// Instanciate a new ControllerLayer :
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
        	currentLayer.lookupValue("filename", fileName);

        	ctlLayer->addLayer(tmpMinVelocity, tmpMaxVelocity, fileName);
        }

        m_ctlLayers.push_back(ctlLayer);


    }

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

const std::vector<ControllerLayer*>& Instrument::getCtlLayers() const {
	return m_ctlLayers;
}

void Instrument::setCtlLayers(const std::vector<ControllerLayer*>& ctlLayers) {
	m_ctlLayers = ctlLayers;
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
	//TODO : load samples
	for (unsigned int i=0; i<m_ctlLayers.size(); i++){
		m_ctlLayers[i]->loadSamples();
	}
	loaded=true;
}
