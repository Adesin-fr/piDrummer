/*
 * ScreenDrawing.cpp
 *
 *  Created on: 15 juil. 2016
 *      Author: ludovic
 */

#include "ScreenDrawing.h"

using namespace std;
using namespace libconfig;


ScreenDrawing::ScreenDrawing(){

	maxSelectedMenuItem=0;

	refreshFunction=&ScreenDrawing::DrawMainScreen;
	myCurrentMenuPath.push_back("MainScreen");
	myCurrentSelectedMenuItem.push_back(0);
	m_tmpBoolValue=false;
	m_tmpFloatValue=0.0;
	m_tmpIntValue=0;
	m_tmpStringValue="";
	m_SelectedDK=NULL;
	m_SelectedTrigger = NULL;
}


ScreenDrawing::~ScreenDrawing(){
}

void ScreenDrawing::DrawSplashScreen(){

	SDL_Color pi={217, 3, 58, 0 };

	DrawLabel("pi", 30,  100, 200, pi, false );
	DrawLabel("Drummer", 30, 128, 200,  false );
	DrawLabel(piDrummerVersion, 10,  290, 225, false);

	// Draw the logo
   	DrawIcon(myglobalSettings.getUserDirectory() + "/.piDrummer/res/pidrummer_logo.gif", 85, 30);

   	//TODO : fill a progress bar while loading instruments samples.

    SDL_Flip(screen);

}

void ScreenDrawing::DrawIcon(const string iconPath, int posX, int posY){
	SDL_Surface *icon = NULL;
	SDL_Rect  positionIcon;

    if (!myglobalSettings.checkIfFileExists(iconPath)){
//        cerr << "ERROR : icon file  " << iconPath << " missing " << endl;
    	return;
    }


	positionIcon.x=posX;
	positionIcon.y=posY;

	icon = IMG_Load(iconPath.c_str());
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, SDL_MapRGB(icon->format, 0, 0, 0));
	SDL_BlitSurface(icon, NULL, screen, &positionIcon);

	SDL_FreeSurface( icon );
	icon=NULL;
}

void ScreenDrawing::DrawLabel( std::string labelText, int fontSize, int posX, int posY){
	SDL_Color white={255,255,255, 0};
	DrawLabel(labelText, fontSize, posX, posY,  white, false);
}

void ScreenDrawing::DrawLabel( std::string labelText, int fontSize, int posX, int posY, bool selected){
	SDL_Color white={255,255,255, 0};

	DrawLabel(labelText, fontSize, posX, posY, white, selected);
}


void ScreenDrawing::DrawLabel( std::string labelText, int fontSize, int posX, int posY, SDL_Color color){

	DrawLabel(labelText, fontSize, posX, posY, color, false);
}


void ScreenDrawing::DrawLabel( std::string labelText, int fontSize, int posX, int posY, SDL_Color color, bool selected){
	SDL_Rect position;
	SDL_Color invertColor;
	SDL_Surface *texte;
	SDL_Surface *BGSurf;
	TTF_Font *myFont= NULL;

	string fontPath = myglobalSettings.getUserDirectory() + "/.piDrummer/res/arial.ttf";

	myFont = myFontstore.getFont(fontPath, fontSize);

	position.x=posX;
	position.y=posY;



	if (selected){

		invertColor.b=255-color.b;
		invertColor.r=255-color.r;
		invertColor.g=255-color.g;

		texte = TTF_RenderText_Blended(myFont, labelText.c_str(), invertColor);


		BGSurf=SDL_CreateRGBSurface(SDL_HWSURFACE,texte->w, texte->h, 16,0,0,0,0);
		SDL_FillRect(BGSurf, NULL, SDL_MapRGB(BGSurf->format, color.r, color.g, color.b));
		SDL_BlitSurface(BGSurf, NULL, screen, &position); /* Blit background*/

		SDL_FreeSurface( BGSurf );
		BGSurf=NULL;

	}else{
		texte = TTF_RenderText_Blended(myFont, labelText.c_str(), color);
	}

	SDL_BlitSurface(texte, NULL, screen, &position); /* Blit text */

	SDL_FreeSurface( texte );
	texte=NULL;


}


void ScreenDrawing::DrawLabelToList(SDL_Surface *dest, std::string labelText, int fontSize, int posX, int posY, SDL_Color color, bool selected=false){
	SDL_Rect position;
	SDL_Color invertColor;
	SDL_Surface *texte ;
	SDL_Surface *BGSurf;
	TTF_Font *myFont= NULL;

	string fontPath = myglobalSettings.getUserDirectory() + "/.piDrummer/res/arial.ttf";

	myFont = myFontstore.getFont(fontPath, fontSize);

	position.x=posX;
	position.y=posY;



	if (selected){

		invertColor.b=255-color.b;
		invertColor.r=255-color.r;
		invertColor.g=255-color.g;

		texte = TTF_RenderText_Blended(myFont, labelText.c_str(), invertColor);

		BGSurf=SDL_CreateRGBSurface(SDL_HWSURFACE,dest->w, texte->h, 16,0,0,0,0);
		SDL_FillRect(BGSurf, NULL, SDL_MapRGB(BGSurf->format, color.r, color.g, color.b));
		SDL_BlitSurface(BGSurf, NULL, dest, &position); /* Blit background*/

		SDL_FreeSurface( BGSurf );
		BGSurf=NULL;

	}else{
		texte = TTF_RenderText_Blended(myFont, labelText.c_str(), color);
	}

	SDL_BlitSurface(texte, NULL, dest, &position); /* Blit text */

	SDL_FreeSurface( texte );
	texte=NULL;

}



