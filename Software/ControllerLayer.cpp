/*
 * ControllerLayer.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "ControllerLayer.h"

using namespace std;

ControllerLayer::ControllerLayer() {

	m_minControllerValue=0;
	m_maxControllerValue=127;

}

ControllerLayer::~ControllerLayer() {
	// Delete layer objects :

	for(unsigned int i(0);i<m_layers.size();i++) {

		Layer *tmpLayer;

		tmpLayer=m_layers[i];

		delete tmpLayer;
	}

}

Layer* ControllerLayer::getLayerFromVelocity(unsigned int velocity){

	for(unsigned int i(0);i<m_layers.size();i++) {

		Layer *tmpLayer;

		tmpLayer=m_layers[i];

		if (tmpLayer->getMinVelocity() <= velocity  && velocity  <= tmpLayer->getMaxVelocity() ){

			return tmpLayer;
		}
	}

	if(m_layers.size()>0){
		// if no layer found for value, return the last from array...
		return m_layers[m_layers.size()-1];
	}
	// If no layers , return null
	return NULL;
}

void ControllerLayer::loadSamples(){
	for (unsigned int i=0; i<m_layers.size(); i++){
		m_layers[i]->loadSample();
	}
}

void ControllerLayer::unloadSamples(){

	for (unsigned int i=0; i<m_layers.size(); i++){
		m_layers[i]->unloadSample();
	}
}
