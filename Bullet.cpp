#include "Bullet.h"
#include <iostream>
#include <cmath>
#include <SDL_image.h>

extern SDL_Window *ecran;

Bullet::Bullet(int x, int y, float angle,from fm)
{
    posX=x;
    posY=y;
    velX=cos(angle)*25;
    velY=sin(angle)*25;
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
    m_sprite1=IMG_Load("./data/sprite/bullet1.png");
    m_sprite2=IMG_Load("./data/sprite/bullet2.png");
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
