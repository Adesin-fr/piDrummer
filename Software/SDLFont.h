/*
 * SDLFont.h
 *
 *  Created on: 5 août 2016
 *      Author: ulle0009
 */

#ifndef SDLFONT_H_
#define SDLFONT_H_

#include <SDL/SDL_ttf.h>
#include <string>

class SDLFont {
public:
	SDLFont();
	virtual ~SDLFont();

	unsigned int fontSize;
	TTF_Font *fontReference;
	std::string fontFile;
};

#endif /* SDLFONT_H_ */
