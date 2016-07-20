/*
 * AudioEngine.h
 *
 *  Created on: 7 juil. 2016
 *      Author: ludovic
 */

#include "soloud.h"
#include "soloud_wav.h"

#ifndef AUDIOENGINE_H_
#define AUDIOENGINE_H_

class AudioEngine {
	public:
		AudioEngine();
		virtual ~AudioEngine();

	private:
		SoLoud::Soloud slaEngine;  // SoLoud engine core

};

#endif /* AUDIOENGINE_H_ */