unsigned int ScreenDrawing::handleKeyPress(unsigned int keyEvent){

	string currentScreen;
	unsigned int currentSelectedItem;
	if (myCurrentMenuPath.size()>0){
		currentScreen=myCurrentMenuPath[myCurrentMenuPath.size()-1];
	}else{
		currentScreen="";
	}

	if (myCurrentSelectedMenuItem.size()>0){
		currentSelectedItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];
	}else{
		currentSelectedItem=0;
	}

	switch (keyEvent){
	case SDLK_F12:
		// POWER OFF !
		return 255;
		break;
	case 112:
		// Handle play/pause action whenever we are..
		break;
	case 13:	// ENTER key
		if (currentScreen=="MainScreen"){
			// If we are on main screen, then we go to main menu
			myCurrentMenuPath.push_back("MainMenu");
			myCurrentSelectedMenuItem.push_back(0);
			maxSelectedMenuItem=5;

			// Save the function name to call it later if needed !
			refreshFunction=&ScreenDrawing::DrawMainMenu;
		}else if (currentScreen=="MainMenu"){
				myCurrentSelectedMenuItem.push_back(0);
				switch (currentSelectedItem){
				case 0:	// Kit Select
					// Select the current kit in list :
					for(unsigned int i=0;i < myglobalSettings.getDrumKitList()->size();i++){
						if ((*myglobalSettings.getDrumKitList())[i]->getKitName() == myglobalSettings.getCurrentDrumKit()->getKitName()) {
							myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1]=i;
							break;
						}
					}
					myCurrentMenuPath.push_back("KitSelect");
					refreshFunction=&ScreenDrawing::DrawKitSelect;
					break;
				case 1: // Metronome
					myCurrentMenuPath.push_back("Metronome");
					refreshFunction=&ScreenDrawing::DrawMetronomeSetup;
					break;
				case 2:	// Audio Player
					myCurrentMenuPath.push_back("AudioPlayer");
					refreshFunction=&ScreenDrawing::DrawAudioPlayer;
					break;
				case 3:	// Training
					myCurrentMenuPath.push_back("Training");
					refreshFunction=&ScreenDrawing::DrawTrainingMenu;
					break;
				case 4: // Kit Setup
					myCurrentMenuPath.push_back("KitSetup");
					refreshFunction=&ScreenDrawing::DrawKitSetupMenu;
					break;
				case 5:	// Global Setup
					myCurrentMenuPath.push_back("GlobalSetup");
					refreshFunction=&ScreenDrawing::DrawGlobalSettingsMenu;
					break;
				}
		}else if (currentScreen=="KitSelect"){
			myglobalSettings.loadDrumKit((*myglobalSettings.getDrumKitList())[currentSelectedItem]);
			// and exit to mainscreen (pop 2 times : 1 to go back to main menu, and 1 more to go back to main screen!)
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
			refreshFunction=&ScreenDrawing::DrawMainScreen;

		}else if(currentScreen=="Metronome"){
			// Manage value change !
			myCurrentMenuPath.push_back("MetronomeVal");
			myCurrentSelectedMenuItem.push_back(0);
		}else if (currentScreen=="MetronomeVal"){
			// Confirm value change
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
		}else if (currentScreen=="KitSetup"){
			// Trigger Selected
			myCurrentMenuPath.push_back("KitSetup1");
			myCurrentSelectedMenuItem.push_back(0);
			// Set selected DK Component :
			unsigned int SelectedDKIndex = myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2];
			m_SelectedDK = (*myglobalSettings.getCurrentDrumKit()->getDkComponentList())[SelectedDKIndex];

			refreshFunction=&ScreenDrawing::DrawKitSetupTriggerChoosen;
		}else if(currentScreen=="KitSetup1"){
			// Manage Trigger value change !
			myCurrentMenuPath.push_back("KitSetup1Val");
			myCurrentSelectedMenuItem.push_back(0);
		}else if (currentScreen=="KitSetup1Val"){
			// Confirm value change
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
		}else if (currentScreen == "GlobalSetup"){
			// if we are on 7th element, go to trigger settings
			if (currentSelectedItem==7){
				myCurrentMenuPath.push_back("TriggerSettings");
				myCurrentSelectedMenuItem.push_back(0);
				refreshFunction=&ScreenDrawing::DrawTriggerSettings;
			}else{
				myCurrentMenuPath.push_back("GlobalSetup1");
				myCurrentSelectedMenuItem.push_back(0);
			}
		}else if (currentScreen=="GlobalSetup1" && myCurrentSelectedMenuItem.size()>2 && myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]==6){
			// Copy kit confirmed ! copy the kit :
			DrumKit *copiedDrumKit;
			copiedDrumKit = myglobalSettings.getCurrentDrumKit()->CopyDrumKit();
			// Add it to the list of availables kits :
			std::vector<DrumKit*> *ptrTodrumKitList;
			ptrTodrumKitList=myglobalSettings.getDrumKitList();
			ptrTodrumKitList->push_back(copiedDrumKit);
			// Set the current kit = new kit.
			myglobalSettings.setCurrentDrumKit(copiedDrumKit);

			// Now, go back 3 levels (1> GlobalSetup, 2>Main Menu)
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
			refreshFunction=&ScreenDrawing::DrawMainScreen;

			currentScreen=myCurrentMenuPath[myCurrentMenuPath.size()-1];

		}else if (currentScreen=="GlobalSetup1"){
			// Validate the current setting and go back to global menu
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
		}else if (currentScreen=="TriggerSettings"){
			myCurrentMenuPath.push_back("TriggerSettings1");
			myCurrentSelectedMenuItem.push_back(0);
			// Set selected Trigger :
			unsigned int SelectedTriggerIndex = myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2];
			m_SelectedTrigger = (*myglobalSettings.getTriggerList())[SelectedTriggerIndex];

			// Set draw screen function to setup Trigger
			refreshFunction=&ScreenDrawing::DrawGlobalSetupTriggerChoosen;
		}else if (currentScreen=="TriggerSettings1"){
			myCurrentMenuPath.push_back("TriggerSettingsVal");
			myCurrentSelectedMenuItem.push_back(0);
		}else if (currentScreen=="TriggerSettingsVal"){
			if (myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]==2 && m_SelectedTrigger->getSignalCurve()->getCurveType()==SignalCurve::Curve_Custom){
				// Go to Signal Curve Editing
				myCurrentMenuPath.push_back("SignalCurveEdit");
				myCurrentSelectedMenuItem.push_back(0);
			}else{
				myCurrentMenuPath.pop_back();
				myCurrentSelectedMenuItem.pop_back();
			}
		}else if (currentScreen == "SignalCurveEdit"){
			myCurrentMenuPath.push_back("SignalCurvePointEdit");
			m_tmpIntValue=(*m_SelectedTrigger->getSignalCurve()->getAllCurvePoints())[myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1]]->yValue;
			myCurrentSelectedMenuItem.push_back(m_tmpIntValue);
		}else if (currentScreen == "SignalCurvePointEdit"){
			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();
		}

		break;
	case 27:	// ESCAPE key
		if (currentScreen=="MainScreen"){
			// TODO : what to do with "escape key" when on main screen ?
			refreshFunction=&ScreenDrawing::DrawMainScreen;
		}else{

			string previousMenu = currentScreen;

			cerr << "previousMenu is " << currentScreen << endl;
			cerr << "previousSel is " << currentScreen << endl;

			myCurrentMenuPath.pop_back();
			myCurrentSelectedMenuItem.pop_back();

			currentScreen=myCurrentMenuPath[myCurrentMenuPath.size()-1];

			cerr << "New CurrentScreen is " << currentScreen << endl;


			if (currentScreen=="MainScreen"){
				// Go back to previous menu :
				// Save the function name to call it later if needed !
				refreshFunction=&ScreenDrawing::DrawMainScreen;
			}else if (currentScreen=="MainMenu"){
				// Save the function name to call it later if needed !
				refreshFunction=&ScreenDrawing::DrawMainMenu;
				maxSelectedMenuItem=5;
				if (previousMenu=="KitSetup"){

					// Save the drumkit to file :
					myglobalSettings.getCurrentDrumKit()->saveDrumKitToConfigFile();
				}
			}else if (currentScreen=="KitSetup"){
				// Save the function name to call it later if needed !
				refreshFunction=&ScreenDrawing::DrawKitSetupMenu;
				maxSelectedMenuItem=5;
			}else if (currentScreen=="GlobalSetup"){
				refreshFunction=&ScreenDrawing::DrawGlobalSettingsMenu;
			}else if (currentScreen == "TriggerSettings"){
				refreshFunction=&ScreenDrawing::DrawTriggerSettings;
			}

		}
		break;
	case 276:	// LEFT key
		if (currentScreen=="MainScreen"){
			// If we are on main screen, then we handle special action (
			switch(myglobalSettings.getRotaryAction()){
				case Settings::Rotary_ChangeBPM:
					myMetronome.DecMetronomeBpm(5);
					break;
				case Settings::Rotary_ChangeVolume:
					if(myglobalSettings.getVolume()>0){
						myglobalSettings.setVolume(myglobalSettings.getVolume()-1);
					}
					break;
				case Settings::Rotary_ChangeDrumKit:
					DrumKit *prevDK;
					prevDK=myglobalSettings.getPreviousDrumKit(myglobalSettings.getCurrentDrumKit());
					if (prevDK!=NULL){
						myglobalSettings.loadDrumKit(prevDK);
					}
					break;
			}
		}else if (currentScreen=="MetronomeVal"){
				switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
					case 0:
						myMetronome.DecMetronomeBpm(1);
						break;
					case 1:
						m_tmpIntValue=myMetronome.getMetronomeVolume();
						if (m_tmpIntValue>1){
							myMetronome.setMetronomeVolume(--m_tmpIntValue);
						}
						break;
					case 2:
						m_tmpIntValue=myMetronome.getMetronomeBCount();
						if (m_tmpIntValue>0){
							myMetronome.setMetronomeBCount(--m_tmpIntValue);
						}
						break;
					case 3:
						myMetronome.setMetronomeOn(!myMetronome.isMetronomeOn());
						break;
				}
			}else if (currentScreen=="KitSetup1Val"){
				switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
					case 0:
						// Change instrument !
						// Get next instrument in list
						Instrument *tmpInstr;
						tmpInstr=m_SelectedDK->getChoosenInstrument();
						tmpInstr=myglobalSettings.getPreviousInstrument(m_SelectedDK->getChoosenInstrument());
						if (tmpInstr!=NULL){
							// Clean up instruments to unload those which are not needed anymore
							m_SelectedDK->setChoosenInstrument(tmpInstr);
							tmpInstr->loadInstrumentSamples();

							// Play the sample so we ear what we choose :
							if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);

							myglobalSettings.getCurrentDrumKit()->cleanUpInstrumentSamples();
						}
						break;
					case 1:
						// Change Pitch
						m_tmpFloatValue=m_SelectedDK->getPitch();
						if (m_tmpFloatValue>0.0f){
							m_tmpFloatValue-=0.01f;
							m_SelectedDK->setPitch(m_tmpFloatValue);

							// Play the sample so we ear what we choose :
							if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);
						}
						break;
					case 2:
						// Change Gain
						m_tmpFloatValue=m_SelectedDK->getReplayGain();
						if (m_tmpFloatValue>0.0f){
							m_tmpFloatValue-=0.1f;
							m_SelectedDK->setReplayGain(m_tmpFloatValue);

							// Play the sample so we ear what we choose :
							if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);
						}
						break;
					case 3:
						// Change Balance
						m_tmpFloatValue=m_SelectedDK->getBalance();
						if (m_tmpFloatValue>-1.0f){
							m_tmpFloatValue-=0.1f;
							m_SelectedDK->setBalance(m_tmpFloatValue);

							// Play the sample so we ear what we choose :
							if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);
						}
						break;
				}

			}else if (currentScreen == "GlobalSetup1"){
				switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
					case 0: // Volume
						// Substract 1
						m_tmpIntValue=myglobalSettings.getVolume();
						if (m_tmpIntValue>0){
							myglobalSettings.setVolume(--m_tmpIntValue);
						}
						break;
					case 1: // Instrument fadeout time
						// Substract 0.1s
						m_tmpFloatValue=myglobalSettings.getGlobalFadeOutTime();
						if (m_tmpFloatValue>0.0f){
							m_tmpFloatValue-=0.1f;
							myglobalSettings.setGlobalFadeOutTime(m_tmpFloatValue);
						}
						break;
					case 2:	//Auto poweroff delay
						// Substract 5 minutes (300 seconds)
						m_tmpIntValue=myglobalSettings.getAutoPowerOffDelay();
						if (m_tmpIntValue>0){
							myglobalSettings.setAutoPowerOffDelay(m_tmpIntValue-300);
						}
						break;
					case 3:	// Invert rotary knob :
						// Set value = NOT value
						myglobalSettings.setRotaryKnobReversed(!myglobalSettings.isRotaryKnobReversed());
						break;
					case 4: // Main screen rotary action
						if (myglobalSettings.getRotaryAction()>0){
							myglobalSettings.setRotaryAction(myglobalSettings.getRotaryAction()-1);
						}
						break;
					case 5:	// Play sample on setting change
						// Set value = NOT value
						myglobalSettings.setPlaySampleOnSettingChange(!myglobalSettings.isPlaySampleOnSettingChange());
						break;
				}
			}else if (currentScreen=="TriggerSettingsVal"){
				switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
					case 0:	// trigger Type
						if (m_SelectedTrigger->getTriggerType()>0){
							m_tmpIntValue=m_SelectedTrigger->getTriggerType();
							m_SelectedTrigger->setTriggerType(--m_tmpIntValue);
						}
						break;
					case 1: // threshold
						if (m_SelectedTrigger->getThreshold()>0){
							m_tmpIntValue=m_SelectedTrigger->getThreshold();
							m_SelectedTrigger->setThreshold(--m_tmpIntValue);
						}
						break;
					case 2:	// Signal Curve
						if (m_SelectedTrigger->getSignalCurve()->getCurveType()>0){
								m_tmpIntValue=m_SelectedTrigger->getSignalCurve()->getCurveType();
								m_SelectedTrigger->getSignalCurve()->setCurveType(--m_tmpIntValue);
						}
						break;
					case 3:	// Max Value
						if (m_SelectedTrigger->getMaxValue()>0){
							m_tmpIntValue=m_SelectedTrigger->getMaxValue();
							m_SelectedTrigger->setMaxValue(--m_tmpIntValue);
						}
						break;
					case 4:	// Mute Group
						if (m_SelectedTrigger->getMuteGroup()>0){
							m_tmpIntValue=m_SelectedTrigger->getMuteGroup();
							m_SelectedTrigger->setMuteGroup(--m_tmpIntValue);
						}
						break;
					case 5:	// Xtalk Group
						if (m_SelectedTrigger->getCrossTalkGroup()>0){
							m_tmpIntValue=m_SelectedTrigger->getCrossTalkGroup();
							m_SelectedTrigger->setCrossTalkGroup(--m_tmpIntValue);
						}
						break;
					case 6:	// Fixed Mask Time
						if (m_SelectedTrigger->getFixedMaskTime()>0){
							m_tmpIntValue=m_SelectedTrigger->getFixedMaskTime();
							m_SelectedTrigger->setFixedMaskTime(--m_tmpIntValue);
						}
						break;
					case 7:	// Dynamic Threshold
						if (m_SelectedTrigger->getDynamicTriggerPercent()>0){
							m_tmpIntValue=m_SelectedTrigger->getDynamicTriggerPercent();
							m_SelectedTrigger->setDynamicTriggerPercent(--m_tmpIntValue);
						}
						break;
					case 8:	// Positional Sensing
						m_SelectedTrigger->setHasController(!m_SelectedTrigger->HasController());
						break;
					case 9:	// Controller Resolution
						if (m_SelectedTrigger->getControllerResolution()>0){
							m_tmpIntValue=m_SelectedTrigger->getControllerResolution();
							m_SelectedTrigger->setControllerResolution(--m_tmpIntValue);
						}
						break;
					case 10:	// Foot splash sensitivity
						if (m_SelectedTrigger->getFootSplashSensitivity()>1){
							m_tmpIntValue=m_SelectedTrigger->getFootSplashSensitivity();
							m_SelectedTrigger->setFootSplashSensitivity(--m_tmpIntValue);
						}
						break;
				}
			}else if (currentScreen=="SignalCurveEdit"){
				// Change Point X cursor :
				if (myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1] > 0 ){
					myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1]--;
				}
			}else if (currentScreen=="SignalCurvePointEdit"){
				// Change Point Y Value
				m_tmpIntValue=(*m_SelectedTrigger->getSignalCurve()->getAllCurvePoints())[myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]]->yValue;
				if (m_tmpIntValue>0){
					m_tmpIntValue--;
					m_SelectedTrigger->getSignalCurve()->setValueAt(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2], m_tmpIntValue);
				}
			}else{
				if (currentSelectedItem > 0){
					myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1]--;
				}
			}
		break;
	case 275:	// RIGHT key
		if (currentScreen=="MainScreen"){
			// If we are on main screen, then we handle special action (
			switch(myglobalSettings.getRotaryAction()){
				case Settings::Rotary_ChangeBPM:
					myMetronome.IncMetronomeBpm(5);
					break;
				case Settings::Rotary_ChangeVolume:
					if(myglobalSettings.getVolume()<32){
						myglobalSettings.setVolume(myglobalSettings.getVolume()+1);
					}
					break;
				case Settings::Rotary_ChangeDrumKit:
					DrumKit *nextDK;
					nextDK=myglobalSettings.getNextDrumKit(myglobalSettings.getCurrentDrumKit());
					if (nextDK!=NULL){
						myglobalSettings.loadDrumKit(nextDK);
					}
					break;
			}
		}else if (currentScreen=="MetronomeVal"){
			switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
				case 0:
					myMetronome.IncMetronomeBpm(1);
					break;
				case 1:
					m_tmpIntValue=myMetronome.getMetronomeVolume();
					if (m_tmpIntValue<32){
						myMetronome.setMetronomeVolume(m_tmpIntValue+1);
					}
					break;
				case 2:
					m_tmpIntValue=myMetronome.getMetronomeBCount();
					if (m_tmpIntValue<32){
						myMetronome.setMetronomeBCount(m_tmpIntValue+1);
					}
					break;
				case 3:
					myMetronome.setMetronomeOn(!myMetronome.isMetronomeOn());
					break;
			}
		}else if (currentScreen=="KitSetup1Val"){
			switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
				case 0:
					// Change instrument !
					// Get next instrument in list
					Instrument *tmpInstr;
					tmpInstr=m_SelectedDK->getChoosenInstrument();
					tmpInstr=myglobalSettings.getNextInstrument(tmpInstr);
					if (tmpInstr!=NULL){
						m_SelectedDK->setChoosenInstrument(tmpInstr);
						tmpInstr->loadInstrumentSamples();

						// Play the sample so we ear what we choose :
						if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);

						myglobalSettings.getCurrentDrumKit()->cleanUpInstrumentSamples();
					}
					break;
				case 1:
					// Change Pitch
					m_tmpFloatValue=m_SelectedDK->getPitch();
					if (m_tmpFloatValue<2.00f){
						m_tmpFloatValue+=0.01f;
						m_SelectedDK->setPitch(m_tmpFloatValue);

						// Play the sample so we ear what we choose :
						if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);

					}
					break;
				case 2:
					// Change Gain
					m_tmpFloatValue=m_SelectedDK->getReplayGain();
					if (m_tmpFloatValue<3.00f){
						m_tmpFloatValue+=0.1f;
						m_SelectedDK->setReplayGain(m_tmpFloatValue);

						// Play the sample so we ear what we choose :
						if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);
					}
					break;
				case 3:
					// Change Balance
					m_tmpFloatValue=m_SelectedDK->getBalance();
					if (m_tmpFloatValue<1.0f){
						m_tmpFloatValue+=0.1f;
						m_SelectedDK->setBalance(m_tmpFloatValue);

						// Play the sample so we ear what we choose :
						if (myglobalSettings.isPlaySampleOnSettingChange()) m_SelectedDK->playInstrument(127,127);
					}
					break;
			}
		}else if (currentScreen == "GlobalSetup1"){
			switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
				case 0: // Volume
					// Add 1
					m_tmpIntValue=myglobalSettings.getVolume();
					if (m_tmpIntValue<32){
						myglobalSettings.setVolume(++m_tmpIntValue);
					}
					break;
				case 1: // Instrument fadeout time
					// Add 0.1s
					m_tmpFloatValue=myglobalSettings.getGlobalFadeOutTime();
					// Max value = 2s
					if (m_tmpFloatValue<2.0f){
						m_tmpFloatValue+=0.1f;
						myglobalSettings.setGlobalFadeOutTime(m_tmpFloatValue);
					}
					break;
				case 2:	//Auto poweroff delay
					// Substract 5 minutes (300 seconds)
					m_tmpIntValue=myglobalSettings.getAutoPowerOffDelay();
					// Max value = 4 hours
					if (m_tmpIntValue<14400){
						myglobalSettings.setAutoPowerOffDelay(m_tmpIntValue+300);
					}
					break;
				case 3:	// Invert rotary knob :
					// Set value = NOT value
					myglobalSettings.setRotaryKnobReversed(!myglobalSettings.isRotaryKnobReversed());
					break;
				case 4: // Main screen rotary action
					if (myglobalSettings.getRotaryAction()<2){
						myglobalSettings.setRotaryAction(myglobalSettings.getRotaryAction()+1);
					}
					break;
				case 5:	// Play sample on setting change
					// Set value = NOT value
					myglobalSettings.setPlaySampleOnSettingChange(!myglobalSettings.isPlaySampleOnSettingChange());
					break;
			}
		}else if (currentScreen=="TriggerSettingsVal"){
			switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
				case 0:	// trigger Type
					if (m_SelectedTrigger->getTriggerType()<6){
						m_tmpIntValue=m_SelectedTrigger->getTriggerType();
						m_SelectedTrigger->setTriggerType(++m_tmpIntValue);
					}
					break;
				case 1: // threshold
					if (m_SelectedTrigger->getThreshold()<512){
						m_tmpIntValue=m_SelectedTrigger->getThreshold();
						m_SelectedTrigger->setThreshold(++m_tmpIntValue);
					}
					break;
				case 2:	// Signal Curve
					if (m_SelectedTrigger->getSignalCurve()->getCurveType()<5){
							m_tmpIntValue=m_SelectedTrigger->getSignalCurve()->getCurveType();
							m_SelectedTrigger->getSignalCurve()->setCurveType(++m_tmpIntValue);
					}
					break;
				case 3:	// Max Value
					if (m_SelectedTrigger->getMaxValue()<1024){
						m_tmpIntValue=m_SelectedTrigger->getMaxValue();
						m_SelectedTrigger->setMaxValue(++m_tmpIntValue);
					}
					break;
				case 4:	// Mute Group
					if (m_SelectedTrigger->getMuteGroup()<64){
						m_tmpIntValue=m_SelectedTrigger->getMuteGroup();
						m_SelectedTrigger->setMuteGroup(++m_tmpIntValue);
					}
					break;
				case 5:	// Xtalk Group
					if (m_SelectedTrigger->getCrossTalkGroup()<64){
						m_tmpIntValue=m_SelectedTrigger->getCrossTalkGroup();
						m_SelectedTrigger->setCrossTalkGroup(++m_tmpIntValue);
					}
					break;
				case 6:	// Fixed Mask Time
					if (m_SelectedTrigger->getFixedMaskTime()<255){
						m_tmpIntValue=m_SelectedTrigger->getFixedMaskTime();
						m_SelectedTrigger->setFixedMaskTime(++m_tmpIntValue);
					}
					break;
				case 7:	// Dynamic Threshold
					if (m_SelectedTrigger->getDynamicTriggerPercent()<100){
						m_tmpIntValue=m_SelectedTrigger->getDynamicTriggerPercent();
						m_SelectedTrigger->setDynamicTriggerPercent(++m_tmpIntValue);
					}
					break;
				case 8:	// Positional Sensing
					m_SelectedTrigger->setHasController(!m_SelectedTrigger->HasController());
					break;
				case 9:	// Controller Resolution
					if (m_SelectedTrigger->getControllerResolution()<127){
						m_tmpIntValue=m_SelectedTrigger->getControllerResolution();
						m_SelectedTrigger->setControllerResolution(++m_tmpIntValue);
					}
					break;
				case 10:	// Foot splash sensitivity
					if (m_SelectedTrigger->getFootSplashSensitivity()<10){
						m_tmpIntValue=m_SelectedTrigger->getFootSplashSensitivity();
						m_SelectedTrigger->setFootSplashSensitivity(++m_tmpIntValue);
					}
					break;
			}
		}else if (currentScreen=="SignalCurveEdit"){
			// Change Point X cursor :
			if (myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1] < m_SelectedTrigger->getSignalCurve()->getAllCurvePoints()->size()-1){
				myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1]++;
			}
		}else if (currentScreen=="SignalCurvePointEdit"){
			// Change Point Y Value
			m_tmpIntValue=(*m_SelectedTrigger->getSignalCurve()->getAllCurvePoints())[myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]]->yValue;
			if (m_tmpIntValue<127){
				m_tmpIntValue++;
				m_SelectedTrigger->getSignalCurve()->setValueAt(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2], m_tmpIntValue);
			}
		}else {
			if (currentSelectedItem < maxSelectedMenuItem){
				myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1]++;
			}
		}
		break;
	}

	return 0;

}

