#include "Eni.h"
#include <iostream>
extern SDL_Window *ecran;
#include "../gfx/SDL2_rotozoom.h"

#include "CustomCollection.h"
#include "Bullet.h"
#include "util/benrandom.h"
#include "Item/Life.h"

#include "Player.h"
extern Player player;

#include "util/benrandom.h"

Eni::Eni(int x,int y)
{
    m_velX=0;
    m_velY=0;

    spriteNumber=0;
    spriteCountDown=1;
    animationDirection=1;
    damaged=false;

    fireCooldown=50;
    fireTime=de(fireCooldown);
}


Eni::~Eni()
{
    SDL_FreeSurface(m_sprite);
    SDL_FreeSurface(m_spriteI);
}

void Eni::update(MapProto* mapProto)
{
    moov();
}

void Eni::draw(int camX,int camY)
{
    SDL_Rect pos;
    SDL_Rect src;

    enum {LEFT,RIGHT};
    int orientation;
    if(velX()<0){
        orientation=LEFT;
    }else{
        orientation=RIGHT;
    }



    #ifdef DEBUG
    //affichage hitBox
    SDL_Surface* hitBoxSprite=SDL_CreateRGBSurface(0,hitBox().w,hitBox().h,32,0,0,0,0);
    SDL_FillRect(hitBoxSprite,NULL,SDL_MapRGB(hitBoxSprite->format,255,255,255));
    pos.x=hitBox().x-camX;
    pos.y=hitBox().y-camY;
    SDL_BlitSurface(hitBoxSprite,NULL,SDL_GetWindowSurface(ecran),&pos);
    SDL_FreeSurface(hitBoxSprite);
    //fin affichage hitBox
    #endif

    SDL_Surface* sprite;
    switch(orientation){
        case RIGHT:
            sprite=m_sprite;
            break;
        case LEFT:
            sprite=m_spriteI;
            break;
    }

    src.y=0;
    src.w=spriteWidth;
    src.h=spriteHeight;

        if(--spriteCountDown<0){
            spriteNumber+=animationDirection;
            spriteCountDown=1;
        }

    if(spriteNumber>spriteNumMax){
            spriteNumber=0;
    }
    if(spriteNumber<0){
            spriteNumber=spriteNumMax;
    }

    pos.x=m_posX-camX-spriteWidth/2;
    pos.y=m_posY-camY-spriteHeight/2;
    switch(orientation){
        case RIGHT:
            src.x=spriteWidth*spriteNumber;
            break;
        case LEFT:
            src.x=sprite->w-(spriteWidth*(1+spriteNumber));
            break;
    }
    //si il y a dommage on créé un sprite rouge
    if(damaged){
        sprite =rotozoomSurfaceXY(sprite,0,1,1,0);
        SDL_SetSurfaceColorMod(sprite,255,0,0);
    }

    SDL_BlitSurface(sprite,&src,SDL_GetWindowSurface(ecran),&pos);

    //si il y a dtruit on créé le sprite rouge
    if(damaged){
        damaged = false;
        SDL_FreeSurface(sprite);
    }
}

void Eni::moov()
{
    m_posX+=velX();
    m_posY+=velY();
}

void Eni::fireUpdate(CustomCollection<Bullet>* bullets)
{
    if(--fireTime<=0){
        fireTime=fireCooldown;
        float angle=atan2(player.posY()-posY(),player.posX()-posX());
        bullets->add(new Bullet(this->posX(),this->posY(),angle,Bullet::ENI,10));
        changeOrientation();

        Mix_PlayChannel(-1, fireSound, 0);

        #ifdef DEBUG
            cout<<"fire"<<endl;
        #endif
    }
}

#define ABS(X) ((((X)<0)?(-(X)):(X)))
void Eni::changeOrientation()
{
    if(player.posX()>posX()){
        m_velX=ABS(m_velX);
    }else{
        m_velX=-ABS(m_velX);
    }
}

void Eni::onDying(CustomCollection<Item>* items)
{
    if(de(8)==1){
        items->add(new Life(posX(),posY()));
    }
}

void Eni::loadSound()
{
    //**************** sfx ****************
    fireSound=Mix_LoadWAV("data/son/LASER.WAV");
    if(!fireSound) {
        std::cerr<<"Mix_LoadWAV: "<< Mix_GetError()<<std::endl;
    }

    deathSound=Mix_LoadWAV("data/son/Randomize18.WAV");
    if(!deathSound) {
        std::cerr<<"Mix_LoadWAV: "<< Mix_GetError()<<std::endl;
    }
    //**************** sfx *****************
}

void Eni::unloadSound()
{
    //**************** sfx ****************
    Mix_FreeChunk(fireSound);
    fireSound=NULL;
    Mix_FreeChunk(deathSound);
    deathSound=NULL;
    //**************** sfx ****************
}



void Eni::deathSoundPlay()
{
    Mix_PlayChannel(-1, deathSound, 0);
}

Mix_Chunk * Eni::fireSound=NULL;
Mix_Chunk * Eni::deathSound=NULL;

