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
	sampleLoaded=false;
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

bool Layer::loadSample() {
	// Using libsndfile to load files ...
	SF_INFO sound_info;
	wavSample=new SoLoud::Wav;
	SNDFILE* file;

	wavSample->load(m_fileName.c_str());
	sampleLoaded=true;
	return true;

	//TODO : bad behavior with libsndfile !!!
	/*

	// Open file, and get file info in struct :
	file = sf_open( m_fileName.c_str(), SFM_READ, &sound_info );
	if (!file){
		cerr << "Error opening file : " << sf_strerror(file) << endl;
		return false;
	}

	if (sound_info.channels>1){
//		cerr << "Sample has " << sound_info.channels << " but only 1 is supported. Going to take only first. " << std::endl;
	}

	if ( sound_info.frames > ( std::numeric_limits<int>::max()/sound_info.channels ) ) {
		cerr << "Sample is too long. it will be truncated. " << std::endl;
		sound_info.frames = ( std::numeric_limits<int>::max()/sound_info.channels );
	}

	// Set a buffer :
	float* buffer = new float[ sound_info.frames ];

	// if we got more than 2 channels, do the conversion :
	if (sound_info.channels >1){
		// Set a temporary buffer :
		float* tmpBuffer = new float[ sound_info.frames * sound_info.channels];
		sf_read_float( file, tmpBuffer, sound_info.frames * sound_info.channels );

		for (unsigned int i =0; i< sound_info.frames ; i++){
			// Pick only the first channel :
			buffer[i]=tmpBuffer[i*sound_info.channels];
		}
		// delete the tmpBuffer
		delete tmpBuffer;
	}else{
		sf_read_float( file, buffer, sound_info.frames );
	}

	sf_close( file );

	wavSample->mData=buffer;
	wavSample->mSampleCount=sound_info.frames * sound_info.channels;
	wavSample->mBaseSamplerate=sound_info.samplerate;

	sampleLoaded=true;

	return true;
	*/
}


void Layer::unloadSample(){
	if (sampleLoaded){
		// Release the buffer data :
		delete wavSample;
		wavSample = NULL;
	}
}

SoLoud::Wav  *Layer::getWavSample() {
	if (sampleLoaded){
		return wavSample;
	}else{
		return NULL;
	}
}