void ScreenDrawing::DrawMainScreen(){
	string kitName;
	string Vol;
	unsigned int nbTriggers;
	unsigned int histogramBarSize;
	unsigned int xOffset;
	unsigned int maxHeight;
	unsigned int boxW;

	// Clean the screen
	fillBackground();

	// An horizontal line on top and bottom:
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));
	line(screen, 0, 220, 319, 220, SDL_MapRGB(screen->format, 255, 255, 255));
	// An vertical line on top and bottom, to split the zone:
	line(screen, 100, 0, 100, 20, SDL_MapRGB(screen->format, 255, 255, 255));
	line(screen, 100, 220, 100, 240, SDL_MapRGB(screen->format, 255, 255, 255));

	// Kit Name :
	if (myglobalSettings.getCurrentDrumKit() != NULL){
		// Kit name in middle of the screen:
		kitName=myglobalSettings.getCurrentDrumKit()->getKitName();
	}else{
		kitName="(no Kit loaded)";
	}

	DrawLabel(kitName, 30, 0, 22, false );

	// Metronome BPM : bottom left
	std::stringstream sbpm;
	sbpm << "BPM : " << myMetronome.getMetronomeBpm();
	DrawLabel(sbpm.str(), 18, 2, 220, false );

	// Volume : top left
	std::stringstream svol;
	svol<< "Vol : " << myglobalSettings.getVolume();
	DrawLabel(svol.str() , 18, 2, 0, false );

	// Last trigger velocity for each input :
	std::vector<DrumKitComponent*> *dkCompList=myglobalSettings.getCurrentDrumKit()->getDkComponentList();
	nbTriggers=dkCompList->size();
	if (nbTriggers>0){
		histogramBarSize=(310/nbTriggers);
	}else{
		histogramBarSize=0;
	}


	xOffset= (320 - (histogramBarSize*nbTriggers))/2;

	// Bar height = 100 max.
	maxHeight=127;

	// Draw a box around histogram
	boxW= (histogramBarSize*nbTriggers) + 4;
	box(screen, xOffset-2, 213 - maxHeight, boxW, maxHeight+4 , SDL_MapRGB(screen->format, 255, 255, 255));
	// Draw a light grey line in middle of histogram :
	line(screen, xOffset-1, (213-(maxHeight/2)), xOffset + boxW-2, (213-(maxHeight/2)),  SDL_MapRGB(screen->format, 120,120,120) );

	Uint32 barColor;

	for(unsigned int i=0; i<nbTriggers;i++){
		// 1 pixel narrower so we have a space between bars.
		for (unsigned int x=0;x<histogramBarSize-1;x++){

			unsigned int xpos=xOffset+(i*histogramBarSize)+x;

			// If Hit since less than 2 second :
			if ((*dkCompList)[i]->getAssociatedTrigger()!=NULL){
				if ((*dkCompList)[i]->getAssociatedTrigger()->getLastTimeHit() + 2000 > ticksNow ){
					unsigned int barHeight = (*dkCompList)[i]->getAssociatedTrigger()->getLastVelocity()*maxHeight/127;

					if (barHeight>0){
						if ((*dkCompList)[i]->getAssociatedTrigger() == myglobalSettings.getCurrentDrumKit()->getLastTriggerHit() ){
							// If last hit trigger, set RED.
							barColor=SDL_MapRGB(screen->format, 255, 0, 0);
						}else{
							// Else set white...
							barColor=SDL_MapRGB(screen->format, 255, 255, 255);
						}
						// Draw a vertical line :
						line(screen, xpos, 215-barHeight,  xpos, 215, barColor);
					}
				}
			}

		}
	}


    SDL_Flip(screen);

}

