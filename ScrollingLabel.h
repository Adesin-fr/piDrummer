/*
 * ScrollingLabel.h
 *
 *  Created on: 26 juil. 2016
 *      Author: ulle0009
 */

#ifndef SCROLLINGLABEL_H_
#define SCROLLINGLABEL_H_

#include <SDL/SDL_ttf.h>
#include "Draw.h"
#include <string>


class ScrollingLabel {
public:
	ScrollingLabel();
	ScrollingLabel(SDL_Surface drawSurface, std::string text, unsigned int fontSize, bool selected);
	virtual ~ScrollingLabel();
	void setDrawSurface(SDL_Surface *drawSurface);
	unsigned int getFontSize() const;
	void setFontSize(unsigned int fontSize);
	unsigned int getScrollOffset() const;
	void setScrollOffset(unsigned int scrollOffset);
	const std::string& getText() const;
	void setText(const std::string& text);
	bool isSelected() const;
	void setSelected(bool selected);

private:
	SDL_Surface *m_DrawSurface;
	std::string m_text;
	unsigned int m_fontSize;
	unsigned int m_scrollOffset;
	bool m_selected;
	unsigned int xPos;
	unsigned int yPos;
	unsigned int maxWidth;
	unsigned int maxHeight;
};

#endif /* SCROLLINGLABEL_H_ */
