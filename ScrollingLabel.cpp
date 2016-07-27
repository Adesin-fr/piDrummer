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
	m_scrollSpeed=0.5f;
	m_scrollOffset=0;
}


ScrollingLabel::ScrollingLabel(SDL_Surface drawSurface, std::string text, unsigned int fontSize, bool selected) {
	m_text="";
	m_DrawSurface=NULL;
	m_selected=false;
	m_fontSize=18;
	m_scrollSpeed=0.5f;
	m_scrollOffset=0;
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

unsigned int ScrollingLabel::getScrollOffset() const {
	return m_scrollOffset;
}

void ScrollingLabel::setScrollOffset(unsigned int scrollOffset) {
	m_scrollOffset = scrollOffset;
}

float ScrollingLabel::getScrollSpeed() const {
	return m_scrollSpeed;
}

void ScrollingLabel::setScrollSpeed(float scrollSpeed) {
	m_scrollSpeed = scrollSpeed;
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
