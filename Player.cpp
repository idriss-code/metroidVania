#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include "util/fonctionDessin.h"
#include "util/fonctionTTF.h"
#include "gfx/SDL2_rotozoom.h"
#include "CustomCollection.h"
#include "Bullet.h"
#include "core/Game.h"
#include "Scene/ScreenMessage.h"
extern TTF_Font* numberFont;
extern SDL_Color JAUNE;

extern SDL_Window *ecran;
extern Game* game;

Player::Player():pvBarre(m_pv,m_pvMax),xpBarre(m_xp,m_xpLvlSuivant)
{
    m_height=64;
    m_width=20;
    speed=12;

    spriteWidth=80*2;
    spriteHeight=80*2;


    SDL_Surface* sprite;
    //duckSprite
    sprite=IMG_Load("./data/sprite/player-duck.png");
    duckSprite=rotozoomSurfaceXY(sprite,0,2,2,0);
    duckSpriteI=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);

    //jumpSprite
    sprite=IMG_Load("./data/sprite/player-jump.png");
    jumpSprite=rotozoomSurfaceXY(sprite,0,2,2,0);
    jumpSpriteI=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);

    //fireSprite
    sprite=IMG_Load("./data/sprite/player-stand.png");
    fireSprite=rotozoomSurfaceXY(sprite,0,2,2,0);
    fireSpriteI=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);

    //runSprite
    sprite=IMG_Load("./data/sprite/player-run.png");
    runSprite=rotozoomSurfaceXY(sprite,0,2,2,0);
    runSpriteI=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);

    //runFireSprite
    sprite=IMG_Load("./data/sprite/player-run-shoot.png");
    runFireSprite=rotozoomSurfaceXY(sprite,0,2,2,0);
    runFireSpriteI=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);

    //idleSprite
    sprite=IMG_Load("./data/sprite/player-idle.png");
    idleSprite=rotozoomSurfaceXY(sprite,0,2,2,0);
    idleSpriteI=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);

    //hurtSprite
    sprite=IMG_Load("./data/sprite/player-hurt.png");
    hurtSprite=rotozoomSurfaceXY(sprite,0,2,2,0);
    hurtSpriteI=rotozoomSurfaceXY(sprite,0,-2,2,0);
    SDL_FreeSurface(sprite);

    pvBarre.setLLL();
    pvBarre.setPosition(10,10);
    pvBarre.setColor(50,255,50);

    xpBarre.setLLL();
    xpBarre.setPosition(10,30);
    xpBarre.setColor(200,50,50);
}

void  Player::init(int x,int y)
{
    m_posX=x;
    m_posY=y;

    m_velX=0;
    m_velY=0;

    falling = true;
    orientation=RIGHT;

    for (int i=0;i<3;i++){
        m_key[i]=false;
    }

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            rooms[i][j]=false;
        }
    }

    m_xp=0;
    m_lvl=1;
    m_xpLvlSuivant=XP_LVL=33;

    m_pv=m_pvMax=10;
    m_power=1;

    status=STAND;
    spriteNumber=0;

    //**************** sfx ****************
    Mix_FreeChunk(fireSound);
    fireSound=NULL;
    //**************** sfx ****************

    //**************** sfx ****************
    fireSound=Mix_LoadWAV("data/son/LASER.WAV");
    if(!fireSound) {
        std::cerr<<"Mix_LoadWAV: "<< Mix_GetError()<<std::endl;
    }
    //**************** sfx *****************
}

SDL_Rect Player::hitBox()
{
    SDL_Rect hitBox;
    hitBox.w=width();
    hitBox.h=height();
    hitBox.x=posX()-width()/2;
    hitBox.y=posY()-height()/2;

    if(status == DUCK ){
        int diff = 25;
        hitBox.y+=diff;
        hitBox.h-=diff;
    }

    return hitBox;
}

Player::~Player()
{
    SDL_FreeSurface(duckSprite);
    SDL_FreeSurface(duckSpriteI);
    SDL_FreeSurface(jumpSprite);
    SDL_FreeSurface(jumpSpriteI);
    SDL_FreeSurface(fireSprite);
    SDL_FreeSurface(fireSpriteI);
    SDL_FreeSurface(runSpriteI);
    SDL_FreeSurface(runFireSprite);
    SDL_FreeSurface(runFireSpriteI);
    SDL_FreeSurface(idleSprite);
    SDL_FreeSurface(idleSpriteI);
    SDL_FreeSurface(hurtSprite);
    SDL_FreeSurface(hurtSpriteI);

    //**************** sfx ****************
    Mix_FreeChunk(fireSound);
    fireSound=NULL;
    //**************** sfx ****************
}

