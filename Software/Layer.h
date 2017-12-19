/*
 * Layer.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#ifndef LAYER_H_
#define LAYER_H_

#include <string>
#include <vector>
#include <limits>
#include <iostream>

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include <sndfile.hh>

class Layer {
	public:
		Layer();
		virtual ~Layer();

		void addFileName(const std::string& fileName);
		unsigned int getMaxVelocity() const;
		void setMaxVelocity(unsigned int maxVelocity);
		unsigned int getMinVelocity() const;
		void setMinVelocity(unsigned int minVelocity);
		bool loadSample();
		void unloadSample();
		SoLoud::Wav *getWavSample();


	private:
		unsigned int m_minVelocity;
		unsigned int m_maxVelocity;

        bool sampleLoaded;

        std::vector <SoLoud::Wav*> m_RRSamples;
        std::vector <std::string> m_fileNames;
        unsigned int m_roundRobinIndex;
        unsigned int m_roundRobinItemCount;
};

#endif /* LAYER_H_ */
