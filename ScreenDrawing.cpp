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
	m_screenNeedRefresh=false;

	m_lastFontSizeUsed=0;
	maxSelectedMenuItem=0;

	refreshFunction=&ScreenDrawing::DrawMainScreen;
	myCurrentMenuPath.push_back("MainScreen");
	myCurrentSelectedMenuItem.push_back(0);
	m_tmpBoolValue=false;
	m_tmpFloatValue=0.0;
	m_tmpIntValue=0;
	m_tmpStringValue="";
	m_SelectedDK=NULL;
}


ScreenDrawing::~ScreenDrawing(){

}

void ScreenDrawing::setLastTriggerVelocity(unsigned int TriggerInput, unsigned int TriggerVelocity){
	m_triggerLastHitValues[TriggerInput]=TriggerVelocity;
}


void ScreenDrawing::DrawSplashScreen(){

	SDL_Color orange={255,162,0};

	DrawLabel("ur", 30,  100, 100, false );
	DrawLabel("Drummer", 30, 128, 100, orange, false );
	DrawLabel(urDrummerVersion, 10,  290, 225, false);

	// Draw the logo
   	DrawIcon(myglobalSettings.getUserDirectory() + "/.urDrummer/res/urdrummer_logo.gif", 140, 30, false);


    SDL_Flip(screen);

}

void ScreenDrawing::DrawIcon(const string iconPath, int posX, int posY,  bool selected){
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
	SDL_Color white={255,255,255};
	DrawLabel(labelText, fontSize, posX, posY,  white, false);
}

void ScreenDrawing::DrawLabel( std::string labelText, int fontSize, int posX, int posY, bool selected){
	SDL_Color white={255,255,255};

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

	string fontPath = myglobalSettings.getUserDirectory() + "/.urDrummer/res/arial.ttf";

	myFont = TTF_OpenFont(fontPath.c_str(), fontSize);

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

	TTF_CloseFont(myFont);

}


void ScreenDrawing::DrawLabelToList(SDL_Surface *dest, std::string labelText, int fontSize, int posX, int posY, SDL_Color color, bool selected=false){
	SDL_Rect position;
	SDL_Color invertColor;
	SDL_Surface *texte ;
	SDL_Surface *BGSurf;
	TTF_Font *myFont= NULL;

	string fontPath = myglobalSettings.getUserDirectory() + "/.urDrummer/res/arial.ttf";

	myFont = TTF_OpenFont(fontPath.c_str(), fontSize);

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

	TTF_CloseFont(myFont);
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

			}

		}
		break;
	case 276:	// LEFT key
		if (currentScreen=="MainScreen"){
			// If we are on main screen, then we handle special action (
			// TODO : handle special action from main screen
			myglobalSettings.DecMetronomeBpm(5);

		}else if (currentScreen=="MetronomeVal"){
				switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
					case 0:
						myglobalSettings.DecMetronomeBpm(1);
						break;
					case 1:
						m_tmpIntValue=myglobalSettings.getMetronomeVolume();
						if (m_tmpIntValue>1){
							myglobalSettings.setMetronomeVolume(--m_tmpIntValue);
						}
						break;
					case 2:
						m_tmpIntValue=myglobalSettings.getMetronomeBCount();
						if (m_tmpIntValue>0){
							myglobalSettings.setMetronomeBCount(--m_tmpIntValue);
						}
						break;
					case 3:
						myglobalSettings.setMetronomeOn(!myglobalSettings.isMetronomeOn());
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

							myglobalSettings.getCurrentDrumKit()->cleanUpInstrumentSamples();
						}
						break;
					case 1:
						// Change Pitch
						m_tmpFloatValue=m_SelectedDK->getPitch();
						if (m_tmpFloatValue>0.0f){
							m_tmpFloatValue-=0.01f;
							m_SelectedDK->setPitch(m_tmpFloatValue);
						}
						break;
					case 2:
						// Change Gain
						m_tmpFloatValue=m_SelectedDK->getReplayGain();
						if (m_tmpFloatValue>0.0f){
							m_tmpFloatValue-=0.1f;
							m_SelectedDK->setReplayGain(m_tmpFloatValue);
						}
						break;
					case 3:
						// Change Balance
						m_tmpFloatValue=m_SelectedDK->getBalance();
						if (m_tmpFloatValue>-1.0f){
							m_tmpFloatValue-=0.1f;
							m_SelectedDK->setBalance(m_tmpFloatValue);
						}
						break;
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
			// TODO : handle special action from main screen
			myglobalSettings.IncMetronomeBpm(5);
		}else if (currentScreen=="MetronomeVal"){
			switch(myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-2]){
				case 0:
					myglobalSettings.IncMetronomeBpm(1);
					break;
				case 1:
					m_tmpIntValue=myglobalSettings.getMetronomeVolume();
					if (m_tmpIntValue<32){
						myglobalSettings.setMetronomeVolume(m_tmpIntValue+1);
					}
					break;
				case 2:
					m_tmpIntValue=myglobalSettings.getMetronomeBCount();
					if (m_tmpIntValue<32){
						myglobalSettings.setMetronomeBCount(m_tmpIntValue+1);
					}
					break;
				case 3:
					myglobalSettings.setMetronomeOn(!myglobalSettings.isMetronomeOn());
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

						myglobalSettings.getCurrentDrumKit()->cleanUpInstrumentSamples();
					}
					break;
				case 1:
					// Change Pitch
					m_tmpFloatValue=m_SelectedDK->getPitch();
					if (m_tmpFloatValue<2.00f){
						m_tmpFloatValue+=0.01f;
						m_SelectedDK->setPitch(m_tmpFloatValue);
					}
					break;
				case 2:
					// Change Gain
					m_tmpFloatValue=m_SelectedDK->getReplayGain();
					if (m_tmpFloatValue<3.00f){
						m_tmpFloatValue+=0.1f;
						m_SelectedDK->setReplayGain(m_tmpFloatValue);
					}
					break;
				case 3:
					// Change Balance
					m_tmpFloatValue=m_SelectedDK->getBalance();
					if (m_tmpFloatValue<1.0f){
						m_tmpFloatValue+=0.1f;
						m_SelectedDK->setBalance(m_tmpFloatValue);
					}
					break;
			}
		}
		else  {
			if (currentSelectedItem < maxSelectedMenuItem){
				myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1]++;
			}
		}
		break;
	}


	// Call the function to draw the screen :
	//(*this.*refreshFunction)();

	return 0;

}

