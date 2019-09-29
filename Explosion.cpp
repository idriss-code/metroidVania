#include "Explosion.h"
#include <iostream>
#include <cmath>
#include "gfx/SDL2_rotozoom.h"

extern SDL_Window *ecran;

Explosion::Explosion(int x, int y)
{
    posX=x;
    posY=y;
    m_toDelete=false;
    state=0;

    spriteW=67*2;
    spriteH=48*2;

    maxSprite=12;
}

Explosion::~Explosion()
{

}

void Explosion::update()
{
    if(state++ >= maxSprite){
        m_toDelete=true;
    }
}

void Explosion::draw(int camX,int camY)
{
    SDL_Rect pos;
    SDL_Rect source;
    source.x=spriteW*state;
    source.y=0;
    source.h=spriteH;
    source.w=spriteW;
    pos.x=posX-camX-source.w/2;
    pos.y=posY-camY-source.h/2;
    SDL_BlitSurface(sprite,&source,SDL_GetWindowSurface(ecran),&pos);
}

void Explosion::load()
{
    SDL_Surface* temp=IMG_Load("./data/sprite/enemy-death.png");
    sprite=rotozoomSurfaceXY(temp,0,2,2,0);
    SDL_FreeSurface(temp);

}

void Explosion::unload()
{
    SDL_FreeSurface(sprite);
}

SDL_Surface *Explosion::sprite=NULL;
