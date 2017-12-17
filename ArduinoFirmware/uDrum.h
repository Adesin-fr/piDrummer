#include <avr/pgmspace.h>

#define NB_ANALOG_CHANNELS 2
//#define NB_ANALOG_CHANNELS 32

#define MUXER_AD0 10
#define MUXER_AD1 11
#define MUXER_AD2 12
// TODO : put old values !
// #define encoderPinA 2
// #define encoderPinB 3
#define encoderPinA 2
#define encoderPinB 3
#define EnterPushButton 4
#define EscapePushButton 5

#define POWER_BUTTON_PIN 6
#define POWER_LED_PIN 7
#define POWER_MOSFET_PIN 8

#define MSGTYPE_TRIGGER_VALUE 1
#define MSGTYPE_CONTROL_VALUE 2
#define MSGTYPE_AFTERTOUCH_VALUE 3
#define MSGTYPE_KEYPRESS_VALUE 4


// Setting ADC frequency reading :
// To disable, just comment the following line :
// Only one of 4 lines must be un-commented ! 
// If more than 1 is uncommented, only last one will be used.
// BEWARE that setting a higher frequency than 1MHZ can cause ADC reading errors.
//

// #define ADC_500KHZ 1
#define ADC_1MHZ 1
// #define ADC_2MHZ 1
// #define ADC_4MHZ 1

// Prototypes : 
void serialOut(byte MessageType, byte InputNumber, byte MessageValue, byte Modifier);


struct Trigger {
	long lastRead;
	byte thresHold;
	byte debounce;
	byte DynamicThreshold;
	long previousReadValue;
	bool rising;
	long maxValue;
	bool thresHoldNeedReset;
	byte SetupThresHold;
	long lastZeroTime;
};

extern Trigger trigArray[NB_ANALOG_CHANNELS];
extern byte HiHatPedalChannel;
extern byte HiHatCymbalChannel;
extern int anaRead;
extern int lastHitRawValue;

extern byte HiHatValue;
extern byte prevHiHatValue;
extern byte lastHitTrigger;
extern bool lcdNeedRefresh;
extern byte midiVelocity;


/*
 *
 *  Analog stuff :
 *
*/

long readChannel(byte ChanNumber){
	long val=0;
	/* 
	 *  Each Analog Input have a CD4051 tied
	 *  When we need to switch the channel input, we do it for all CD4015, 
	 *  and then we read the correct input .
	 *  Since we got 8 input channels * 8 CD4051 = 64 total input triggers !
	 */

	digitalWrite(MUXER_AD0, bitRead(ChanNumber,0));
	digitalWrite(MUXER_AD1, bitRead(ChanNumber,1));
	digitalWrite(MUXER_AD2, bitRead(ChanNumber,2));

	// The CD4051 takes 720ns max (0.72µs) to switch channel, so let's wait a bit (a microsecond should be enought) :
	delayMicroseconds(1);

	// Do stuff to switch CD4051 channels :
	if (ChanNumber<8){
		val = analogRead(A0);
	}else if (ChanNumber<16){
		val = analogRead(A1);
	}else if (ChanNumber<24){
		val = analogRead(A2);
	}else if (ChanNumber<32){
		val = analogRead(A3);
	}else if (ChanNumber<40){
		val = analogRead(A4);
	}else if (ChanNumber<48){
		val = analogRead(A5);
	}else if (ChanNumber<56){
		val = analogRead(A6);
	}else{
		val = analogRead(A7);
	}

	return val;
}



