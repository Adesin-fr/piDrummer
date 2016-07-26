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
#include "Settings.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <libconfig.h++>
#include <map>
#include "Draw.h"
#include "Trigger.h"


class ScreenDrawing{
public:
	ScreenDrawing();
	virtual ~ScreenDrawing();

	void setScreenReference(SDL_Surface *screenReference);
	void setSettingsReference(Settings *globalSettingsReference);
	void setLastTriggerVelocity(unsigned int TriggerInput, unsigned int TriggerVelocity);

	void DrawSplashScreen();

	void handleKeyPress(unsigned int keyEvent);

	void DrawMainScreen();
	void DrawMainMenu();
	void DrawKitSelect();
	void DrawMetronomeSetup();
	void DrawAudioPlayer();
	void DrawTrainingMenu();
	void DrawKitSetupMenu();
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
	SDL_Surface *myScreenReference;
	Settings *myGlobalSettings;
	std::vector<std::string> myCurrentMenuPath;
	std::vector<unsigned int> myCurrentSelectedMenuItem;


	// Screen & SDL variables :
	bool m_screenNeedRefresh;
	int m_lastFontSizeUsed;
	TTF_Font *myFont= NULL;

	// function used to refresh Screen :
	void(ScreenDrawing::*refreshFunction)(void);
	unsigned int maxSelectedMenuItem;

	bool m_tmpBoolValue;
	unsigned int m_tmpIntValue;
	float m_tmpFloatValue;
	std::string m_tmpStringValue;

	std::vector<unsigned int> m_triggerLastHitValues;

};


#endif /* SCREENDRAWING_H_ */
