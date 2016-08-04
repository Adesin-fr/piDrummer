/*
 * ControllerLayer.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#ifndef CONTROLLERLAYER_H_
#define CONTROLLERLAYER_H_


#include <vector>
#include "Layer.h"

class ControllerLayer {
	public:
		ControllerLayer();
		virtual ~ControllerLayer();
		Layer* getLayerFromVelocity(unsigned int velocity);

	unsigned int getMaxControllerValue() const {
		return m_maxControllerValue;
	}

	void setMaxControllerValue(unsigned int maxControllerValue) {
		m_maxControllerValue = maxControllerValue;
	}

	unsigned int getMinControllerValue() const {
		return m_minControllerValue;
	}

	void setMinControllerValue(unsigned int minControllerValue) {
		m_minControllerValue = minControllerValue;
	}

	void addLayer(unsigned int minVelocity, unsigned int maxVelocity, std::string fileName) {
		Layer *newLayer(0);

		newLayer = new Layer();

		newLayer->setMinVelocity(minVelocity);
		newLayer->setMaxVelocity(maxVelocity);
		newLayer->setFileName(fileName);

		m_layers.push_back(newLayer);
	}

	void loadSamples();
	void unloadSamples();

	private:
        unsigned int m_minControllerValue;
        unsigned int m_maxControllerValue;
        std::vector<Layer*> m_layers;


};

#endif /* CONTROLLERLAYER_H_ */
