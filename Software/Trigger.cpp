/*
 * Trigger.cpp
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "Trigger.h"

Trigger::Trigger() {
	m_ControllerResolution=16;
	m_InputNumber=0;
	m_dynamicTriggerPercent=20;
	m_crossTalkGroup=0;
	m_threshold=0;
	m_signalCurve=new SignalCurve();
	m_isChoked=false;
	m_hasController=false;
	m_triggerType=Trigger::TT_PadCenter;
	m_footSplashSensitivity=4;
	m_FixedMaskTime=10;
	m_muteGroup=0;
	m_lastVelocity=0;
	m_lastTimeHit=0;
	m_maxValue=1024;
}

Trigger::~Trigger() {
	delete m_signalCurve;
}


unsigned int Trigger::getCrossTalkGroup() const {
	return m_crossTalkGroup;
}

void Trigger::setCrossTalkGroup(unsigned int crossTalkGroup) {
	m_crossTalkGroup = crossTalkGroup;
	sendSerialParameter(m_InputNumber,"CT",m_crossTalkGroup);
}

unsigned int Trigger::getDynamicTriggerPercent() const {
	return m_dynamicTriggerPercent;
}

void Trigger::setDynamicTriggerPercent(unsigned int dynamicTriggerPercent) {
	m_dynamicTriggerPercent = dynamicTriggerPercent;
	sendSerialParameter(m_InputNumber,"DT",m_dynamicTriggerPercent);
}

unsigned int Trigger::getFootSplashSensitivity() const {
	return m_footSplashSensitivity;
}

void Trigger::setFootSplashSensitivity(unsigned int footSplashSensitivity) {
	m_footSplashSensitivity = footSplashSensitivity;
	sendSerialParameter(m_InputNumber,"FS",m_footSplashSensitivity);
}

bool Trigger::HasController() const {
	return m_hasController;
}

void Trigger::setHasController(bool hasController) {
	m_hasController = hasController;
}

unsigned int Trigger::getControllerResolution() const {
	return m_ControllerResolution;
}

void Trigger::setControllerResolution(unsigned int ControllerResolution) {
	m_ControllerResolution = ControllerResolution;
	sendSerialParameter(m_InputNumber,"CR",m_ControllerResolution);
}

bool Trigger::isChoked() const {
	return m_isChoked;
}

void Trigger::setChoked(bool isChoked) {
	m_isChoked = isChoked;
}


unsigned int Trigger::getLastVelocity() const {
	return m_lastVelocity;
}

void Trigger::setLastVelocity(unsigned int lastVelocity) {
	m_lastVelocity = lastVelocity;
	m_lastTimeHit=ticksNow;
}

unsigned int Trigger::getMuteGroup() const {
	return m_muteGroup;
}

void Trigger::setMuteGroup(unsigned int muteGroup) {
	m_muteGroup = muteGroup;
	sendSerialParameter(m_InputNumber,"MG",m_muteGroup);
}


unsigned int Trigger::getFixedMaskTime() const {
	return m_FixedMaskTime;
}

void Trigger::setFixedMaskTime(unsigned int retriggerDelay) {
	m_FixedMaskTime = retriggerDelay;
	sendSerialParameter(m_InputNumber,"MT",m_FixedMaskTime);

}

SignalCurve *Trigger::getSignalCurve() {
	return m_signalCurve;
}

void Trigger::setSignalCurve(SignalCurve *signalCurve) {
	m_signalCurve = signalCurve;
}

unsigned int Trigger::getThreshold() const {
	return m_threshold;
}

void Trigger::setThreshold(unsigned int threshold) {
	m_threshold = threshold;
	sendSerialParameter(m_InputNumber,"TH",m_threshold);
}

unsigned int Trigger::getTriggerType() const {
	return m_triggerType;
}

void Trigger::setTriggerType(unsigned int triggerType) {
	m_triggerType = triggerType;
	sendSerialParameter(m_InputNumber,"TT",m_triggerType);
}

std::string Trigger::getTriggerName() {
	return m_triggerName;
}

void Trigger::setTriggerName(std::string triggerName) {
	m_triggerName = triggerName;
}

unsigned int Trigger::getInputNumber() const {
	return m_InputNumber;
}

void Trigger::setInputNumber(unsigned int inputNumber) {
	m_InputNumber = inputNumber;
}

unsigned int Trigger::getMaxValue() const {
	return m_maxValue;
}

void Trigger::setMaxValue(unsigned int maxValue) {
	m_maxValue = maxValue;
	sendSerialParameter(m_InputNumber,"MV",m_maxValue);
}

unsigned int Trigger::getLastTimeHit() const {
	return m_lastTimeHit;
}

void Trigger::setLastTimeHit(unsigned int lastTimeHit) {
	m_lastTimeHit = lastTimeHit;
}
