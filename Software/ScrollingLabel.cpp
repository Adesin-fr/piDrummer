/*
 * ScrollingLabel.cpp
 *
 *  Created on: 26 juil. 2016
 *      Author: ulle0009
 */

#include "ScrollingLabel.h"

ScrollingLabel::ScrollingLabel() {
	m_text="";
	m_DrawSurface=NULL;
	m_selected=false;
	m_fontSize=18;
	m_scrollOffset=0;
	xPos=0;
	yPos=0;
	maxHeight=0;
	maxWidth=0;
}


ScrollingLabel::ScrollingLabel(SDL_Surface *drawSurface, std::string text, unsigned int fontSize, bool selected) {
	m_text=text;
	m_DrawSurface=drawSurface;
	m_selected=selected;
	m_fontSize=fontSize;
	m_scrollOffset=0;
	xPos=0;
	yPos=0;
	maxHeight=0;
	maxWidth=0;

}


ScrollingLabel::~ScrollingLabel() {

}

void ScrollingLabel::setDrawSurface( SDL_Surface *drawSurface) {
	m_DrawSurface = drawSurface;
}

unsigned int ScrollingLabel::getFontSize() const {
	return m_fontSize;
}

void ScrollingLabel::setFontSize(unsigned int fontSize) {
	m_fontSize = fontSize;
}

const std::string& ScrollingLabel::getText() const {
	return m_text;
}

void ScrollingLabel::setText(const std::string& text) {
	m_text = text;
}

bool ScrollingLabel::isSelected() const {
	return m_selected;
}

void ScrollingLabel::setSelected(bool selected) {
	m_selected = selected;
}
