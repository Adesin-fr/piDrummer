/*
 * Trigger.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "Trigger.h"

Trigger::Trigger() {
	// TODO Auto-generated constructor stub
	m_ControllerResolution=16;
	m_InputNumber=0;
	m_dynamicTriggerPercent=20;
	m_crossTalkGroup=0;
	m_threshold=0;
	m_signalCurve=0;
	m_isChoked=false;
	m_hasController=false;
	m_triggerType=0;
	m_footSplashSensitivity=0;
	m_retriggerDelay=10;
	m_muteGroup=0;
	m_lastVelocity=0;

}

Trigger::~Trigger() {
	// TODO Auto-generated destructor stub
}

unsigned int Trigger::getInputNumber() const {
	return m_InputNumber;
}

void Trigger::setInputNumber(unsigned int inputNumber) {
	m_InputNumber = inputNumber;
}