void doAnalogReadings(){
	
	for (int i=0; i<NB_ANALOG_CHANNELS; i++){
//	for (int i=0; i<1; i++){
		if (i == HiHatPedalChannel){
			// Read the hihat channel different way:
			anaRead = readChannel(i) ;
			// 32 steps is faaaaaaar enought for a hihat pedal !
			HiHatValue = map ( anaRead, 0, 1024, 0, 32);
			// Remap to 127 values
			HiHatValue = map ( HiHatValue , 0, 32, 0, 127);
			if (prevHiHatValue != HiHatValue){
				prevHiHatValue = HiHatValue;
				// Send MIDI CC 
//				serialOut(MSGTYPE_CONTROL_VALUE, i, HiHatValue);
			}
		}else{
				// Read the value of the input:
				anaRead = readChannel(i) ;


				if (anaRead > trigArray[i].thresHold) {
						// Seems we did passed the end of peak, so send the previousReadValue :
					if (trigArray[i].previousReadValue > anaRead && trigArray[i].rising==true){

						if (millis() > trigArray[i].lastRead + trigArray[i].debounce){

							// Since we passed the peak , keep the timestamp for retriggering
							trigArray[i].lastRead=millis();
							lastHitRawValue = trigArray[i].previousReadValue;

							if (anaRead > trigArray[i].maxValue){
								trigArray[i].maxValue= anaRead ;
							}
							
							// Set the dynamic threshold 
							trigArray[i].thresHold=trigArray[i].previousReadValue*trigArray[i].DynamicThreshold/100;
							trigArray[i].thresHoldNeedReset=true;
	

							// TODO : Should we send RAW values and parse them on oPi side ?

							midiVelocity = map ( trigArray[i].previousReadValue, 0, trigArray[i].maxValue, 0, 127);
							if (midiVelocity==0){
								midiVelocity=1;
							}
							if (midiVelocity>127){
								midiVelocity=127;
							}
							
							serialOut(MSGTYPE_TRIGGER_VALUE, i, midiVelocity, 127);
/*
							Serial.print("New Thr : ");
							Serial.print(trigArray[i].thresHold);
							
							Serial.print(" Vel : ");
							Serial.print(midiVelocity);

							Serial.print(" An : ");
							Serial.print(anaRead);

							Serial.print(" Pv : ");
							Serial.print(trigArray[i].previousReadValue);
							
							Serial.print(" Pk time : ");
							// Calculate peak delay time : difference between last zero value and now.
							long pk = (micros() - trigArray[i].lastZeroTime)/100;
							Serial.println(pk);
*/

							lastHitTrigger=i;
							trigArray[i].rising=false;
						}

					}else if (trigArray[i].previousReadValue < anaRead){
						// last value is smaller than current, We're rising !:
						trigArray[i].rising=true;

					}

					// Store the previous read value, to compare to the next value.
					trigArray[i].previousReadValue = anaRead;
				}else{
					trigArray[i].lastZeroTime=micros();
					trigArray[i].previousReadValue =0;
				}
		}
		
	}
}

void ResetThresholdValues(){
			// Set the dynamic threshold 
	for (int i=1; i<=NB_ANALOG_CHANNELS; i++){
		if (trigArray[i].thresHoldNeedReset==true && millis() > trigArray[i].lastRead){
			trigArray[i].thresHold=trigArray[i].SetupThresHold;
			trigArray[i].thresHoldNeedReset=false;
		}
	}
}



void serialOut(byte MessageType, byte InputNumber, byte MessageValue, byte Modifier){
	Serial.write(MessageType);
	Serial.write(InputNumber);
	Serial.write(MessageValue);
	Serial.write(Modifier);
	Serial.write(0x0A); 		// Message END
}


void setADCSampleRate(){


	// defines for setting and clearing register bits
	#ifndef cbi
		#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
	#endif
	#ifndef sbi
		#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
	#endif

	#ifdef ADC_500KHZ
		// set prescale to 32
		sbi(ADCSRA,ADPS2) ;
		cbi(ADCSRA,ADPS1) ;
		sbi(ADCSRA,ADPS0) ;
	#endif


	#ifdef ADC_1MHZ
		// set prescale to 16
		sbi(ADCSRA,ADPS2) ;
		cbi(ADCSRA,ADPS1) ;
		cbi(ADCSRA,ADPS0) ;
	#endif

	#ifdef ADC_2MHZ
		// set prescale to 8
		cbi(ADCSRA,ADPS2) ;
		sbi(ADCSRA,ADPS1) ;
		sbi(ADCSRA,ADPS0) ;
	#endif

	#ifdef ADC_4MHZ
		// set prescale to 4
		cbi(ADCSRA,ADPS2) ;
		sbi(ADCSRA,ADPS1) ;
		cbi(ADCSRA,ADPS0) ;
	#endif

}
