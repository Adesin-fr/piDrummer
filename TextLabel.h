/*
 * DrawLabel.h
 *
 *  Created on: 28 juil. 2016
 *      Author: ulle0009
 */

#ifndef TEXTLABEL_H_
#define TEXTLABEL_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include "Settings.h"
#include "SDLFontStore.h"

extern Settings myglobalSettings;
extern SDL_Surface* screen;
extern unsigned int labelScrollOffset;
extern SDLFontStore myFontstore;


class TextLabel {

	public:

		enum TextAlign{
			LEFT_ALIGN,
			CENTER_ALIGN,
			RIGHT_ALIGN
		};

		TextLabel();
		TextLabel(std::string text, unsigned int xPos, unsigned int yPos);
		void doDraw();
		virtual ~TextLabel();

	unsigned int getFontSize() const {
		return m_fontSize;
	}

	void setFontSize(unsigned int fontSize) {
		m_fontSize = fontSize;
	}

	unsigned int getMaxWidth() const {
		return m_maxWidth;
	}

	void setMaxWidth(unsigned int maxWidth) {
		m_maxWidth = maxWidth;
	}

	const std::string& getText() const {
		return m_text;
	}

	void setText(const std::string& text) {
		m_text = text;
	}

	TextLabel::TextAlign getTextAlignment() const {
		return m_TextAlignment;
	}

	void setTextAlignment(TextLabel::TextAlign textAlignment) {
		m_TextAlignment = textAlignment;
	}

	SDL_Color getTextColor() const {
		return m_textColor;
	}

	void setTextColor(SDL_Color textColor) {
		m_textColor = textColor;
	}

	bool isTextSelected() const {
		return m_textSelected;
	}

	void setTextSelected(bool textSelected) {
		m_textSelected = textSelected;
	}

	int getXPos() const {
		return m_xPos;
	}

	void setXPos(int xPos) {
		m_xPos = xPos;
	}

	int getYPos() const {
		return m_yPos;
	}

	void setYPos(int yPos) {
		m_yPos = yPos;
	}

	void setDrawingSurface(SDL_Surface *drawingSurface) {
		m_drawingSurface = drawingSurface;
	}

	private:
		std::string m_text;
		unsigned int m_fontSize;
		int m_xPos;
		int m_yPos;
		unsigned int m_maxWidth;
		TextLabel::TextAlign m_TextAlignment;
		SDL_Color m_textColor;
		bool m_textSelected;
		SDL_Surface *m_drawingSurface;


};

#endif /* TEXTLABEL_H_ */
