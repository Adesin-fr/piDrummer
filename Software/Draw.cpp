/*
 * Draw.cpp
 *
 *  Created on: 16 juil. 2016
 *      Author: ludovic
 */

#include "Draw.h"



//puts a pixel at the specifiated location
void pxl(SDL_Surface *surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
    case 1:
        *p = color;
        break;

    case 2:
        *(Uint16 *)p = color;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        } else {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = color;
        break;
    }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________
//puts a pixel at the specifiated location (clipped)

Uint8 Cpxl(SDL_Surface *surface, int x, int y, Uint32 color)
{
    if( ((x>=0) && (x<surface->w))  &&  ((y>=0) && (y<surface->h))    )
    {
        pxl(surface, x, y, color);
        return 0;
    }else{
        return 1;
    }
}



// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________
// gets the value of a pixel at the specifiated location

Uint32 getpxl(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;
    }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws a filled rectangle
void frame(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = h;

    SDL_FillRect(surface, &area, color);
}

// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws a filled rectangle
void cls(SDL_Surface* surface, Uint32 color)
{
    SDL_FillRect(surface, NULL, color);
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws an horizontal line
void Hline(SDL_Surface* surface, int x, int y, int w, Uint32 color)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = 1;

    SDL_FillRect(surface, &area, color);
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws a vertical line
void Vline(SDL_Surface* surface, int x, int y, int h, Uint32 color)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = 1;
    area.h = h;

    SDL_FillRect(surface, &area, color);
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________

//Draw a rectangle
void box(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color)
{
  Hline(surface, x, y, w, color);
  Hline(surface, x, y + h - 1, w, color);
  Vline(surface, x, y + 1, h - 2, color);
  Vline(surface, x + w - 1, y + 1, h - 2, color);
}




// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________

//switches integers
void SwitchInt(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void line(SDL_Surface *surface, int x1, int y1, int x2, int y2, Uint32 color)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */

    if (y1 > y2) {
      SwitchInt(&x1, &x2);
      SwitchInt(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    Cpxl(surface, x, y, color);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
        x += xincr;
        d += aincr;
      } else
        d += bincr;

      Cpxl(surface, x, y, color);
    }

  } else {
    /* parcours par l'axe horizontal */

    if (x1 > x2) {
      SwitchInt(&x1, &x2);
      SwitchInt(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    Cpxl(surface, x, y, color);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
        y += yincr;
        d += aincr;
      } else
        d += bincr;

      Cpxl(surface, x, y, color);
    }
  }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


//draws a circle
void circle(SDL_Surface* surface, int cx, int cy, int rayon, int color)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    Cpxl(surface, cx + x, cy + y, color);
    Cpxl(surface, cx + y, cy + x, color);
    Cpxl(surface, cx - x, cy + y, color);
    Cpxl(surface, cx - y, cy + x, color);
    Cpxl(surface, cx + x, cy - y, color);
    Cpxl(surface, cx + y, cy - x, color);
    Cpxl(surface, cx - x, cy - y, color);
    Cpxl(surface, cx - y, cy - x, color);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


//draws a filled circle
void disc(SDL_Surface *surface, int cx, int cy, int rayon, int color)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    Hline(surface, cx - x, cy - y, 2 * x + 1, color);
    Hline(surface, cx - x, cy + y, 2 * x + 1, color);
    Hline(surface, cx - y, cy - x, 2 * y + 1, color);
    Hline(surface, cx - y, cy + x, 2 * y + 1, color);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}


void drawSignalCurve(SDL_Surface *surface, SignalCurve *sigCurve, int xPos, int yPos, int width, int height){
	unsigned int white, lineColor, gridColor,  nbPoints;
	SDL_Point lastPoint, currentPoint;

	white	  = SDL_MapRGB(surface->format, 255, 255, 255);
	lineColor = SDL_MapRGB(surface->format, 255, 0, 0);
	gridColor = SDL_MapRGB(surface->format, 80, 80, 80);

	//  Draw a light gray grid :
	// Vertical lines :
	for (unsigned int x=0; x<8; x++){
		line(surface, xPos + (x*width/8) ,yPos, xPos + (x*width/8), yPos+height, gridColor);
	}
	// Horizontal lines :
	for (unsigned int y=0; y<8; y++){
		line(surface, xPos  ,yPos + (y*height/8), xPos + width, yPos + (y*height/8), gridColor);
	}

	// Draw the box around:
	box(surface, xPos-1, yPos-1, width+2, height+2, white);

	// Draw the curve line :
	nbPoints= sigCurve->getAllCurvePoints()->size();

	if (nbPoints<1){
		return;
	}

	// Get First point position :
	lastPoint.x=xPos;
	lastPoint.y=yPos + height - ((*sigCurve->getAllCurvePoints())[0]->yValue * height / 127 );
	if (lastPoint.y > yPos + height-1){
		lastPoint.y = yPos + height-1;
	}

	for (unsigned int i=1; i<nbPoints; i++){
		currentPoint.x=xPos + (i * width / (nbPoints-1)) ;
		currentPoint.y=yPos + height - ((*sigCurve->getAllCurvePoints())[i]->yValue * height / 127  );

		// Draw the segment :
		line(surface, lastPoint.x, lastPoint.y, currentPoint.x, currentPoint.y, lineColor);

		lastPoint.x=currentPoint.x;
		lastPoint.y=currentPoint.y;

	}

}