void ScreenDrawing::DrawMainMenu(){

	unsigned int currentSel=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];

	// Clean the screen
	fillBackground();

	// First line of icons
	DrawIcon(myglobalSettings.getUserDirectory() + "/.piDrummer/res/kitsel.gif",44, 20);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.piDrummer/res/metronome.gif",136, 20);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.piDrummer/res/audioplayer.gif",228, 20);

	// Labels
	DrawLabel("Kit Sel." , 18, 34, 70, (currentSel==0?true:false));
	DrawLabel("Metronome" , 18, 106, 70, (currentSel==1?true:false));
	DrawLabel("Audio Play" , 18, 208, 70, (currentSel==2?true:false));


	// Second line of icons
	DrawIcon(myglobalSettings.getUserDirectory() + "/.piDrummer/res/training.gif",44, 130);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.piDrummer/res/kitsetup.gif",136, 130);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.piDrummer/res/settings.gif",228, 130);
	DrawLabel("Trainer" , 18, 34, 180, (currentSel==3?true:false));
	DrawLabel("Kit Setup" , 18, 126, 180, (currentSel==4?true:false));
	DrawLabel("Settings" , 18, 223, 180, (currentSel==5?true:false));


    SDL_Flip(screen);

}


void ScreenDrawing::DrawKitSelect(){

	std::vector<std::string> ListOfKits;
	unsigned int selItem;

	// Clean the screen
	fillBackground();

	DrawLabel("Kit Select" , 18, 110, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	if (myglobalSettings.getDrumKitList()->size()>0){
		maxSelectedMenuItem= myglobalSettings.getDrumKitList()->size()-1;

		// Draw the list of available drumkits :
		for(unsigned int i=0;i <= maxSelectedMenuItem;i++){
			ListOfKits.push_back((*myglobalSettings.getDrumKitList())[i]->getKitName());
		}

		if (myCurrentSelectedMenuItem.size()>0){
			selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];
		}else{
			selItem=0;
		}

		DrawList(ListOfKits, 0, 21, 320, 219, selItem);
	}



    SDL_Flip(screen);

}

