#include <Arduino.h>
#include <EEPROM.h>
#include "piDrummer.h"
#include "encoder.h"

/*
 * POWER Button behavior :
 * 		When we power the arduino, we are on standby mode. > MOSFET is OFF, POWER LED is OFF
 *		If we push the power button :
 *			turn ON the MOSFET
 *			blink the LED until the OrangePI sends "ready status" and get parameters
 *		If we push the button before ready status : do nothing
 *		If we push the button after ready status :
 * 			blink led while not ready to poweroff (a few seconds)
 *			send POWEROFF event to OrangePI
 *			wait a few seconds and MOSFET OFF
 *		If receive a POWEROFF event from OrangePI :
 *			do POWEROFF sequence.
 *
 * TODO :
 * - Handle serial inputs to set parameters for each trigger.
	"CT",m_crossTalkGroup);
	"DT",m_dynamicTriggerPercent);
	"FS",m_footSplashSensitivity);
	"CR",m_ControllerResolution);
	"MG",m_muteGroup);
	"MT",m_FixedMaskTime);
	"TH",m_threshold);
	"TT",m_triggerType);
	"MV",m_maxValue);
 *
 * - Cymbal 3 zones w/ Chocke :  ?
 * 		> Voir fichier cy-15r.gif pour cablage & principe
 * 			3 entrées :
 * 			> 1 piezo = velocité
 * 			> 1 switch bell / 1 switch underside (choke) en parallele
 * 				> Maintient appuyé sur switch = choke
 * 			> 1 switch edge
 *
 * 		> Frappe courte sur switch bell/edge = envoi note bell/edge
 *
 * - Pour les entrées SWITCH : activer resistance PULL-UP : digitalWrite(A0, HIGH);
 * - Parametre par entree : type PAD / SWITCH
 * - FAIRE UN TEST AVEC TOUTES LES PULLUP ?
 * - Implement HiHat "Chicks" (record time between pedal value variation )
 * - Implement Cross-Talk groups (i.e. for cymbal dual zone handling)
 */

Trigger trigArray[NB_ANALOG_CHANNELS];

int anaRead=0;
int lastHitRawValue;
byte midiVelocity=0;
byte lastHitTrigger=0;
byte HiHatPedalChannel=16;
byte HiHatCymbalChannel=17;
byte HiHatValue=0;
byte prevHiHatValue;
bool isPowerON=false;
bool isOPiReady=false;
bool PowerLedState=false;
bool PowerOffAsked=false;
unsigned long lastPowerButtonPress=0;
unsigned long lastPowerLedBlinkTime=0;
unsigned long PowerOffAskTime=0;
unsigned int encoder0Pos = 0;
int oldEncoderPos = 0;

void setup() {
	Serial.begin(115200);

	// Faster ADC readings :
	setADCSampleRate();


	pinMode(MUXER_AD0, OUTPUT)   ; // Muxer address select PINs
	pinMode(MUXER_AD1, OUTPUT)   ; // Muxer address select PINs
	pinMode(MUXER_AD2, OUTPUT)   ; // Muxer address select PINs
	pinMode(encoderPinA, INPUT_PULLUP);
	pinMode(encoderPinB, INPUT_PULLUP);
	pinMode(EnterPushButton, INPUT_PULLUP);
	pinMode(EscapePushButton, INPUT_PULLUP);
	pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);


		/*
		// Perform auto-threshold

		// Read each channel 20 times, sum the values, then divide them to get the average value:
		long readValue[NB_ANALOG_CHANNELS];
		for (int i=1; i<=NB_ANALOG_CHANNELS; i++){
			readValue[i]=0;
		}

		for (int count=0; count<20; count++) {
			for (int i=0; i<NB_ANALOG_CHANNELS; i++){
				// Read the channel and add th result to the array :
				byte tempValue=readChannel(i);
				readValue[i]+=tempValue;
				// Wait 10 ms between each channel reading...
				delay (10);
			}
		}

		// Once we're done with readings, divide the values and store them in config :
		for (int i=0; i<NB_ANALOG_CHANNELS; i++){
			// Read the channel and add th result to the array :
			if (i != HiHatPedalChannel){
				// Don't apply threshold to hihat channel
				byte tempValue=readValue[i] / 20;
				trigArray[i].thresHold = tempValue;
			}
		}
		*/



		for (int i=0; i<NB_ANALOG_CHANNELS; i++){

			trigArray[i].thresHold = 25;
			trigArray[i].debounce=20;
			trigArray[i].DynamicThreshold=20;
			trigArray[i].maxValue=1023;
		}


}




void loop() {


		doAnalogReadings();

		// Deal with Encoder values :
		HandleEncoderChange();

	// Deal with trigger events only if OPi is Ready !
	if (isOPiReady){

		// Deal with Encoder values :
		HandleEncoderChange();

		// Deal with inputs :
		doAnalogReadings();

		// Reset Threshold values :
		ResetThresholdValues();
	}

	// Handle POWER button  :
	if (lastPowerButtonPress+100 < millis() && digitalRead(POWER_BUTTON_PIN)==LOW){
		Serial.println("Pow !");
		lastPowerButtonPress = millis();
		// Button was pressed : do something !
		if (isPowerON==false){
			// We are not powered , let's go ON !
			isPowerON=true;
			// Turn on the led...
			PowerLedState=true;
			digitalWrite(POWER_MOSFET_PIN, HIGH);
			digitalWrite(POWER_LED_PIN, PowerLedState);
		}else{
			// We are powered , let's go OFF (if we can...)
			// If we are powered ON, but the OrangiPI is not ready, do nothing...
			if (isOPiReady){
				isOPiReady=false;
				PowerOffAsked=true;
				// Since isOpiReady==false AND isPowerON==true, the LED should start blinking !
				// Send the OPi a signal to ask him shut-off...
				// Equivalent to F12 key value !
				serialOut(MSGTYPE_KEYPRESS_VALUE, 255, 38, 0);
			}
		}
	}

	// Should we blink the led ?
	if (isPowerON && !isOPiReady && lastPowerLedBlinkTime+1000 < millis()){
			PowerLedState=!PowerLedState;
			digitalWrite(POWER_LED_PIN, PowerLedState);
	}

	// Should we shut power to the oPi ?
	if (PowerOffAskTime+10000 < millis() && PowerOffAsked==true){
		PowerOffAsked=false;
		isPowerON=false;
		// Switch off power supply now :
		digitalWrite(POWER_MOSFET_PIN, LOW);
	}

}
