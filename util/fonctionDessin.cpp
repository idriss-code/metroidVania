#include "fonctionDessin.h"

SDL_Rect Trajectoire(int x1, int y1, int x2, int y2,float v)
{
    SDL_Rect rect;
    if (abs(y2-y1)+abs(x2-x1)>v)
    {
        float angle=atan2(y2-y1,x2-x1);

        rect.x=x1+v*cos(angle);
        rect.y=y1+v*sin(angle);
    }

    else rect.x=x2,rect.y=y2;
    return rect;
}



 void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)

{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp)
    {
    case 1:
        *p = pixel;
        break;
    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void setPixelVerif(SDL_Surface *surface,int x, int y, Uint32 coul)
{
  if (x >= 0 && x < surface->w &&
      y >= 0 && y < surface->h)
    setPixel(surface,x, y, coul);
}


void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void ligne(SDL_Surface *surface,int x1, int y1, int x2, int y2, Uint32 coul)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */

    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    setPixelVerif(surface,x, y, coul);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(surface,x, y, coul);
    }

  } else {
    /* parcours par l'axe horizontal */

    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    setPixelVerif(surface,x, y, coul);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(surface,x, y, coul);
    }
  }
}


void ligneHorizontale(SDL_Surface *surface,int x, int y, int w, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;

  SDL_FillRect(surface, &r, coul);
}

void ligneVerticale(SDL_Surface *surface,int x, int y, int h, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = 1;
  r.h = h;

  SDL_FillRect(surface, &r, coul);
}

void rectangle(SDL_Surface *surface,int x, int y, int w, int h, Uint32 coul)
{
  ligneHorizontale(surface,x, y, w, coul);
  ligneHorizontale(surface,x, y + h - 1, w, coul);
  ligneVerticale(surface,x, y + 1, h - 2, coul);
  ligneVerticale(surface,x + w - 1, y + 1, h - 2, coul);
}

void cercle(SDL_Surface *surface,int cx, int cy, int rayon, int coul)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    setPixelVerif(surface,cx + x, cy + y, coul);
    setPixelVerif(surface,cx + y, cy + x, coul);
    setPixelVerif(surface,cx - x, cy + y, coul);
    setPixelVerif(surface,cx - y, cy + x, coul);
    setPixelVerif(surface,cx + x, cy - y, coul);
    setPixelVerif(surface,cx + y, cy - x, coul);
    setPixelVerif(surface,cx - x, cy - y, coul);
    setPixelVerif(surface,cx - y, cy - x, coul);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}

void disque(SDL_Surface *surface,int cx, int cy, int rayon, int coul)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    ligneHorizontale(surface,cx - x, cy - y, 2 * x + 1, coul);
    ligneHorizontale(surface,cx - x, cy + y, 2 * x + 1, coul);
    ligneHorizontale(surface,cx - y, cy - x, 2 * y + 1, coul);
    ligneHorizontale(surface,cx - y, cy + x, 2 * y + 1, coul);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}