void Player::fire(CustomCollection<Bullet>* bullets)
{
    int bulletHeght=20;
    if(status==DUCK)bulletHeght=-5;

    if(orientation==RIGHT){
        bullets->add(new Bullet(this->posX()+10,this->posY()-bulletHeght,0,Bullet::AMI));
    }else{
        bullets->add(new Bullet(this->posX()-10,this->posY()-bulletHeght,M_PI,Bullet::AMI));
    }

    firing=true;
    if(status==STAND)spriteNumber=0;

    Mix_PlayChannel(-1, fireSound, 0);
}


void Player::draw(int camX,int camY)
{
    SDL_Rect pos;
    SDL_Rect src;
    int spriteNumMax=0;


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
    SDL_Surface* sprite=NULL;
    switch(status){
        case DUCK:
            switch(orientation){
                case RIGHT:
                    sprite=duckSprite;
                    break;
                case LEFT:
                    sprite=duckSpriteI;
                    break;
            }
            spriteNumMax=0;
            break;

        case STAND:
            switch(orientation){
                case RIGHT:
                    if(firing){
                        sprite=fireSprite;
                        spriteNumMax=2;
                    }else{
                        sprite=idleSprite;
                        spriteNumMax=3;
                    }
                    break;
                case LEFT:
                    if(firing){
                        sprite=fireSpriteI;
                        spriteNumMax=2;
                    }else{
                        sprite=idleSpriteI;
                        spriteNumMax=3;
                    }
                    break;
            }

            //if fire
            break;

        case JUMP:
            switch(orientation){
                case RIGHT:
                    sprite=jumpSprite;
                    break;
                case LEFT:
                    sprite=jumpSpriteI;
                    break;
            }
            spriteNumMax=5;
            break;

        case RUN:
            switch(orientation){
                case RIGHT:
                    if(firing){
                        sprite=runFireSprite;
                    }else{
                        sprite=runSprite;
                    }

                    break;
                case LEFT:
                    if(firing){
                        sprite=runFireSpriteI;
                    }else{
                        sprite=runSpriteI;
                    }
                    break;
            }
            spriteNumMax=9;
            //if fire
            break;
        case HURT:
                switch(orientation){
                case RIGHT:
                    sprite=hurtSprite;
                    break;
                case LEFT:
                    sprite=hurtSpriteI;
                    break;
                }
            spriteNumMax=0;
            break;
    }


    pos.x=m_posX-camX-spriteWidth/2;
    pos.y=m_posY-camY-spriteHeight/2-15;
    switch(orientation){
        case RIGHT:
            src.x=spriteWidth*spriteNumber;
            break;
        case LEFT:
            src.x=sprite->w-(spriteWidth*(1+spriteNumber));
            break;
    }

    //ralentissemnt anime stand
    static int standCount=1;
    if(status==STAND){
        if(--standCount<0){
            spriteNumber++;
            standCount=1;
        }
    }else{
        spriteNumber++;
    }

    if(spriteNumber>spriteNumMax){
            spriteNumber=status==JUMP?2:0;
            //if(status==HURT)status=STAND;
    }
    src.y=0;
    src.w=spriteWidth;
    src.h=spriteHeight;
    SDL_BlitSurface(sprite,&src,SDL_GetWindowSurface(ecran),&pos);

    static int fireCount=6;
    if(--fireCount<0)firing=false,fireCount=6;



    pvBarre.afficheGD(ecran);
    xpBarre.afficheBH(ecran);

    #ifdef DEBUG
    //affichage des infos
    pos.x=game->screenW()/2;
    pos.y= 20;
    afficheIntSurInt(pos,posX(),posY(),ecran,numberFont,JAUNE);
    pos.x-=50;
    afficheIntSurInt(pos,currentRoom,currentPart,ecran,numberFont,JAUNE);
    #endif
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

void Player::gainXp(int val,Scene* parent)
{
    m_xp+=val;
    while(m_xp>=m_xpLvlSuivant){

        m_xp-=m_xpLvlSuivant;
        m_xpLvlSuivant=m_lvl*XP_LVL;

        ScreenMessage::loach("Level UP",parent,10);
        levelUp(++m_lvl);

    }
}

void Player::levelUp(int lvl)
{
    m_power=lvl/2+1;
    m_pv=m_pvMax=lvl*2+10;
}

void Player::damage(int val)
{
    m_pv-=val;
    if(orientation==LEFT){
        m_velX=10;
    }else{
        m_velX=-10;
    }

    status=HURT;
    hurtCooldown=3;
}

void Player::setCurrentRoom(int room,int part)
{
    rooms[room-1][part]=true;
    currentRoom = room-1;
    currentPart = part;
}