void ScreenDrawing::DrawMainScreen(){
	/*
	 * Main screen shows :
	 * 	- current Kit Name
	 * 	- current BPM
	 * 	- Loaded audio file name
	 * 	- Position in playing track
	 * 	- Last Hit pad and velocity
	 */
	string kitName;
	string Vol;

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
	sbpm << "BPM : " << myglobalSettings.getMetronomeBpm();
	DrawLabel(sbpm.str(), 18, 2, 220, false );

	// Volume : top left
	std::stringstream svol;
	svol<< "Vol : " << myglobalSettings.getVolume();
	DrawLabel(svol.str() , 18, 2, 0, false );

	// Last trigger velocity for each input :
	std::vector<DrumKitComponent*> *dkCompList=myglobalSettings.getCurrentDrumKit()->getDkComponentList();
	unsigned int nbTriggers=dkCompList->size();
	unsigned int histogramBarSize=(310/nbTriggers);

	unsigned int xOffset= (320 - (histogramBarSize*nbTriggers))/2;

	// Bar height = 100 max.
	unsigned int maxHeight=127;

	// Draw a box around histogram
	unsigned int boxW= (histogramBarSize*nbTriggers) + 4;
	box(screen, xOffset-2, 213 - maxHeight, boxW, maxHeight+4 , SDL_MapRGB(screen->format, 255, 255, 255));
	// Draw a light grey line in middle of histogram :
	line(screen, xOffset-1, (213-(maxHeight/2)), xOffset + boxW-2, (213-(maxHeight/2)),  SDL_MapRGB(screen->format, 120,120,120) );

	Uint32 barColor;

	for(unsigned int i=0; i<nbTriggers;i++){
		// 1 pixel narrower so we have a space between bars.
		for (unsigned int x=0;x<histogramBarSize-1;x++){

			unsigned int xpos=xOffset+(i*histogramBarSize)+x;

			// If Hit since less than 2 second :
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



    // finally, update the screen :)
    SDL_Flip(screen);

}

void ScreenDrawing::DrawMainMenu(){

	unsigned int currentSel=myCurrentSelectedMenuItem[myCurrentSelectedMenuItem.size()-1];

	// Clean the screen
	fillBackground();

	// First line of icons
	DrawIcon(myglobalSettings.getUserDirectory() + "/.urDrummer/res/kitsel.gif",44, 20, false);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.urDrummer/res/metronome.gif",136, 20, false);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.urDrummer/res/audioplayer.gif",228, 20, false);

	// Labels
	DrawLabel("Kit Sel." , 18, 34, 70, (currentSel==0?true:false));
	DrawLabel("Metronome" , 18, 106, 70, (currentSel==1?true:false));
	DrawLabel("Audio Play" , 18, 208, 70, (currentSel==2?true:false));


	// Second line of icons
	DrawIcon(myglobalSettings.getUserDirectory() + "/.urDrummer/res/training.gif",44, 130, false);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.urDrummer/res/kitsetup.gif",136, 130, false);
	DrawIcon(myglobalSettings.getUserDirectory() + "/.urDrummer/res/settings.gif",228, 130, false);
	DrawLabel("Trainer" , 18, 34, 180, (currentSel==3?true:false));
	DrawLabel("Kit Setup" , 18, 126, 180, (currentSel==4?true:false));
	DrawLabel("Settings" , 18, 223, 180, (currentSel==5?true:false));

    // finally, update the screen :)
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


    // finally, update the screen :)
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
	myItoA << myglobalSettings.getMetronomeBpm();
	valueList.push_back(myItoA.str());

	myItoA.str("");
	myItoA << myglobalSettings.getMetronomeVolume();
	valueList.push_back(myItoA.str());

	myItoA.str("");
	myItoA << myglobalSettings.getMetronomeBCount();
	valueList.push_back(myItoA.str());

	if (myglobalSettings.isMetronomeOn()){
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


    // finally, update the screen :)
    SDL_Flip(screen);

}

void ScreenDrawing::DrawAudioPlayer(){

	// Clean the screen
	fillBackground();

	DrawLabel("Audio Player" , 18, 110, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));


    // finally, update the screen :)
    SDL_Flip(screen);

}

void ScreenDrawing::DrawTrainingMenu(){

	// Clean the screen
	fillBackground();

	DrawLabel("Training" , 18, 120, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));


    // finally, update the screen :)
    SDL_Flip(screen);

}

