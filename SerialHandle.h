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
#include <string>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <linux/serial.h>
#include <linux/ioctl.h>
#include <asm/ioctls.h>
#include "ScreenDrawing.h"

#include "DrumKit.h"

class SerialHandle {
public:
	SerialHandle(std::string serialDevice, int baudRate);
	SerialHandle();
	virtual ~SerialHandle();

	unsigned int handleEvents(DrumKit *currentDrumKit);
	bool initSerial();
	void sendParameter(int TriggerNumber, int ParameterNumber, int ParameterValue);

	void setScreenDrawingReference(ScreenDrawing *ScreenDrawerRef);


private:
	int  m_serPort;
	std::string m_SerialPort;
	std::string m_serialDataLine;
	int baudrate;

	struct termios oldtio, newtio;
	struct serial_struct ser_info;
	bool m_serPortOpened;

	ScreenDrawing *mySDreference;
};

#endif /* SERIALHANDLE_H_ */
