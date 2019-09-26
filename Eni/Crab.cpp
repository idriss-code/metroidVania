#include "Crab.h"
#include "../gfx/SDL2_rotozoom.h"

Crab::Crab(int x,int y):WalkingEni(x,y)
{
    //ctor
    m_pv=2;

    m_height=50;
    m_width=40;
    /*
    m_sprite=SDL_CreateRGBSurface(0,m_width,m_height,32,0,0,0,0);
    SDL_FillRect(m_sprite,NULL,SDL_MapRGB(m_sprite->format,255,255,255));
    */

    SDL_Surface* sprite=IMG_Load("./data/sprite/crab-walk.png");
    m_spriteI=rotozoomSurfaceXY(sprite,0,2,2,0);
    m_sprite=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);


    m_posX=x ;
    m_posY=y ;

    m_xp=10;


    spriteNumMax=3;
    spriteWidth=96;
    spriteHeight=64;

}

Crab::~Crab()
{
    //dtor
}
