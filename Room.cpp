#include "Room.h"
#include "util/fonctionDessin.h"

extern SDL_Window *ecran;

Room::Room(int X,int Y,int up,int down,int left,int right)
{
    HEIGHT = 15;
    WIDTH = 15;
    x=X;
    y=Y;

    activated=false;

    side[UP]=up;
    side[DOWN]=down;
    side[LEFT]=left;
    side[RIGHT]=right;
}

Room::~Room()
{

}

void Room::draw()
{
    int xPix=x*(WIDTH-1)+270;
    int yPix=y*(HEIGHT-1)+200;
    int doorSize=3;
    SDL_Surface* screen=SDL_GetWindowSurface(ecran);
    Uint32 wallColor=SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,200,100,255);
    Uint32 doorColor=SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,0,0,0);
    Uint32 pointColor=SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,100,255,0);

    if(side[UP]!=NO){
        ligneHorizontale(screen,xPix,yPix,WIDTH,wallColor);

        if(side[UP]==DOOR){
            ligneHorizontale(screen,xPix+doorSize,yPix,WIDTH-doorSize*2,doorColor);
        }
    }
    if(side[LEFT]!=NO){
        ligneVerticale(screen,xPix,yPix,HEIGHT,wallColor);

        if(side[LEFT]==DOOR){
            ligneVerticale(screen,xPix,yPix+doorSize,HEIGHT-doorSize*2,doorColor);
        }
    }
    if(side[DOWN]!=NO){
            ligneHorizontale(screen,xPix,yPix+HEIGHT-1,WIDTH,wallColor);
        if(side[DOWN]==DOOR){
            ligneHorizontale(screen,xPix+doorSize,yPix+HEIGHT-1,WIDTH-doorSize*2,doorColor);
        }
    }
    if(side[RIGHT]!=NO){
            ligneVerticale(screen,xPix+WIDTH-1,yPix,HEIGHT,wallColor);
        if(side[RIGHT]==DOOR){
            ligneVerticale(screen,xPix+WIDTH-1,yPix+doorSize,HEIGHT-doorSize*2,doorColor);
        }
    }
    if(activated){
        disque(screen,xPix+WIDTH/2,yPix+HEIGHT/2,3,pointColor);
    }
}
