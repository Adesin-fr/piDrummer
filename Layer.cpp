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

	// Open file, and get file info in struct :
	file = sf_open( m_fileName.c_str(), SFM_READ, &sound_info );
	if (!file){
		cerr << "Error opening file : " << sf_strerror(file) << endl;
		return false;
	}


	if ( sound_info.frames > ( std::numeric_limits<int>::max()/sound_info.channels ) ) {
		cerr << "Sample is too long. it will be truncated. " << std::endl;
		sound_info.frames = ( std::numeric_limits<int>::max()/sound_info.channels );
	}


	if (sound_info.channels >2){
		// TODO : handle samples with more than 2 channels
		cerr << "Cannot load more than 2 channels for sample " << m_fileName << ". Aborting." << endl;
		return false;
	}

	// Set a buffer :
	float* buffer = new float[ sound_info.frames  * sound_info.channels];
	sf_read_float( file, buffer, sound_info.frames * sound_info.channels);
	sf_close( file );

	// if more than 1 channel, reorder data correctly :
	// We need to have values for first channel first, then second, etc... :
	// ex : 	  L,L,L,L,L,L,L,L,L,L,L,R,R,R,R,R,R,R,R,R,R,R
	// instead of L,R,L,R,L,R,L,R,L,R,L,R,L,R,L,R,L,R,L,R,L,R
	if (sound_info.channels>1){
		float* newBuffer = new float[ sound_info.frames  * sound_info.channels];

		for (unsigned int i=0; i< sound_info.frames ; i++){
			for (int ch=0; ch< sound_info.channels; ch++){
				// Destination = sound_info.frames * ch + i
				newBuffer[sound_info.frames * ch + i] = buffer[i*sound_info.channels+ch];
			}
		}

		// destroy old buffer:
		delete[] buffer;

		// assign data to wav object :
		wavSample->mData=newBuffer;
	}else{
		wavSample->mData=buffer;
	}

	wavSample->mChannels=sound_info.channels;
	wavSample->mSampleCount=sound_info.frames ;
	wavSample->mBaseSamplerate= (float)sound_info.samplerate;

	sampleLoaded=true;

	return true;

}


void Layer::unloadSample(){
	if (sampleLoaded){
		// Release the buffer data :
		delete wavSample;
		wavSample = NULL;
	}
}

SoLoud::Wav *Layer::getWavSample() {
	if (sampleLoaded){
		return wavSample;
	}else{
		return NULL;
	}
}