void ScreenDrawing::DrawMetronomeSetup(){
	vector<string> settingsList;
	vector<string> valueList;
	unsigned int selItem;
	bool valChange;
	TextLabel *txtLabel;

	settingsList.push_back("BPM");
	settingsList.push_back("Volume");
	settingsList.push_back("B. Count");
	settingsList.push_back("On/Off");


	std::stringstream myItoA;
	myItoA << myMetronome.getMetronomeBpm();
	valueList.push_back(myItoA.str());

	myItoA.str("");
	myItoA << myMetronome.getMetronomeVolume();
	valueList.push_back(myItoA.str());

	myItoA.str("");
	myItoA << myMetronome.getMetronomeBCount();
	valueList.push_back(myItoA.str());

	if (myMetronome.isMetronomeOn()){
		valueList.push_back("On");
	}else{
		valueList.push_back("Off");
	}

	// Clean the screen
	fillBackground();

	DrawLabel("Metronome" , 18, 110, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));


	// Draw the list of available settings :
	maxSelectedMenuItem= settingsList.size()-1;

	if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="MetronomeVal"){
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2];
	}else{
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];
	}

	DrawList(settingsList, 0, 21, 100, 219, selItem);
	// Draw a line at right of the list :
	line(screen, 100, 20, 100, 239, SDL_MapRGB(screen->format, 255, 255, 255));

	// Draw the current setting on right :
	txtLabel=new TextLabel(settingsList[selItem],210,85);
	txtLabel->setFontSize(30);
	txtLabel->setTextAlignment(TextLabel::CENTER_ALIGN);
	txtLabel->doDraw();

	if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="MetronomeVal"){
		valChange=true;
	}else{

		valChange=false;
	}

	txtLabel->setText(valueList[selItem]);
	txtLabel->setYPos(120);
	txtLabel->setTextAlignment(TextLabel::CENTER_ALIGN);
	txtLabel->setTextSelected(valChange);
	txtLabel->doDraw();

	delete txtLabel;
	txtLabel=NULL;



    SDL_Flip(screen);

}

