/*
 * Screen.h
 *
 *  Created on: 15 juil. 2016
 *      Author: ludovic
 */

#ifndef SCREENDRAWING_H_
#define SCREENDRAWING_H_

#include <string>
#include <sstream>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <map>
#include <libconfig.h++>
#include <pthread.h>

#include "Settings.h"
#include "Draw.h"
#include "Trigger.h"
#include "TextLabel.h"
#include "Metronome.h"


extern SDL_Surface* screen;
extern Settings myglobalSettings;
extern const std::string urDrummerVersion;
extern unsigned int ticksNow;
extern unsigned int lastTimeScreenRefresh;
extern Metronome myMetronome;

class ScreenDrawing{
public:
	ScreenDrawing();
	virtual ~ScreenDrawing();

	void setLastTriggerVelocity(unsigned int TriggerInput, unsigned int TriggerVelocity);

	void DrawSplashScreen();

	unsigned int handleKeyPress(unsigned int keyEvent);

	void DrawMainScreen();
	void DrawMainMenu();
	void DrawKitSelect();
	void DrawMetronomeSetup();
	void DrawAudioPlayer();
	void DrawTrainingMenu();
	void DrawKitSetupMenu();
	void DrawKitSetupTriggerChoosen();
	void DrawGlobalSettingsMenu();

	void DrawSubMenuSelect();


	// "Utility" functions
	void DrawIcon(const std::string iconPath, int posX, int posY, bool selected);
	void DrawLabel(const std::string labelText, int fontSize, int posX, int posY);
	void DrawLabel(const std::string labelText, int fontSize, int posX, int posY, bool selected);
	void DrawLabel(const std::string labelText, int fontSize, int posX, int posY, SDL_Color color);
	void DrawLabel(const std::string labelText, int fontSize, int posX, int posY, SDL_Color color, bool selected);
	void DrawLabelToList(SDL_Surface *dest, std::string labelText, int fontSize, int posX, int posY, SDL_Color color, bool selected);
	void DrawList(std::vector<std::string> listText, int x, int y, int w, int h,unsigned int selectedItem);


	void RefreshScreen();

private:
	std::vector<std::string> myCurrentMenuPath;
	std::vector<unsigned int> myCurrentSelectedMenuItem;


	// Screen & SDL variables :
	bool m_screenNeedRefresh;
	int m_lastFontSizeUsed;

	// function used to refresh Screen :
	void(ScreenDrawing::*refreshFunction)(void);
	unsigned int maxSelectedMenuItem;

	bool m_tmpBoolValue;
	unsigned int m_tmpIntValue;
	float m_tmpFloatValue;
	std::string m_tmpStringValue;

	std::vector<unsigned int> m_triggerLastHitValues;

	// Pointer to Selected DK Component being edited.
	DrumKitComponent* m_SelectedDK;

};


#endif /* SCREENDRAWING_H_ */
