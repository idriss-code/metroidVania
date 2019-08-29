#include "Player.h"
#include <iostream>
#include "util/fonctionDessin.h"

extern TTF_Font* numberFont;
extern SDL_Color GRIS;

extern SDL_Window *ecran;

Player::Player()
{
    m_width=m_height=50;

    //m_sprite=IMG_Load("./data/sprite/blob.png");
    m_sprite=SDL_CreateRGBSurface(0,m_width,m_height,32,0,0,0,0);
    SDL_FillRect(m_sprite,NULL,SDL_MapRGB(m_sprite->format,255,255,255));

    speed=8;
}

void  Player::init(int x,int y)
{
    m_posX=x;
    m_posY=y;

    m_velX=0;
    m_velY=0;

    falling = true;
}


Player::~Player()
{
    SDL_FreeSurface(m_sprite);
}

void Player::draw()
{
    SDL_Rect pos;
    pos.x=SDL_GetWindowSurface(ecran)->w/2-m_sprite->w/2;
    pos.y=SDL_GetWindowSurface(ecran)->h/2-m_sprite->h/2;
    SDL_BlitSurface(m_sprite,NULL,SDL_GetWindowSurface(ecran),&pos);
}


void Player::moov(int vx,int vy)
{
    m_posX+=vx;
    m_posY+=vy;
}

void Player::moov()
{
    m_posX+=velX();
    m_posY+=velY();
}
