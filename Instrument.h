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
#include <sys/stat.h>

#include "ControllerLayer.h"
#include "soloud_wav.h"

class Instrument {
	public:
		Instrument();
		virtual ~Instrument();
		SoLoud::Wav* getSampleForVelocity(unsigned int velocity);
		bool loadInstrumentFromConfig(std::string Path, std::string configFileName);

		void loadInstrumentSamples();
		void unloadInstrumentSamples();

		bool isLoaded() const;
		unsigned int getControllerValue() const;
		void setControllerValue(unsigned int controllerValue);
		unsigned int getCurrentPlayingSample() const;
		void setCurrentPlayingSample(unsigned int currentPlayingSample);
		const std::string& getInstrumentName() const;
		void setInstrumentName(const std::string& instrumentName);


	private:
		std::string m_instrumentName;
		std::vector<ControllerLayer*> m_ctlLayers;
		unsigned int m_controllerValue;
		unsigned int m_currentPlayingSample;
		bool loaded;

		// Private functions :
		ControllerLayer* getControllerLayerFromVelocity(unsigned int &velocity);
};

#endif /* INSTRUMENT_H_ */
