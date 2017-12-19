#ifndef ENCODER_H_
#define ENCODER_H_

#include <Arduino.h>
#include "piDrummerPins.h"
#include "piDrummer.h"

extern unsigned int encoder0Pos;
extern int oldEncoderPos;

unsigned long LastEncoderSendTime;
unsigned long LastEncoderPushTime;
unsigned long LastEscapePushTime;

long encoder0PinALast;


void doEncoderA(){

  // look for a low-to-high on channel A
  if (digitalRead(encoderPinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void doEncoderB(){

  // look for a low-to-high on channel B
  if (digitalRead(encoderPinB) == HIGH) {
   // check channel A to see which way encoder is turning
    if (digitalRead(encoderPinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void HandleEncoderChange(){
	int n;



	 n = digitalRead(encoderPinA);
	   if ((encoder0PinALast == LOW) && (n == HIGH)) {
	     if (digitalRead(encoderPinB) == LOW) {
	       encoder0Pos++;
	     } else {
	       encoder0Pos--;
	     }
	   }
	   encoder0PinALast = n;


	if (encoder0Pos != oldEncoderPos && LastEncoderSendTime + 200 < millis()){
		LastEncoderSendTime=millis();
		byte lValue;
		// Get delta :
		int delta= encoder0Pos-oldEncoderPos;

		// Reset old value to current one !
		oldEncoderPos=encoder0Pos;

		// if previous value != current one, we moved, send key presses events
		if (delta>0){
			// Send N RIGHT key events
			lValue=20;	// RIGHT KEY value is 275 : 255 is MSB and 20 is LSB
		}else if (delta<0){
			delta=-delta;
			lValue=21;	// LEFT KEY value is 276 : 255 is MSB and 21 is LSB
			// Send N LEFT key events
		}

		for (int i=0; i<delta; i++){
			serialOut(MSGTYPE_KEYPRESS_VALUE, 1, lValue, 0 );
		}

	}


	// Encoder push button pressed ?
	if (LastEncoderPushTime + 200 < millis() && digitalRead(EnterPushButton)==LOW){
		LastEncoderPushTime=millis();
		// Send "ENTER" key value
		serialOut(MSGTYPE_KEYPRESS_VALUE, 0, 13, 0 );
	}

	// ESCAPE push button pressed ?
	if (LastEscapePushTime + 200 < millis() && digitalRead(EscapePushButton)==LOW){
		LastEscapePushTime=millis();
		// Send "ESCAPE " key value
		serialOut(MSGTYPE_KEYPRESS_VALUE, 0, 27, 0);
	}

	// Play/pause button : value = 112

}

#endif	/* ENCODER_H_ */
