/*
 * Layer.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#ifndef LAYER_H_
#define LAYER_H_

#include <string>
#include "soloud_wav.h"
#include <iostream>


class Layer {
	public:
		Layer();
		virtual ~Layer();
		bool LoadSample();

	const std::string& getFileName() const {
		return m_fileName;
	}

	void setFileName(const std::string& fileName) {
		m_fileName = fileName;
	}


	unsigned int getMaxVelocity() const {
		return m_maxVelocity;
	}

	void setMaxVelocity(unsigned int maxVelocity) {
		m_maxVelocity = maxVelocity;
	}

	unsigned int getMinVelocity() const {
		return m_minVelocity;
	}

	void setMinVelocity(unsigned int minVelocity) {
		m_minVelocity = minVelocity;
	}

	void loadSample() {
		std::cerr << "Going to load sample file " << m_fileName << std::endl;
		wavSample.load(m_fileName.c_str());
	}


	SoLoud::Wav& getWavSample() {
		return wavSample;
	}

	private:
		unsigned int m_minVelocity;
		unsigned int m_maxVelocity;
        std::string m_fileName;
        SoLoud::Wav wavSample;

};

#endif /* LAYER_H_ */
