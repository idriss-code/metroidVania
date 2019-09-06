#include "PlatformMap.h"

#include <iostream>

#include "../core/Game.h"
extern Game* game;
#include "../Player.h"
extern Player player;
#include "MenuScene.h"

#include "../util/collision.h"
#include "../util/benrandom.h"

#include "../Eni.h"
#include "../Bullet.h"
#include "../Item/Item.h"
#include "../MapElement/MapElement.h"

PlatformMap::PlatformMap(const char* file,const char* TileSet) : MapProto(file,TileSet)
{
    //ctor
}

PlatformMap::~PlatformMap()
{
    //dtor
}

void PlatformMap::load()
{
    initPlayer();//  dans level
    initEni();//  dans level
    Bullet::load();

    countDownBowl=50;

    //itemInit
        //if key == true add item

    std::cerr<<"load"<<std::endl;
}

void PlatformMap::unload()
{
    Bullet::unload();
    bullets.clear();
    enis.clear();
    std::cerr<<"unload"<<std::endl;
}

void PlatformMap::input()
{
    switch(event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)//  Gestion des touches du clavier
                {
                    case SDLK_ESCAPE:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        menu=true;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.goEast();
                        break;
                    case SDLK_LEFT:
                    case SDLK_q:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.goWest();
                        break;
                    case SDLK_UP:
                    case SDLK_z:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        if(event.key.repeat == 0)player.goNorth();
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.goSouth();
                        break;
                    case SDLK_RETURN:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche

                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)//  Gestion des touches du clavier
                {
                    case SDLK_RIGHT:
                    case SDLK_d:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.stopEast();
                        break;
                    case SDLK_LEFT:
                    case SDLK_q:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.stopWest();
                        break;
                    case SDLK_UP:
                    case SDLK_z:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.stopNorth();
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.stopSouth();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN  :
                switch(event.button.button)//  Gestion des bouton souris
                {
                    case SDL_BUTTON_LEFT:
                        event.button.button=0;
                        player.fire(&bullets);
                        break;
                    default:
                        break;
                }
                break;
                case SDL_MOUSEMOTION:
                    //player.setMouse(event.motion.x,event.motion.y);
                break;
        }
}

void PlatformMap::update(int dt)
{
    if(menu){
        MenuScene::loach(this);
        menu=false;
    }

    player.fall();//chutte
    playerMoov(player.velX(),player.velY(),player.hitBox());
    playerFallControle();
    TestActionTile();// test action genre porte etc..

    CustomIterator<Eni> eniIt = enis.newIterator();
    while(eniIt.hasNext()){
        Eni* eni = eniIt.next();
        eni->update(this);
        if(boxCollision(player.hitBox(),eni->hitBox())){
            player.damage(2);
        }
    }

    CustomIterator<Item> itemIt = items.newIterator();
    while(itemIt.hasNext()){
        Item* item = itemIt.next();

        if(boxCollision(player.hitBox(),item->hitBox())){
            item->action(&player);
            itemIt.remove();
        }
    }

    CustomIterator<Bullet> bulletIt = bullets.newIterator();
    while(bulletIt.hasNext()){
        Bullet* bullet = bulletIt.next();
        bullet->update();

        eniIt = enis.newIterator();
        while(eniIt.hasNext()){
            Eni* eni = eniIt.next();
            if(pointCollision(bullet->GetposX(),bullet->GetposY(),eni->hitBox())){
                player.gainXp(eni->xp(),this);
                eniIt.remove();
                bulletIt.remove();
            }
        }
    }

    //Gestion collision avec item
        //if collision action item et remove item

    if(player.pv()<=0){
        cout<<"game over"<<endl;
    }
/*
    if(collisionTile(player.hitBox(),3)){
        goNextLevel();
    }
    */
}

void PlatformMap::draw()
{
    setCamera(player.posX()-game->screenW()/2,player.posY()-game->screenH()/2);

    drawMap();

    CustomIterator<Item> itemIt = items.newIterator();
    while(itemIt.hasNext()){
        Item* item = itemIt.next();
        item->draw(this->cameraX(),this->cameraY());
    }

    CustomIterator<Eni> it = enis.newIterator();
    while(it.hasNext()){
        Eni* eni = it.next();
        eni->draw(this->cameraX(),this->cameraY());
    }

    CustomIterator<Bullet> bulletIt = bullets.newIterator();
    while(bulletIt.hasNext()){
        Bullet* bullet = bulletIt.next();

        bullet->draw(this->cameraX(),this->cameraY());
    }

    player.draw();
}

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

void PlatformMap::playerMoov(int velX,int velY,SDL_Rect hitBox)
{
    // division du mouvement trop rapide
    if(velX >= this->tileWidth() || velY >= this->tileHeight() ){
        playerMoov(velX/2,velY/2,hitBox);
        playerMoov(velX-velX/2,velY-velY/2,hitBox);
        return;
    }

    // gestion des platform
    if(velY>0){
        SDL_Rect hitBoxTest=hitBox;
        SDL_Rect hitBoxTile;
        hitBoxTest.x+=velX;
        hitBoxTest.y+=velY;
        hitBoxTile.w=tileWidth();
        hitBoxTile.h=tileHeight();

        int test=true;
        for(int i=0;i<width() && test;i++){
            for(int j=0;j<height() && test;j++){
                if(obj(i,j) == 2){
                    hitBoxTile.x=i*tileWidth();
                    hitBoxTile.y=j*tileHeight();
                    if(boxCollision(hitBoxTest,hitBoxTile)){
                        if(hitBox.y+hitBox.h<=hitBoxTile.y){
                            player.setPosition(player.posX(),hitBoxTile.y-(hitBox.h/2+hitBox.h%2));
                            velY=0;
                            player.stopFalling();
                            std::cerr<<"stop fall"<<std::endl;
                        }
                    }
                }
            }
        }
    }


    //mouvement sans mur
    if(testMoov(velX,velY,hitBox)){
        player.moov(velX,velY);
        return;
    }

    //affinage avec mur
    for(int i=0;i<ABS(velX);i++)
    {
        if (testMoov(SGN(velX),0,hitBox)) {
            player.moov(SGN(velX),0);
            hitBox.x+=SGN(velX);
        }else{
            break;
        }
    }
    for(int i=0;i<ABS(velY);i++)
    {
        if (testMoov(0,SGN(velY),hitBox)){
            player.moov(0,SGN(velY));
            hitBox.y+=SGN(velY);
        }else{
            break;
        }
    }
}

void PlatformMap::playerFallControle()
{
    SDL_Rect hitBoxTest=player.hitBox();
    hitBoxTest.y+=hitBoxTest.h+1;
    hitBoxTest.h=1;
    if(collisionWall(hitBoxTest)){
        player.stopFalling();
        return;
    }else if(collisionTile(hitBoxTest,2)){
        return;
    }else{
        player.startFalling();
        // touché de téte au plafond
        hitBoxTest.y=player.hitBox().y-1;
        if(collisionWall(hitBoxTest)){
            player.stopVelY();
        }

    }
}

void PlatformMap::TestActionTile()
{
    for(int i=0;i<100;i++)//100 objet max dans une carte
    {
        if(this->element(i)->doActionOnEnter() && collisionTile(player.hitBox(),i))
           {
               this->element(i)->action();
           }
    }
}



void PlatformMap::restart()
{
    this->unload();
    this->load();
}