void ScreenDrawing::DrawAudioPlayer(){

	// Clean the screen
	fillBackground();

	DrawLabel("Audio Player" , 18, 110, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));



    SDL_Flip(screen);

}

void ScreenDrawing::DrawTrainingMenu(){

	// Clean the screen
	fillBackground();

	DrawLabel("Training" , 18, 120, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));



    SDL_Flip(screen);

}

void ScreenDrawing::DrawKitSetupMenu(){
	vector<string> valueList;
	std::vector<DrumKitComponent*> *dkCompList;
	unsigned int selItem;
	Trigger *dkTrig;

	dkCompList=	myglobalSettings.getCurrentDrumKit()->getDkComponentList();

	// Set a list of available triggers :
	for (unsigned int i=0; i<dkCompList->size() ; i++ ){
		// Add the trigger name to the list :
		dkTrig= (*dkCompList)[i]->getAssociatedTrigger();
		valueList.push_back(dkTrig->getTriggerName());
	}

	maxSelectedMenuItem= valueList.size()-1;

	selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];

	// Clean the screen
	fillBackground();

	DrawLabel("Kit Setup" , 18, 120, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	// Draw the current setting on right :
	DrawLabel("Select a trigger" , 24, 120, 115, false);
	DrawLabel("in list" , 24, 160, 145, false);


	DrawList(valueList, 0, 21, 100, 219, selItem);

	// Draw a line at right of the list :
	line(screen, 100, 20, 100, 239, SDL_MapRGB(screen->format, 255, 255, 255));



    SDL_Flip(screen);

    // Free pointers ...
    dkCompList=NULL;
    dkTrig=NULL;
}

void ScreenDrawing::DrawKitSetupTriggerChoosen(){
	vector<string> valueList ;
	unsigned int selItem;
	string TrigName;
	std::stringstream myItoA;
	string txtValue;
	TextLabel *txtLabel;
	bool ValueSelected;


	if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="KitSetup1"){
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];
		maxSelectedMenuItem=3;
		ValueSelected=false;
	}else{
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2];
		ValueSelected=true;
	}

	TrigName = m_SelectedDK->getAssociatedTrigger()->getTriggerName();
	TrigName += " Setup";


	// Clean the screen
	fillBackground();

	// Draw the name of selected trigger on screen :
	txtLabel=new TextLabel(TrigName,160,0);
	txtLabel->setFontSize(18);
	txtLabel->setTextAlignment(TextLabel::CENTER_ALIGN);
	txtLabel->doDraw();

	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	// Make a list of available settings :
	valueList.push_back("Instrument");
	valueList.push_back("Pitch");
	valueList.push_back("Gain");
	valueList.push_back("Balance");

	DrawList(valueList, 0, 21, 100, 219, selItem);

	// Draw a line at right of the list :
	line(screen, 100, 20, 100, 239, SDL_MapRGB(screen->format, 255, 255, 255));

	// Draw the current setting on right :
	txtLabel->setText(valueList[selItem]);
	txtLabel->setXPos(210);
	txtLabel->setYPos(85);
	txtLabel->setFontSize(30);
	txtLabel->doDraw();

	// Draw the current value of setting :
	switch(selItem){
		case 0:
			// Instrument
			if (m_SelectedDK->getChoosenInstrument()==NULL){
				txtValue = "- None selected -";
			}else{
				txtValue = m_SelectedDK->getChoosenInstrument()->getInstrumentName();
			}
			break;
		case 1:
			// Pitch
			myItoA << std::fixed << std::setprecision(2) << m_SelectedDK->getPitch();
			txtValue=myItoA.str();
			break;
		case 2:
			// Gain
			myItoA << std::fixed << std::setprecision(2) <<  m_SelectedDK->getReplayGain();
			txtValue=myItoA.str();
			break;
		case 3:
			// Balance
			myItoA << std::fixed << std::setprecision(2) <<  m_SelectedDK->getBalance();
			txtValue=myItoA.str();
			break;
	}

	txtLabel->setFontSize(24);
	txtLabel->setXPos(210);
	txtLabel->setYPos(130);
	txtLabel->setText(txtValue);
	txtLabel->setTextSelected(ValueSelected);
	txtLabel->setMaxWidth(210);
	txtLabel->doDraw();


	delete txtLabel;
	txtLabel=NULL;


    SDL_Flip(screen);
}

