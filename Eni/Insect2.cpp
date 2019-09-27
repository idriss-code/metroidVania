#include "Insect2.h"
#include "../gfx/SDL2_rotozoom.h"

Insect2::Insect2(int x,int y):FlyingEni(x,y)
{
    //ctor
    m_pv=3;

    m_height=132;
    m_width=90;
    /*
    m_sprite=SDL_CreateRGBSurface(0,m_width,m_height,32,0,0,0,0);
    SDL_FillRect(m_sprite,NULL,SDL_MapRGB(m_sprite->format,255,255,255));
    */

    SDL_Surface* sprite=IMG_Load("./data/sprite/bosswasp.png");
    m_spriteI=rotozoomSurfaceXY(sprite,0,2,2,0);
    m_sprite=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);


    m_posX=x ;
    m_posY=y ;

    m_xp=10;


    spriteNumMax=2;
    spriteWidth=128*2;
    spriteHeight=96*2;

    animationDirection=-1;

}

Insect2::~Insect2()
{
    //dtor
}
