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
}


SerialHandle::SerialHandle(std::string serialDevice="", int baudRate=115200) {

	m_serPort=0;
	m_serPortOpened=false;

	m_SerialPort=serialDevice;
	baudrate = baudRate;
}

SerialHandle::~SerialHandle() {
	// Close the serial port cleanly !
	close(m_serPort);
}

bool SerialHandle::initSerial(){
	// Initialize the serial Port :

	if (m_SerialPort==""){
		cerr << "Serial device not defined ! Please set it in config file. " << m_SerialPort << endl;
	return false;
	}

	cerr << "Opening serial port " << m_SerialPort << endl;

	m_serPort = open(m_SerialPort.c_str(), O_RDWR | O_NOCTTY );

	if (m_serPort < 0){
		cerr << "Error opening serial device " << m_SerialPort << endl;
		m_serPortOpened=false;
		return false;
	}else{
		cerr << "Serial port " << m_SerialPort  << "  opened !" << endl;
	}

	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = B115200 | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;


	newtio.c_cc[VTIME]=0;
	newtio.c_cc[VMIN]=1;

	tcflush(m_serPort, TCIFLUSH);
	tcsetattr(m_serPort, TCSANOW, &newtio);

	m_serPortOpened=true;
	return true;
}


unsigned int SerialHandle::handleEvents(DrumKit *currentDrumKit){

	unsigned int triggerNumber, triggerVelocity, triggerPosition, triggerValue ;

	unsigned char nextData[32];
	int n;

	fd_set input;
	struct timeval timeout;

	FD_ZERO(&input);
	FD_SET(m_serPort, &input);

	// Block for only 50 ms :
	timeout.tv_sec = 0;
	timeout.tv_usec = 50000;

	n = select(m_serPort + 1,  &input, NULL, NULL, &timeout ) ;

	if (n<=0){
		// No data has arrived within timeout...
		return 0;
	}



	while (m_serPortOpened && read(m_serPort, nextData, 1)){

		m_serialDataLine+=nextData[0];

		//Is the line over ?
		if (m_serialDataLine[m_serialDataLine.size()-1] == 10){


			// Yes,  handle it !
			if (m_serialDataLine.size()<5){
				return 0;
			}

			switch(m_serialDataLine[0]){
			case 1:
				// "Trigger" Event :

				// Check the message length first !

				triggerNumber  = m_serialDataLine[1];
				triggerVelocity = m_serialDataLine[2];
				triggerPosition = m_serialDataLine[3];

				// Find in the current drumKit if the corresponding trigger is mapped:
				if (currentDrumKit==NULL){
					cerr << " No current drumkit ! "<< endl;
				}
				currentDrumKit->playInstrumentForTriggerInput(triggerNumber, triggerVelocity, triggerPosition);

				m_serialDataLine="";
				return 1;

				break;
			case 2:
				// Controller Change Event:

				triggerNumber  = m_serialDataLine[1];
				triggerValue = m_serialDataLine[2];

				cerr << "Received Controller Change Event : " << endl;
				cerr << "   Trigger number    : " << triggerNumber << endl;
				cerr << "   Trigger new value : " << triggerValue << endl;

				currentDrumKit->setNewControllerValue(triggerNumber, triggerValue);

				m_serialDataLine="";
				return 1;

				break;
			case 3:
				// After-Touch, i.e. Cymbal Choke


				triggerNumber  = m_serialDataLine[1];
				triggerValue = m_serialDataLine[2];

				cerr << "Received After touch Event : " << endl;

				cerr << "   Trigger number    : " << triggerNumber << endl;
				cerr << "   Trigger new value : " << triggerValue << endl;

				currentDrumKit->setAfterTouchValue(triggerNumber, triggerValue);

				m_serialDataLine="";
				return 1;

				break;
			case 4:
				// Key inputs from arduino (rotary, push buttons,...)
				unsigned int keyVal;
				keyVal=((m_serialDataLine[1]*255) + m_serialDataLine[2]);
				cerr << "   Received key value : " << keyVal << endl;

				m_serialDataLine="";
				return keyVal;

				break;
			}
			// Reset line so we do not use it again
		} // End if line is over

	} // End of While isDataAvailable
	// No data available, return 0.

	return 0;
}

void SerialHandle::sendParameter(unsigned int TriggerNumber, string ParameterCode, int ParameterValue){
	/*
	 * Message format :
	 * TTPPVVVV
	 * TT = Trigger Number
	 * PP = Parameter Code
	 * VVVV = Parameter Value (variable length)
	 */

	std::stringstream myItoA;
	string outString;

	myItoA << "TP" << std::setw(2) << std::setfill('0') <<  TriggerNumber << ParameterCode << ParameterValue << endl;
	outString=myItoA.str();

	// Send string to serial port.

	if (m_serPortOpened==true){

		cerr << "Send Serial data: " << outString << endl;

		write( m_serPort, outString.c_str(), outString.size() );
	}

	cerr << "Send Serial data finished "<< endl;

}

void SerialHandle::sendString(string serialString){
	if (m_serPortOpened==true){

		cerr << "Send Serial data: " << serialString << endl;
		write( m_serPort, serialString.c_str(), serialString.size() );
		cerr << "Send Serial data finished "<< endl;
	}


}
