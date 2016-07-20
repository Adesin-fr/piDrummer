/*
 * SerialEvent.cpp
 *
 *  Created on: 13 juil. 2016
 *      Author: ludovic
 */

#include "SerialHandle.h"


using namespace std;

SerialHandle::SerialHandle() {

	m_serPort=0;
	m_serPortOpened=false;

	m_SerialPort="";
	baudrate =115200;
	SerialHandle(m_SerialPort, baudrate );
	mySDreference=NULL;
}


SerialHandle::SerialHandle(std::string serialDevice="", int baudRate=115200) {

	m_serPort=0;
	m_serPortOpened=false;

	m_SerialPort=serialDevice;
	baudrate = baudRate;
	mySDreference=NULL;
}

SerialHandle::~SerialHandle() {
	// TODO Auto-generated destructor stub
}

bool SerialHandle::initSerial(){
	// Initialize the serial Port :

	if (m_SerialPort==""){
		cerr << "Serial device not defined ! Please set it in config file. " << m_SerialPort << endl;
		return false;
	}

	m_serPort = open(m_SerialPort.c_str(), O_RDWR | O_NOCTTY );

	if (m_serPort < 0)
	{
		cerr << "Error opening serial device " << m_SerialPort << endl;
		m_serPortOpened=false;
		return false;
	}

	/* save current serial port settings */
	tcgetattr(m_serPort, &oldtio);

	/* clear struct for new port settings */
	bzero(&newtio, sizeof(newtio));

	/*
	 * BAUDRATE : Set bps rate. You could also use cfsetispeed and cfsetospeed.
	 * CRTSCTS  : output hardware flow control (only used if the cable has
	 * all necessary lines. See sect. 7 of Serial-HOWTO)
	 * CS8      : 8n1 (8bit, no parity, 1 stopbit)
	 * CLOCAL   : local connection, no modem contol
	 * CREAD    : enable receiving characters
	 */
	newtio.c_cflag = baudrate | CS8 | CLOCAL | CREAD; // CRTSCTS removed

	/*
	 * IGNPAR  : ignore bytes with parity errors
	 * ICRNL   : map CR to NL (otherwise a CR input on the other computer
	 * will not terminate input)
	 * otherwise make device raw (no other input processing)
	 */
	newtio.c_iflag = IGNPAR;

	/* Raw output */
	newtio.c_oflag = 0;

	/*
	 * ICANON  : enable canonical input
	 * disable all echo functionality, and don't send signals to calling program
	 */
	newtio.c_lflag = 0; // non-canonical

	/*
	 * set up: we'll be reading 4 bytes at a time.
	 */
	newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
	newtio.c_cc[VMIN]     = 1;     /* blocking read until n character arrives */

	/*
	 * now clean the modem line and activate the settings for the port
	 */
	tcflush(m_serPort, TCIFLUSH);
	tcsetattr(m_serPort, TCSANOW, &newtio);

	m_serPortOpened=true;
	return true;
}


unsigned int SerialHandle::handleEvents(DrumKit *currentDrumKit){

	unsigned char triggerNumber, triggerVelocity, triggerPosition, triggerValue ;
	char nextData[1];

	while (m_serPortOpened && read(m_serPort, nextData, 1)){

		m_serialDataLine+=nextData;

		//Is the line over ?
		if (nextData[0] == '\n'){
			// Yes,  handle it !
			switch(m_serialDataLine[0]){
			case 1:
				// "Trigger" Event :

				// Check the message length first !
				if (m_serialDataLine.size()!=5){
					break;
				}

				triggerNumber  = m_serialDataLine[1];
				triggerVelocity = m_serialDataLine[2];
				triggerPosition = m_serialDataLine[3];

				cerr << "Received Trigger Event : " << endl;
				cerr << "   Trigger number   : " << triggerNumber << endl;
				cerr << "   Trigger velocity : " << triggerVelocity << endl;
				cerr << "   Trigger position : " << triggerPosition << endl;

				// Find in the current drumKit if the corresponding trigger is mapped:
				currentDrumKit->playInstrumentForTriggerInput(triggerNumber, triggerVelocity, triggerPosition);

				return 1;

				break;
			case 2:
				// Controller Change Event:

				// Check the message length first !
				if (m_serialDataLine.size()!=4){
					break;
				}

				triggerNumber  = m_serialDataLine[1];
				triggerValue = m_serialDataLine[2];

				cerr << "Received Controller Change Event : " << endl;
				cerr << "   Trigger number    : " << triggerNumber << endl;
				cerr << "   Trigger new value : " << triggerValue << endl;

				currentDrumKit->setNewControllerValue(triggerNumber, triggerValue);

				return 1;

				break;
			case 3:
				// After-Touch, i.e. Cymbal Choke

				// Check the message length first !
				if (m_serialDataLine.size()!=4){
					break;
				}

				triggerNumber  = m_serialDataLine[1];
				triggerValue = m_serialDataLine[2];

				cerr << "Received After touch Event : " << endl;

				cerr << "   Trigger number    : " << triggerNumber << endl;
				cerr << "   Trigger new value : " << triggerValue << endl;

				currentDrumKit->setAfterTouchValue(triggerNumber, triggerValue);

				return 1;

				break;
			case 4:
				// Key inputs from arduino (rotary, push buttons,...)
				if (m_serialDataLine.size()!=4){
					// We wait only 4 bytes :
					// first is event type (already used up there,
					// Second is key pushed (MSB)
					// third is key pushed (LSB)
					// Fourth is line feed
					break;
				}

				return ((m_serialDataLine[1]*256) + m_serialDataLine[2]);

				break;
			}
			// Reset line so we do not use it again
			m_serialDataLine="";
		} // End if line is over

	} // End of While isDataAvailable
	// No data available, return 0.
	return 0;
}

void SerialHandle::sendParameter(int TriggerNumber, int ParameterNumber, int ParameterValue){

}

void SerialHandle::setScreenDrawingReference(ScreenDrawing *ScreenDrawerRef){
	mySDreference=ScreenDrawerRef;
}
