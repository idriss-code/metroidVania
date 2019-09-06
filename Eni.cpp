#include "Eni.h"
#include <iostream>
extern SDL_Window *ecran;

Eni::Eni(int x,int y)
{
    m_height=64;
    m_width=32;

    m_posX=x ;
    m_posY=y ;

    m_sprite=SDL_CreateRGBSurface(0,m_width,m_height,32,0,0,0,0);
    SDL_FillRect(m_sprite,NULL,SDL_MapRGB(m_sprite->format,255,255,255));

    m_velX=0;
    m_velY=0;

    m_xp=10;
}


Eni::~Eni()
{
//free surface
}

void Eni::update(MapProto* mapProto)
{
    moov();
}

void Eni::draw(int camX,int camY)
{
    SDL_Rect pos;
    pos.x=m_posX-camX-m_sprite->w/2;
    pos.y=m_posY-camY-m_sprite->h/2;
    SDL_BlitSurface(m_sprite,NULL,SDL_GetWindowSurface(ecran),&pos);
}

void Eni::moov()
{
    m_posX+=velX();
    m_posY+=velY();
}
