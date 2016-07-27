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
}


unsigned int Trigger::getCrossTalkGroup() const {
	return m_crossTalkGroup;
}

void Trigger::setCrossTalkGroup(unsigned int crossTalkGroup) {
	m_crossTalkGroup = crossTalkGroup;
}

unsigned int Trigger::getDynamicTriggerPercent() const {
	return m_dynamicTriggerPercent;
}

void Trigger::setDynamicTriggerPercent(unsigned int dynamicTriggerPercent) {
	m_dynamicTriggerPercent = dynamicTriggerPercent;
}

unsigned int Trigger::getFootSplashSensitivity() const {
	return m_footSplashSensitivity;
}

void Trigger::setFootSplashSensitivity(unsigned int footSplashSensitivity) {
	m_footSplashSensitivity = footSplashSensitivity;
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
}

unsigned int Trigger::getMuteGroup() const {
	return m_muteGroup;
}

void Trigger::setMuteGroup(unsigned int muteGroup) {
	m_muteGroup = muteGroup;
}


unsigned int Trigger::getRetriggerDelay() const {
	return m_retriggerDelay;
}

void Trigger::setRetriggerDelay(unsigned int retriggerDelay) {
	m_retriggerDelay = retriggerDelay;
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
}

unsigned int Trigger::getTriggerType() const {
	return m_triggerType;
}

void Trigger::setTriggerType(unsigned int triggerType) {
	m_triggerType = triggerType;
}

const std::string& Trigger::getTriggerName() const {
	return m_triggerName;
}

void Trigger::setTriggerName(const std::string& triggerName) {
	m_triggerName = triggerName;
}

unsigned int Trigger::getInputNumber() const {
	return m_InputNumber;
}

void Trigger::setInputNumber(unsigned int inputNumber) {
	m_InputNumber = inputNumber;
}
