/*
 * SDLFontStore.h
 *
 *  Created on: 5 août 2016
 *      Author: ulle0009
 */

#ifndef SDLFONTSTORE_H_
#define SDLFONTSTORE_H_

#include <vector>
#include <string>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "SDLFont.h"

class SDLFontStore {
	public:
		SDLFontStore();
		virtual ~SDLFontStore();

		TTF_Font *getFont(std::string fontFile, unsigned int fontSize);
	private:
		std::vector <SDLFont*> myFonts;
};




#endif /* SDLFONTSTORE_H_ */