void ScreenDrawing::DrawKitSetupMenu(){
	vector<string> valueList;
	std::vector<DrumKitComponent*> *dkCompList;
	unsigned int selItem;
	Trigger *dkTrig;

	// TODO : allow changing kit name in kit setup
	// TODO : allow changing REVERB and EQ of kit.

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
	// TODO : Display basic informations about trigger in right panel



	DrawList(valueList, 0, 21, 100, 219, selItem);

	// Draw a line at right of the list :
	line(screen, 100, 20, 100, 239, SDL_MapRGB(screen->format, 255, 255, 255));


    // finally, update the screen :)
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

    // finally, update the screen :)
    SDL_Flip(screen);
}

void ScreenDrawing::DrawGlobalSettingsMenu(){

	// Clean the screen
	fillBackground();

	DrawLabel("Global Settings" , 18, 100, 0, false);
	line(screen, 0, 20, 319, 20, SDL_MapRGB(screen->format, 255, 255, 255));

	/* TODO : Global settings to be set :
	 * Volume
	 * Reverb	 (TO BE DONE)
	 * Equalizer (TO BE DONE)
	 * Triggers
	 * 		Trigger List
	 * 			Name
	 * 			Type
	 * 			Signal Curve
	 * 			Threshold
	 * 			Max Value
	 * 			Mute Group
	 * 			CrossTalk Group
	 * 			Mask Time
	 * 			Dynamic Trigger
	 * 			Foot Splash Sensitivity
	 * 			Controller Resolution
	 * Instrument Fade-Out Time
	 * Auto PowerOff Delay
	 * Inv. Rot. Sw.
	 */


    // finally, update the screen :)
    SDL_Flip(screen);

}

void ScreenDrawing::DrawList(std::vector<std::string> listText, int x, int y, int w, int h, unsigned int selectedItem){
	SDL_Surface *ListSurface;
	SDL_Surface *Container;
	SDL_Color white={255,255,255};
	SDL_Rect position;
	SDL_Rect positionList;

	position.x=x;
	position.y=y;

	// We center the list on the middle : the selected item is always on center .
	positionList.x=0;
	positionList.y=(h/2)-(selectedItem*20);

	unsigned int i; // List index
	unsigned int listHeight;
	// With a 18 font size, each line should be about 20 pixel high.
	listHeight=listText.size()*20;

	//Create the container surface :
	Container=SDL_CreateRGBSurface(SDL_HWSURFACE,w, h, 16,0,0,0,0);


	// Create the receiving surface :
	ListSurface=SDL_CreateRGBSurface(SDL_HWSURFACE,w, listHeight, 16,0,0,0,0);

	// Fill the receiving surface :
	for (i=0; i<listText.size(); i++){
		DrawLabelToList(ListSurface, listText[i],18,0,i*20,white,(selectedItem==i?true:false));

	}

	SDL_SetColorKey(ListSurface, SDL_SRCCOLORKEY, SDL_MapRGB(ListSurface->format, 0, 0, 0));
	SDL_SetColorKey(Container, SDL_SRCCOLORKEY, SDL_MapRGB(Container->format, 0, 0, 0));

	SDL_BlitSurface(ListSurface, NULL, Container, &positionList); /* Blit List to the container*/
	SDL_BlitSurface(Container, NULL, screen, &position); /* Blit container to screen*/



	SDL_FreeSurface( ListSurface );
	SDL_FreeSurface( Container );
	ListSurface=NULL;
	Container=NULL;

}



void ScreenDrawing::RefreshScreen(){
	// Call the function to draw the screen :

	(*this.*refreshFunction)();

}

void fillBackground(){
	// Draw a gradient :

	SDL_Rect dims;
	dims.x=0;
	dims.w=320;
	dims.h=4;

	for (unsigned int i=0;i<80;i++){
		dims.y=i*4;
		SDL_FillRect(screen, &dims, SDL_MapRGB(screen->format, i, i, i));

	}

}

