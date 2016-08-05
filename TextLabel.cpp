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
}

void TextLabel::doDraw(){
	SDL_Surface *texte ;
	SDL_Rect position, blitSize;
	SDL_Color invertColor;
	unsigned int labelWidth;
	bool scrollNeeded=false;
	TTF_Font *myFont;

	string fontPath = myglobalSettings.getUserDirectory() + "/.urDrummer/res/arial.ttf";

	myFont = TTF_OpenFont(fontPath.c_str(), m_fontSize);


	texte = TTF_RenderText_Blended(myFont, m_text.c_str(), m_textColor);

	labelWidth=texte->w;
	if (labelWidth>m_maxWidth){
		labelWidth=m_maxWidth;
		scrollNeeded=true;
	}
	// Set blitting size...
	if (scrollNeeded){
		unsigned int labelOverSizeAmount=(texte->w-m_maxWidth)+150;
		blitSize.x=(labelScrollOffset % labelOverSizeAmount);
	}else{
		blitSize.x=0;
	}

	blitSize.y=0;
	blitSize.w=labelWidth;
	blitSize.h=texte->h;

	//calculate text position :

	position.y=m_yPos;
	switch(m_TextAlignment){
		case TextLabel::LEFT_ALIGN:
			position.x=m_xPos;
			break;
		case TextLabel::CENTER_ALIGN:
			position.x=m_xPos-(labelWidth/2);
			break;
		case TextLabel::RIGHT_ALIGN:
			position.x=m_xPos-labelWidth;
			break;
	}

	// Delete the generated text : it will be re-generated !
	SDL_FreeSurface(texte);
	texte=NULL;

	if (m_textSelected){

		invertColor.b=255-m_textColor.b;
		invertColor.r=255-m_textColor.r;
		invertColor.g=255-m_textColor.g;

		texte = TTF_RenderText_Blended(myFont, m_text.c_str(), invertColor);

		SDL_Surface *BGSurf;
		BGSurf=SDL_CreateRGBSurface(SDL_HWSURFACE,labelWidth, texte->h, 16,0,0,0,0);
		SDL_FillRect(BGSurf, NULL, SDL_MapRGB(BGSurf->format, m_textColor.r, m_textColor.g, m_textColor.b));
		SDL_BlitSurface(BGSurf, NULL, screen, &position); /* Blit background*/
		SDL_FreeSurface( BGSurf);
		BGSurf=NULL;
	}else{
		texte = TTF_RenderText_Blended(myFont, m_text.c_str(), m_textColor);
	}

	SDL_BlitSurface(texte, &blitSize, screen, &position); /* Blit text */

	SDL_FreeSurface( texte);
	texte=NULL;

	TTF_CloseFont(myFont);
	myFont=NULL;
}


TextLabel::~TextLabel() {
}

