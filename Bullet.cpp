#include "Bullet.h"
#include <iostream>
#include <cmath>
#include <SDL_image.h>
#include "gfx/SDL2_rotozoom.h"

extern SDL_Window *ecran;

Bullet::Bullet(int x, int y, float angle,from fm,int speed)
{
    posX=x;
    posY=y;
    velX=cos(angle)*speed;
    velY=sin(angle)*speed;
    frm=fm;
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
    posX+=velX;
    posY+=velY;
}

void Bullet::draw(int camX,int camY)
{

    SDL_Surface *sprite;
    if(frm==AMI){
        sprite=m_sprite1;
    }else{
        sprite=m_sprite2;
    }

    SDL_Rect pos;
    pos.x=GetposX()-camX-sprite->w/2;
    pos.y=GetposY()-camY-sprite->h/2;

    SDL_BlitSurface(sprite,NULL,SDL_GetWindowSurface(ecran),&pos);
}

void Bullet::load()
{
    SDL_Surface* temp;

    temp=IMG_Load("./data/sprite/bullet1.png");
    m_sprite1=rotozoomSurfaceXY(temp,0,2,2,0);
    SDL_FreeSurface(temp);

    temp=IMG_Load("./data/sprite/bullet2.png");
    m_sprite2=rotozoomSurfaceXY(temp,0,2,2,0);
    SDL_FreeSurface(temp);
}

void Bullet::unload()
{
    SDL_FreeSurface(m_sprite1);
    SDL_FreeSurface(m_sprite2);
}

vector<Bullet> Bullet::vec;
vector<Bullet>::iterator Bullet::it;
SDL_Surface * Bullet::m_sprite1=NULL;
SDL_Surface * Bullet::m_sprite2=NULL;
