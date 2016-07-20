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

}

Layer::~Layer() {
}

bool Layer::LoadSample(){
	if (m_fileName.empty()){
		return false;
	}
	const char * fileName = m_fileName.c_str();
	//TODO : check if the file exists and it is valid ?
	wavSample.load(fileName);

	return true;
}