void ScreenDrawing::DrawGlobalSettingsMenu(){
	vector<string> settingsList;
	unsigned int selItem=0;
	TextLabel *txtLabel;
	string txtValue;
	std::stringstream myItoA;
	bool ValueSelected;

	// Clean the screen
	fillBackground();

	DrawLabel("Global Settings" , 18, 100, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	settingsList.push_back("Volume");
//	settingsList.push_back("Master Reverb");
//	settingsList.push_back("Master Equalizer");
	settingsList.push_back("Instrument Fade-out Time");
	settingsList.push_back("Auto Power-Off Delay");
	settingsList.push_back("Invert rotary knob");
	settingsList.push_back("Main screen rotary action");
	settingsList.push_back("Play sample on setting change");
	settingsList.push_back("Copy Kit");
	settingsList.push_back("Triggers Settings");

	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	// Draw the list of available settings :
	if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="GlobalSetup1"){
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2];
		ValueSelected=true;
	}else{
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];
		maxSelectedMenuItem= settingsList.size()-1;
		ValueSelected=false;
	}


	DrawList(settingsList, 0, 21, 100, 219, selItem);
	// Draw a line at right of the list :
	line(screen, 100, 20, 100, 239, SDL_MapRGB(screen->format, 255, 255, 255));

	// Draw the name of selected trigger on screen :
	txtLabel=new TextLabel(settingsList[selItem],210,85);
	txtLabel->setMaxWidth(210);
	txtLabel->setFontSize(30);
	txtLabel->setTextAlignment(TextLabel::CENTER_ALIGN);
	txtLabel->doDraw();

	// Draw the current value of setting :
	txtLabel->setFontSize(24);
	txtLabel->setXPos(210);
	txtLabel->setYPos(130);

	switch(selItem){
		case 0:
			// Volume
			myItoA << myglobalSettings.getVolume();
			txtValue=myItoA.str();
			break;
		case 1:
			// Instrument FadeOut Time
			myItoA << std::fixed << std::setprecision(2) <<  myglobalSettings.getGlobalFadeOutTime() << " s.";
			txtValue=myItoA.str();
			break;
		case 2:
			// Power Off delay
			myItoA << (myglobalSettings.getAutoPowerOffDelay()/60) << " min.";
			txtValue=myItoA.str();
			break;
		case 3:
			// Invert rot. Knob
			if (myglobalSettings.isRotaryKnobReversed()){
				txtValue="On";
			}else{
				txtValue="Off";
			}
			break;
		case 4:
			// Main screen rotary action
			switch(myglobalSettings.getRotaryAction()){
				case Settings::Rotary_ChangeBPM:
					txtValue="Change BPM";
					break;
				case Settings::Rotary_ChangeVolume:
					txtValue="Change Volume";
					break;
				case Settings::Rotary_ChangeDrumKit:
					txtValue="Change Drum Kit";
					break;
			}
			break;
		case 5:
			// Play sample on setting change
			if (myglobalSettings.isPlaySampleOnSettingChange()){
				txtValue="On";
			}else{
				txtValue="Off";
			}
			break;
		case 6:
			// Copy Kit
			txtValue = "Copy";
			break;
		case 7:
			// Trigger Settings
			txtValue = "> Setup";
			break;
	}

	txtLabel->setText(txtValue);
	txtLabel->setTextSelected(ValueSelected);
	txtLabel->doDraw();


	delete txtLabel;
	txtLabel=NULL;



    SDL_Flip(screen);

}

void ScreenDrawing::DrawList(std::vector<std::string> listText, int x, int y, int w, int h, unsigned int selectedItem){
	SDL_Surface *ListSurface;
	SDL_Surface *Container;
	SDL_Color white={255,255,255, 0};
	SDL_Rect position;
	SDL_Rect positionList;
	TextLabel *txtLabel;
	unsigned int i; // List index
	unsigned int listHeight;

	position.x=x;
	position.y=y;

	// We center the list on the middle : the selected item is always on center .
	positionList.x=0;
	positionList.y=(h/2)-(selectedItem*20);

	// With a 18 font size, each line should be about 20 pixel high.
	listHeight=listText.size()*20;

	//Create the container surface :
	Container=SDL_CreateRGBSurface(SDL_HWSURFACE,w, h, 16,0,0,0,0);

	// Create the receiving surface :
	ListSurface=SDL_CreateRGBSurface(SDL_HWSURFACE,w, listHeight, 16,0,0,0,0);

	// Initialize the textLabel
	txtLabel=new TextLabel();
	txtLabel->setFontSize(18);
	txtLabel->setTextAlignment(TextLabel::LEFT_ALIGN);
	txtLabel->setDrawingSurface(ListSurface);
	txtLabel->setXPos(0);
	txtLabel->setMaxWidth(w);


	// Fill the receiving surface :
	for (i=0; i<listText.size(); i++){
		txtLabel->setText(listText[i]);
		txtLabel->setYPos(i*20);
		txtLabel->setTextColor(white);
		txtLabel->setTextSelected(selectedItem==i?true:false);
		txtLabel->setDoScroll(selectedItem==i?true:false);

		// Draw the current setting on right :
		txtLabel->doDraw();

	}

	delete txtLabel;
	txtLabel=NULL;

	SDL_SetColorKey(ListSurface, SDL_SRCCOLORKEY, SDL_MapRGB(ListSurface->format, 0, 0, 0));
	SDL_SetColorKey(Container, SDL_SRCCOLORKEY, SDL_MapRGB(Container->format, 0, 0, 0));

	SDL_BlitSurface(ListSurface, NULL, Container, &positionList); /* Blit List to the container*/
	SDL_BlitSurface(Container, NULL, screen, &position); /* Blit container to screen*/

	SDL_FreeSurface( ListSurface );
	SDL_FreeSurface( Container );
	ListSurface=NULL;
	Container=NULL;

}


void ScreenDrawing::DrawTriggerSettings(){
	// Draw the trigger Settings menu :
	vector<string> valueList;
	std::vector<Trigger*> *TriggerList ;
	unsigned int selItem;
	Trigger *Trig;


	TriggerList =myglobalSettings.getTriggerList();

	// Set a list of available triggers :
	for (unsigned int i=0; i < TriggerList->size() ; i++ ){
		// Add the trigger name to the list :
		Trig= (*TriggerList )[i];
		valueList.push_back(Trig->getTriggerName());
	}

	maxSelectedMenuItem= valueList.size()-1;

	selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];

	// Clean the screen
	fillBackground();

	DrawLabel("Triggers Setup" , 18, 120, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	// Draw the current setting on right :
	DrawLabel("Select a trigger" , 24, 120, 115, false);
	DrawLabel("in list" , 24, 160, 145, false);


	DrawList(valueList, 0, 21, 100, 219, selItem);

	// Draw a line at right of the list :
	line(screen, 100, 20, 100, 239, SDL_MapRGB(screen->format, 255, 255, 255));

    SDL_Flip(screen);

    // Free pointers ...
    TriggerList = NULL;
    Trig = NULL;
}

void ScreenDrawing::RefreshScreen(){
	// Call the function to draw the screen :
	(*this.*refreshFunction)();
}


void ScreenDrawing::setLastTriggerVelocity(unsigned int TriggerInput, unsigned int TriggerVelocity){
	m_triggerLastHitValues[TriggerInput]=TriggerVelocity;
}


