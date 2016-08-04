/*
 * DrawLabel.cpp
 *
 *  Created on: 28 juil. 2016
 *      Author: ulle0009
 */

#include "TextLabel.h"

using namespace std;

TextLabel::TextLabel() {
	m_TextAlignment=TextLabel::LEFT_ALIGN;
	m_xPos=0;
	m_yPos=0;
	m_maxWidth=2000;
	m_fontSize=18;
	m_drawingSurface=screen;
	m_textColor=(SDL_Color){255,255,255};
	m_textSelected=false;
	fontLoaded=false;
	myFont=NULL;
}

TextLabel::TextLabel(std::string text, unsigned int xPos, unsigned int yPos){
	m_text=text;
	m_TextAlignment=TextLabel::LEFT_ALIGN;
	m_xPos=xPos;
	m_yPos=yPos;
	m_maxWidth=2000;
	m_fontSize=18;
	m_drawingSurface=screen;
	m_textColor=(SDL_Color){255,255,255};
	m_textSelected=false;
	fontLoaded=false;
	myFont=NULL;
}

void TextLabel::doDraw(){
	SDL_Rect position;
	SDL_Color invertColor;

	string fontPath = myglobalSettings.getUserDirectory() + "/.urDrummer/res/arial.ttf";

	if ( fontLoaded==false ){
		myFont = TTF_OpenFont(fontPath.c_str(), m_fontSize);
	}

	SDL_Surface *texte ;

	texte = TTF_RenderText_Blended(myFont, m_text.c_str(), m_textColor);

	//calculate text position :

	position.y=m_yPos;
	switch(m_TextAlignment){
		case TextLabel::LEFT_ALIGN:
			position.x=m_xPos;
			break;
		case TextLabel::CENTER_ALIGN:
			position.x=m_xPos-(texte->w/2);
			break;
		case TextLabel::RIGHT_ALIGN:
			position.x=m_xPos-texte->w;
			break;
	}

	// Delete the generated text : it will be re-generated !
	delete texte;

	if (m_textSelected){

		invertColor.b=255-m_textColor.b;
		invertColor.r=255-m_textColor.r;
		invertColor.g=255-m_textColor.g;

		texte = TTF_RenderText_Blended(myFont, m_text.c_str(), invertColor);

		SDL_Surface *BGSurf;
		BGSurf=SDL_CreateRGBSurface(SDL_HWSURFACE,texte->w, texte->h, 16,0,0,0,0);
		SDL_FillRect(BGSurf, NULL, SDL_MapRGB(BGSurf->format, m_textColor.r, m_textColor.g, m_textColor.b));
		SDL_BlitSurface(BGSurf, NULL, screen, &position); /* Blit background*/
		delete BGSurf;
	}else{
		texte = TTF_RenderText_Blended(myFont, m_text.c_str(), m_textColor);
	}

	// TODO : offset blitting position respectif to labelScrollOffset and maxWidth

	SDL_BlitSurface(texte, NULL, screen, &position); /* Blit text */

	delete texte;

}


TextLabel::~TextLabel() {
}

