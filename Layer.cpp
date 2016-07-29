/*
 * Layer.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "Layer.h"

using namespace std;

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
	// Using libsndfile to load files ...
	SF_INFO sound_info;
	wavSample=new SoLoud::Wav;
	SNDFILE* file;

	std::cerr << "Going to load sample file " << m_fileName << std::endl;

	// Open file, and get file info in struct :
	file = sf_open( m_fileName.c_str(), SFM_READ, &sound_info );
	if (!file){
		cerr << "Error opening file : " << sf_strerror(file) << endl;
	}

	if (sound_info.channels>1){
		cerr << "Sample has " << sound_info.channels << " but only 1 is supported. Going to take only first. " << std::endl;
		sound_info.channels=1;
	}

	if ( sound_info.frames > ( std::numeric_limits<int>::max()/sound_info.channels ) ) {
		cerr << "Sample is too long. it will be truncated. " << std::endl;
		sound_info.frames = ( std::numeric_limits<int>::max()/sound_info.channels );
	}

	// Set a buffer :
	float* buffer = new float[ sound_info.frames ];

	sf_read_float( file, buffer, sound_info.frames * sound_info.channels );

	sf_close( file );

	wavSample->mData=buffer;
	wavSample->mSampleCount=sound_info.frames * sound_info.channels;
	wavSample->mBaseSamplerate=sound_info.samplerate;

}


void Layer::unloadSample(){
	delete wavSample;
	wavSample = NULL;
}

SoLoud::Wav  *Layer::getWavSample() {
	return wavSample;
}

