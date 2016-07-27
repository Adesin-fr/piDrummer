/*
 * Draw.h
 *
 *  Created on: 16 juil. 2016
 *      Author: ludovic
 */

#ifndef DRAW_H_
#define DRAW_H_


#include <SDL/SDL.h>



void pxl(SDL_Surface *surface, int x, int y, Uint32 color);
// Sets the pixel at (x, y) in the specified surface.

Uint32 getpxl(SDL_Surface *surface, int x, int y);
// Returns the value of a pixel at (x,y) from the specified surface.

void frame(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color);
// Draws a colored filled box at (x, y) with specified width and height.

void cls(SDL_Surface* surface, Uint32 color);
// Fill the entire surface with specified color

void Hline(SDL_Surface* surface, int x, int y, int w, Uint32 color);
// Draws and colored horizontal line at (x, y) with specified width.

void Vline(SDL_Surface* surface, int x, int y, int h, Uint32 color);
// Draws and colored horizontal line at (x, y) with specified height.

Uint8 Cpxl(SDL_Surface *surface, int x, int y, Uint32 color);
// Checks wether the pixel is in the surface before calling pxl function.

void box(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color);
// Draws a colored square or a rectangle at (x, y) with specified width and
// height.

void line(SDL_Surface *surface, int x1, int y1, int x2, int y2, Uint32 color);
// Draws a colored line from A(x, y) to B(x, y).

void circle(SDL_Surface* surface, int cx, int cy, int rayon, int color);
// Draws a colored circle with center at (x, y) and with the specified radius.

void disc(SDL_Surface *surface, int cx, int cy, int rayon, int color);
// Draws a colored filled circle with center at (x, y) and with the specified
// radius.






#endif /* DRAW_H_ */
