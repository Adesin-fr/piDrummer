/*
 * SDLFont.cpp
 *
 *  Created on: 5 août 2016
 *      Author: ulle0009
 */

#include "SDLFont.h"

SDLFont::SDLFont() {
	fontSize=0;
	fontReference=NULL;

}

SDLFont::~SDLFont() {
	TTF_CloseFont(fontReference);
}