void ScreenDrawing::DrawGlobalSetupTriggerChoosen(){
	vector<string> settingsList;
	SDL_Color green={0,255,0, 0};
	unsigned int selItem=0;
	TextLabel *txtLabel;
	string txtValue;
	std::stringstream myItoA;
	bool ValueSelected;
	unsigned int selPoint;
	const unsigned int xCurvePos=105;
	const unsigned int yCurvePos=82;
	const unsigned int CurveWidth=155;
	const unsigned int CurveHeight=155;


	// Clean the screen
	fillBackground();

	txtValue=m_SelectedTrigger->getTriggerName() + " settings";

	DrawLabel(txtValue , 18, 100, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	/* Trigger settings to be set :
	 * 			Type
	 * 			Threshold
	 * 			Signal Curve
	 * 			Max Value
	 * 			Mute Group
	 * 			Xtalk Group
	 * 			Fixed Mask Time
	 * 			Dynamic Threshold
	 * 			Positional Sensing
	 * 			Foot Splash Sensitivity
	 * 			Controller Resolution
	 */

	settingsList.push_back("Type");
	settingsList.push_back("Threshold");
	settingsList.push_back("Signal curve");
	settingsList.push_back("Max. Value");
	settingsList.push_back("Mute Group");
	settingsList.push_back("Xtalk Group");
	settingsList.push_back("Fixed Mask Time");
	settingsList.push_back("Dynamic Threshold");
	settingsList.push_back("Positional Sensing");
	settingsList.push_back("Controller Resolution");
	if (m_SelectedTrigger->getTriggerType() == Trigger::TT_HiHatController){
		settingsList.push_back("Foot splash sensitivity");
	}

	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];
	maxSelectedMenuItem= settingsList.size()-1;
	ValueSelected=false;
	// Draw the list of available settings :
	if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="TriggerSettingsVal" ){
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2];
		ValueSelected=true;
	}else if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="SignalCurveEdit"){
		selPoint=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];
		selItem=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-3];
		ValueSelected=true;
	}else if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="SignalCurvePointEdit"){
		selPoint=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2];
		selItem = myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-4];
		ValueSelected=true;
	}


	DrawList(settingsList, 0, 21, 100, 219, selItem);
	// Draw a line at right of the list :
	line(screen, 100, 20, 100, 239, SDL_MapRGB(screen->format, 255, 255, 255));

	// Draw the name of selected trigger on screen :
	txtLabel=new TextLabel(settingsList[selItem],210,20);
	txtLabel->setMaxWidth(210);
	txtLabel->setFontSize(30);
	txtLabel->setTextAlignment(TextLabel::CENTER_ALIGN);
	txtLabel->doDraw();

	// Draw the current value of setting :
	txtLabel->setFontSize(24);
	txtLabel->setXPos(210);
	txtLabel->setYPos(52);

	switch(selItem){
		case 0:
			// Type
			switch(m_SelectedTrigger->getTriggerType()){
				case Trigger::TT_CymbalBell:
					txtValue="Cymbal Bell";
					break;
				case Trigger::TT_CymbalEdgeOrChoke:
					txtValue="Cymbal Edge or Choke";
					break;
				case Trigger::TT_CymbalPiezo:
					txtValue="Cymbal Piezo";
					break;
				case Trigger::TT_PadCenter:
					txtValue="Pad Center";
					break;
				case Trigger::TT_PadEdge:
					txtValue="Pad Edge";
					break;
				case Trigger::TT_HiHatController:
					txtValue="HiHat Controller";
					break;
				case Trigger::TT_Switch:
					txtValue="Switch";
					break;
				case Trigger::TT_HiHatPedalOpen:
					txtValue="HiHat Pedal Opened";
					break;
				case Trigger::TT_HiHatPedalClose:
					txtValue="HiHat Pedal Closed";
					break;
			}
			break;
		case 1:
			// Threshold
			myItoA <<  m_SelectedTrigger->getThreshold();
			txtValue=myItoA.str();
			break;
		case 2:
			// Signal Curve
			// Draw the curve :
			drawSignalCurve(screen, m_SelectedTrigger->getSignalCurve(), xCurvePos, yCurvePos , CurveWidth, CurveHeight);
			// Draw a box to show the curve is being edited :
			if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="SignalCurveEdit"
			 || myCurrentMenuPath[myCurrentMenuPath.size()-1]=="SignalCurvePointEdit"){
				// Draw a box around the signal curve graph to show it's selected !
				box(screen, xCurvePos, yCurvePos , CurveWidth, CurveHeight, SDL_MapRGB(screen->format, 0, 255, 0));
				box(screen, xCurvePos-1, yCurvePos -1, CurveWidth+2, CurveHeight+2, SDL_MapRGB(screen->format, 0, 255, 0));

				// Show the current selected point :
				unsigned int nbPoints=m_SelectedTrigger->getSignalCurve()->getAllCurvePoints()->size();
				CurvePoint *curvPt;
				SDL_Point pt;
				curvPt=(*m_SelectedTrigger->getSignalCurve()->getAllCurvePoints())[selPoint];
				pt.x=xCurvePos + (selPoint*CurveWidth/(nbPoints-1))-1;
				pt.y=yCurvePos  + CurveWidth - (curvPt->yValue*CurveHeight/127)-1 ;
				// Draw the box around point :
				box(screen, pt.x, pt.y, 3, 3, SDL_MapRGB(screen->format, 255, 255, 0));
				box(screen, pt.x-1, pt.y-1, 4, 4, SDL_MapRGB(screen->format, 255, 255, 0));

				// Write the point Values at right of the graph :
				DrawLabel("In :", 24, 270, 100,  false );
				myItoA.str("");
				myItoA <<  curvPt->xValue;
				txtValue=myItoA.str();
				DrawLabel(txtValue, 24, 270, 130, green, false);

				DrawLabel("Out:", 24, 270, 160, false);
				myItoA.str("");
				myItoA <<  curvPt->yValue;
				txtValue=myItoA.str();
				if (myCurrentMenuPath[myCurrentMenuPath.size()-1]=="SignalCurvePointEdit"){
					DrawLabel(txtValue, 24, 270, 190, green, true);
				}else{
					DrawLabel(txtValue, 24, 270, 190, green, false);
				}
			}


			switch(m_SelectedTrigger->getSignalCurve()->getCurveType()){
				case SignalCurve::Curve_Linear:
					txtValue="Linear";
					break;
				case SignalCurve::Curve_Exp:
					txtValue="Exponential";
					break;
				case SignalCurve::Curve_Log:
					txtValue="Logarithmic";
					break;
				case SignalCurve::Curve_SLine:
					txtValue="S-Line";
					break;
				case SignalCurve::Curve_Max:
					txtValue="Max Value";
					break;
				case SignalCurve::Curve_Custom:
					txtValue="Custom";
					break;
			}
			break;
		case 3:
			// Max Value
			myItoA <<  m_SelectedTrigger->getMaxValue();
			txtValue=myItoA.str();
			break;
		case 4:
			// Mute Group
			myItoA <<  m_SelectedTrigger->getMuteGroup();
			txtValue=myItoA.str();
			break;
		case 5:
			// Xtalk Group
			myItoA <<  m_SelectedTrigger->getCrossTalkGroup();
			txtValue=myItoA.str();
			break;
		case 6:
			// Fixed Mask Time
			myItoA <<  m_SelectedTrigger->getFixedMaskTime();
			txtValue=myItoA.str();
			break;
		case 7:
			// Dynamic Threshold
			myItoA <<  m_SelectedTrigger->getDynamicTriggerPercent() << " %";
			txtValue=myItoA.str();
			break;
		case 8:
			//Positional Sensing
			if (m_SelectedTrigger->HasController() ){
				txtValue="On";
			}else{
				txtValue="Off";
			}
			break;
		case 9:
			// Controller Resolution
			myItoA <<  m_SelectedTrigger->getControllerResolution();
			txtValue=myItoA.str();
			break;
		case 10:
			// Foot Splash Sensitivity
			myItoA <<  m_SelectedTrigger->getFootSplashSensitivity();
			txtValue=myItoA.str();
			break;
	}

	txtLabel->setText(txtValue);
	txtLabel->setTextSelected(ValueSelected);
	txtLabel->doDraw();


	delete txtLabel;
	txtLabel=NULL;

    SDL_Flip(screen);

}


void fillBackground(){
	// Draw a gradient from black to grey:

	SDL_Rect dims;
	dims.x=0;
	dims.w=320;
	dims.h=4;

	for (unsigned int i=0;i<80;i++){
		dims.y=i*4;
		SDL_FillRect(screen, &dims, SDL_MapRGB(screen->format, i, i, i));
	}

}


void ScreenDrawing::DrawPowerOffScreen(){
	// Clean the screen
	fillBackground();

	SDL_Color orange={255,162,0, 0};
	DrawLabel("Bye !", 30, 160, 100, orange, false );

    SDL_Flip(screen);

}
