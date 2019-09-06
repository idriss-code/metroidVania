#include "Player.h"
#include <iostream>
#include "util/fonctionDessin.h"
#include "util/fonctionTTF.h"
#include "gfx/SDL2_rotozoom.h"
#include "CustomCollection.h"
#include "Bullet.h"
#include "core/Game.h"
#include "Scene/ScreenMessage.h"
extern TTF_Font* numberFont;
extern SDL_Color GRIS;

extern SDL_Window *ecran;
extern Game* game;

Player::Player():pvBarre(m_pv,m_pvMax),xpBarre(m_xp,m_xpLvlSuivant)
{
    m_height=64;
    m_width=20;
    SDL_Surface* sprite= IMG_Load("./data/sprite/metroid.png");
    m_sprite2= rotozoomSurfaceXY(sprite,0,2,2,0);
    m_sprite3= rotozoomSurfaceXY(sprite,0,-2,2,0);
    m_sprite=SDL_CreateRGBSurface(0,m_width,m_height,32,0,0,0,0);
    SDL_FillRect(m_sprite,NULL,SDL_MapRGB(m_sprite->format,255,255,255));

    speed=8;
    m_xp=0;
    m_lvl=1;
    m_xpLvlSuivant=XP_LVL=33;

    m_pv=m_pvMax=100;

    pvBarre.setLLL();
    pvBarre.setPosition(10,10);
    pvBarre.setColor(50,255,50);

    xpBarre.setLLL();
    xpBarre.setPosition(10,30);
    xpBarre.setColor(200,50,50);

    for (int i=0;i<10;i++){
        key[i]=false;
    }

}

void  Player::init(int x,int y)
{
    m_posX=x;
    m_posY=y;

    m_velX=0;
    m_velY=0;

    falling = true;
    orientation=RIGHT;
}


Player::~Player()
{
    SDL_FreeSurface(m_sprite);
}

void Player::fire(CustomCollection<Bullet>* bullets)
{
    if(orientation==RIGHT){
        bullets->add(new Bullet(this->posX()+10,this->posY()-10,0,Bullet::AMI));
    }else{
        bullets->add(new Bullet(this->posX()-10,this->posY()-10,M_PI,Bullet::AMI));
    }
}


void Player::draw()
{
    SDL_Rect pos;
    pos.x=SDL_GetWindowSurface(ecran)->w/2-m_sprite->w/2;
    pos.y=SDL_GetWindowSurface(ecran)->h/2-m_sprite->h/2;
    SDL_BlitSurface(m_sprite,NULL,SDL_GetWindowSurface(ecran),&pos);
    if(orientation==RIGHT)
    {
        pos.x=SDL_GetWindowSurface(ecran)->w/2-m_sprite2->w/2;
        pos.y=SDL_GetWindowSurface(ecran)->h/2-m_sprite2->h/2;
        SDL_BlitSurface(m_sprite2,NULL,SDL_GetWindowSurface(ecran),&pos);
    }else{
        pos.x=SDL_GetWindowSurface(ecran)->w/2-m_sprite3->w/2;
        pos.y=SDL_GetWindowSurface(ecran)->h/2-m_sprite3->h/2;
        SDL_BlitSurface(m_sprite3,NULL,SDL_GetWindowSurface(ecran),&pos);

    }
    pos.x=game->screenW()/2;
    pos.y= 20;
    afficheIntSurInt(pos,posX(),posY(),ecran,numberFont,GRIS);
    pos.x=game->screenW()/3;
    afficheInt(pos,xp(),ecran,numberFont,GRIS);

    pvBarre.afficheGD(ecran);
    xpBarre.afficheBH(ecran);
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

int Player::gainXp(int val,Scene* parent)
{
    m_xp+=val;
    while(m_xp>=m_xpLvlSuivant){

        m_xp-=m_xpLvlSuivant;
        m_xpLvlSuivant=m_lvl*XP_LVL;

        m_lvl++;
        ScreenMessage::loach("Level UP",parent,10);
    }
    return m_xp;
}

void Player::damage(int val)
{
    m_pv-=val;
    if(orientation==LEFT){
        m_velX=10;
    }else{
        m_velX=-10;
    }
}
