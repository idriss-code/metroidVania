#ifndef FONCTIONDESSIN_H_INCLUDED
#define FONCTIONDESSIN_H_INCLUDED
#include <SDL.h>
#include <cmath>

//  divers fonction servant a dessiner et deplacer des sprites

using namespace std;


//  deplace un sprite x1 y1 = position actuel x2 y2 position a atteindre
SDL_Rect Trajectoire(int x1, int y1, int x2, int y2,float v);

// série de fonction pour tracer des ligne d'un poit x1 y1 a un point x2 y2
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void setPixelVerif(SDL_Surface *surface,int x, int y, Uint32 coul);
void echangerEntiers(int* x, int* y);
void ligne(SDL_Surface *surface,int x1, int y1, int x2, int y2, Uint32 coul);//  *surface ou dessiner  coul = couleur
void ligneHorizontale(SDL_Surface *surface,int x, int y, int w, Uint32 coul);
void ligneVerticale(SDL_Surface *surface,int x, int y, int h, Uint32 coul);
void rectangle(SDL_Surface *surface,int x, int y, int w, int h, Uint32 coul);
void cercle(SDL_Surface *surface,int cx, int cy, int rayon, int coul);
void disque(SDL_Surface *surface,int cx, int cy, int rayon, int coul);

#endif // FONCTIONDESSIN_H_INCLUDED
