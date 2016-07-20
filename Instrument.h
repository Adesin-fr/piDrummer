/*
 * Instrument.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

#include <vector>
#include <string>
#include <libconfig.h++>
#include <list>
#include <iostream>
#include "ControllerLayer.h"
#include "soloud_wav.h"


class Instrument {
	public:
		Instrument();
		virtual ~Instrument();
		SoLoud::Wav& getSampleForVelocity(unsigned char &velocity);

	unsigned int getCurrentPlayingSample() const {
		return m_currentPlayingSample;
	}

	void setCurrentPlayingSample(unsigned int currentPlayingSample) {
		this->m_currentPlayingSample = currentPlayingSample;
	}

	unsigned int getControllerValue() const {
		return m_controllerValue;
	}

	void setControllerValue(unsigned int controllerValue) {
		m_controllerValue = controllerValue;
	}

	const std::string& getInstrumentName() const {
		return m_instrumentName;
	}

	void setInstrumentName(const std::string& instrumentName) {
		m_instrumentName = instrumentName;
	}


	bool loadInstrumentFromConfig(std::string configFileName);

	void loadInstrumentSamples();

	void unloadInstrumentSamples();


	private:
		std::string m_instrumentName;
		std::vector<ControllerLayer*> m_ctlLayers;
		unsigned int m_controllerValue;
		unsigned int m_currentPlayingSample;

		// Private functions :
		ControllerLayer* getControllerLayerFromVelocity(unsigned int &velocity);
};

#endif /* INSTRUMENT_H_ */
