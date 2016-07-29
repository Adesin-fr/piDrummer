/*
 * Layer.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#ifndef LAYER_H_
#define LAYER_H_

#include <string>
#include <limits>
#include <iostream>

#include "soloud_wav.h"
#include <sndfile.hh>

#define BUFFER_LEN 1024

class Layer {
	public:
		Layer();
		virtual ~Layer();

		const std::string& getFileName() const;
		void setFileName(const std::string& fileName);
		unsigned int getMaxVelocity() const;
		void setMaxVelocity(unsigned int maxVelocity);
		unsigned int getMinVelocity() const;
		void setMinVelocity(unsigned int minVelocity);
		void loadSample();
		void unloadSample();
		SoLoud::Wav *getWavSample();


	private:
		unsigned int m_minVelocity;
		unsigned int m_maxVelocity;
        std::string m_fileName;
        SoLoud::Wav *wavSample;

};

#endif /* LAYER_H_ */
