/*
 * ControllerLayer.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "ControllerLayer.h"

ControllerLayer::ControllerLayer() {
	// TODO Auto-generated constructor stub
	m_minControllerValue=0;
	m_maxControllerValue=127;

}

ControllerLayer::~ControllerLayer() {
	// TODO Auto-generated destructor stub
}

Layer* ControllerLayer::getLayerFromVelocity(unsigned char &velocity){

	for(unsigned int i(0);i<m_layers.size();i++) {

		Layer *tmpLayer;

		tmpLayer=m_layers[i];

		if (tmpLayer->getMinVelocity() <= velocity  && velocity  <= tmpLayer->getMaxVelocity() ){

			return tmpLayer;
		}
	};
	return NULL;
}

void ControllerLayer::loadSamples(){
	for (unsigned int i=0; i<m_layers.size(); i++){
		m_layers[i]->loadSample();
	}
}

void ControllerLayer::unloadSamples(){
	for (unsigned int i=0; i<m_layers.size(); i++){
		m_layers[i]->UnloadSample();
	}
}
