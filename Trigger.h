/*
 * Trigger.h
 *
 *  Created on: 6 juil. 2016
 *      Author: ludovic
 */

#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "SignalCurve.h"
#include <string>


class Trigger {
	public:
		Trigger();
		virtual ~Trigger();


		unsigned int getCrossTalkGroup() const;
		void setCrossTalkGroup(unsigned int crossTalkGroup);
		unsigned int getDynamicTriggerPercent() const;
		void setDynamicTriggerPercent(unsigned int dynamicTriggerPercent);
		unsigned int getFootSplashSensitivity() const;
		void setFootSplashSensitivity(unsigned int footSplashSensitivity);
		bool HasController() const;
		void setHasController(bool hasController);
		unsigned int getControllerResolution() const;
		void setControllerResolution(unsigned int ControllerResolution);
		bool isChoked() const;
		void setChoked(bool isChoked);
		unsigned int getLastVelocity() const;
		void setLastVelocity(unsigned int lastVelocity);
		unsigned int getMuteGroup() const;
		void setMuteGroup(unsigned int muteGroup);
		unsigned int getRetriggerDelay() const;
		void setRetriggerDelay(unsigned int retriggerDelay);
		SignalCurve *getSignalCurve();
		void setSignalCurve(SignalCurve *signalCurve);
		unsigned int getThreshold() const;
		void setThreshold(unsigned int threshold);
		unsigned int getTriggerType() const;
		void setTriggerType(unsigned int triggerType);
		const std::string& getTriggerName() const;
		void setTriggerName(const std::string& triggerName);
		unsigned int getInputNumber() const;
		void setInputNumber(unsigned int inputNumber);

	private:
		unsigned int m_triggerType;
		std::string m_triggerName;
		unsigned int m_lastVelocity;
		bool m_hasController;
		bool m_isChoked;
		SignalCurve *m_signalCurve;
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
