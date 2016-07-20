/*
 * Trigger.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#include "Instrument.h"

#ifndef TRIGGER_H_
#define TRIGGER_H_

class Trigger {
	public:
		Trigger();
		virtual ~Trigger();


	unsigned int getCrossTalkGroup() const {
		return m_crossTalkGroup;
	}

	void setCrossTalkGroup(unsigned int crossTalkGroup) {
		m_crossTalkGroup = crossTalkGroup;
	}

	unsigned int getDynamicTriggerPercent() const {
		return m_dynamicTriggerPercent;
	}

	void setDynamicTriggerPercent(unsigned int dynamicTriggerPercent) {
		m_dynamicTriggerPercent = dynamicTriggerPercent;
	}

	unsigned int getFootSplashSensitivity() const {
		return m_footSplashSensitivity;
	}

	void setFootSplashSensitivity(unsigned int footSplashSensitivity) {
		m_footSplashSensitivity = footSplashSensitivity;
	}

	bool isHasController() const {
		return m_hasController;
	}

	void setHasController(bool hasController) {
		m_hasController = hasController;
	}

	unsigned int getControllerResolution() const {
		return m_ControllerResolution;
	}

	void setControllerResolution(unsigned int ControllerResolution) {
		m_ControllerResolution = ControllerResolution;
	}

	bool isIsChoked() const {
		return m_isChoked;
	}

	void setIsChoked(bool isChoked) {
		m_isChoked = isChoked;
	}


	unsigned int getLastVelocity() const {
		return m_lastVelocity;
	}

	void setLastVelocity(unsigned int lastVelocity) {
		m_lastVelocity = lastVelocity;
	}

	unsigned int getMuteGroup() const {
		return m_muteGroup;
	}

	void setMuteGroup(unsigned int muteGroup) {
		m_muteGroup = muteGroup;
	}


	unsigned int getRetriggerDelay() const {
		return m_retriggerDelay;
	}

	void setRetriggerDelay(unsigned int retriggerDelay) {
		m_retriggerDelay = retriggerDelay;
	}

	unsigned int getSignalCurve() const {
		return m_signalCurve;
	}

	void setSignalCurve(unsigned int signalCurve) {
		m_signalCurve = signalCurve;
	}

	unsigned int getThreshold() const {
		return m_threshold;
	}

	void setThreshold(unsigned int threshold) {
		m_threshold = threshold;
	}

	unsigned int getTriggerType() const {
		return m_triggerType;
	}

	void setTriggerType(unsigned int triggerType) {
		m_triggerType = triggerType;
	}

	const std::string& getTriggerName() const {
		return m_triggerName;
	}

	void setTriggerName(const std::string& triggerName) {
		m_triggerName = triggerName;
	}

	unsigned int getInputNumber() const;
	void setInputNumber(unsigned int inputNumber);

	private:
		unsigned int m_triggerType;
		std::string m_triggerName;
		unsigned int m_lastVelocity;
		bool m_hasController;
		bool m_isChoked;
		unsigned int m_signalCurve;
		unsigned int m_threshold;
		unsigned int m_muteGroup;
		unsigned int m_crossTalkGroup;
		unsigned int m_retriggerDelay;
		unsigned int m_dynamicTriggerPercent;
		unsigned int m_footSplashSensitivity;
		unsigned int m_ControllerResolution;
		unsigned int m_InputNumber;

};

#endif /* TRIGGER_H_ */
