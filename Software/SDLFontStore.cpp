/*
 * SDLFontStore.cpp
 *
 *  Created on: 5 août 2016
 *      Author: ulle0009
 */

#include "SDLFontStore.h"


using namespace std;

SDLFontStore::SDLFontStore() {
	for (unsigned int i=0; i< myFonts.size(); i++){
		delete myFonts[i];
	}
	myFonts.clear();

}

SDLFontStore::~SDLFontStore() {

}

TTF_Font *SDLFontStore::getFont(std::string fontFile, unsigned int fontSize){
	for (unsigned int i=0; i< myFonts.size(); i++){
		SDLFont *newFont;
		newFont=myFonts[i];
		if (newFont->fontSize==fontSize && newFont->fontFile == fontFile){
			return newFont->fontReference;
		}
	}
	// If we arrive here, this mean we doesn't have the font size in our store. Add it !
	SDLFont *newFont;
	TTF_Font *newTTFFont;

	newTTFFont = TTF_OpenFont(fontFile.c_str(), fontSize);

	newFont=new SDLFont;

	newFont->fontReference = newTTFFont;
	newFont->fontSize = fontSize;
	newFont->fontFile= fontFile;

	myFonts.push_back(newFont);

	return newTTFFont;

}

