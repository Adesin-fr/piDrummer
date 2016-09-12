/*
 * SerialEvent.h
 *
 *  Created on: 13 juil. 2016
 *      Author: ludovic
 */

#ifndef SERIALHANDLE_H_
#define SERIALHANDLE_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <linux/serial.h>
#include <linux/ioctl.h>
#include <asm/ioctls.h>
#include <sys/select.h>

#include "DrumKit.h"

class SerialHandle {
public:
	SerialHandle(std::string serialDevice, int baudRate);
	SerialHandle();
	virtual ~SerialHandle();

	unsigned int handleEvents(DrumKit *currentDrumKit);
	bool initSerial();
	void sendParameter(unsigned int TriggerNumber, std::string ParameterCode, int ParameterValue);
	void sendString(std::string serialString);

private:
	int m_serPort;

	std::string m_SerialPort;
	std::string m_serialDataLine;
	int baudrate;

	struct termios newtio;
	struct serial_struct ser_info;
	bool m_serPortOpened;
};

#endif /* SERIALHANDLE_H_ */
