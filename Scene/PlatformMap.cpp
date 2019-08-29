#include "PlatformMap.h"

#include <iostream>

#include "../core/Game.h"
extern Game* game;
#include "../Player.h"
extern Player player;
#include "MenuScene.h"

#include "../util/collision.h"
#include "../util/benrandom.h"

PlatformMap::PlatformMap(const char* file,const char* TileSet) : MapProto(file,TileSet)
{
    //ctor
    std::cerr<<"test"<<std::endl;
}

PlatformMap::~PlatformMap()
{
    //dtor
}


void PlatformMap::load()
{
    initPlayer();//  dans level
    initEni();//  dans level

    countDownBowl=50;

    std::cerr<<"load"<<std::endl;
}

void PlatformMap::unload()
{
    /*
    // dechargement des boules
    if(!bowls.empty())
    {
        for(bowlIt=bowls.begin();bowlIt!=bowls.end();bowlIt++){
            delete *bowlIt;
        }
    }
    bowls.clear();
*/
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
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        menu=true;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.goEast();
                        break;
                    case SDLK_LEFT:
                    case SDLK_q:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.goWest();
                        break;
                    case SDLK_UP:
                    case SDLK_z:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.goNorth();
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        player.goSouth();
                        break;
                    case SDLK_RETURN:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche

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
                        //player.fire();
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

    if(collisionTile(player.hitBox(),3)){
        goNextLevel();
    }
}

void PlatformMap::draw()
{
    setCamera(player.posX()-game->screenW()/2,player.posY()-game->screenH()/2);

    drawMap();

    player.draw();
}

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

void PlatformMap::playerMoov(int velX,int velY,SDL_Rect hitBox)
{


    // division du mouvement trop rapide
    if(velX >= this->tileWidth() || velY >= this->tileHeight() )
    {
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
                    if(boxCollision(hitBoxTest,hitBoxTile))
                    {
                        if(hitBox.y+hitBox.h<=hitBoxTile.y){
                            player.setPosition(player.posX(),hitBoxTile.y-(hitBox.h/2+hitBox.h%2));
                            velY=0;
                            player.stopFalling();
                            std::cerr<<"test"<<std::endl;
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
        hitBoxTest.y=player.hitBox().y-1;
        if(collisionWall(hitBoxTest)){
            player.stopVelY();
        }
    }
}

void PlatformMap::restart()
{
    this->unload();
    this->load();
}

