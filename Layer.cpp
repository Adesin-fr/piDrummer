/*
 * Layer.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "Layer.h"

Layer::Layer() {
	m_minVelocity=0;
	m_maxVelocity=127;
	wavSample = NULL;
}

Layer::~Layer() {
	delete wavSample;
	wavSample = NULL;
}


const std::string& Layer::getFileName() const {
	return m_fileName;
}

void Layer::setFileName(const std::string& fileName) {
	m_fileName = fileName;
}


unsigned int Layer::getMaxVelocity() const {
	return m_maxVelocity;
}

void Layer::setMaxVelocity(unsigned int maxVelocity) {
	m_maxVelocity = maxVelocity;
}

unsigned int Layer::getMinVelocity() const {
	return m_minVelocity;
}

void Layer::setMinVelocity(unsigned int minVelocity) {
	m_minVelocity = minVelocity;
}

void Layer::loadSample() {
	std::cerr << "Going to load sample file " << m_fileName << std::endl;

	wavSample=new SoLoud::Wav;

	wavSample->load(m_fileName.c_str());
}


void Layer::unloadSample(){
	delete wavSample;
	wavSample = NULL;
}

SoLoud::Wav  *Layer::getWavSample() {
	return wavSample;
}

