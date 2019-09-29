#include "PlatformMap.h"
#include <iostream>
#include "../MyGame.h"
extern Game* game;
#include "../Player.h"
extern Player player;
#include "MenuScene.h"
#include "../util/collision.h"
#include "../util/benrandom.h"
#include "../gfx/SDL2_rotozoom.h"
#include "../Eni.h"
#include "../Bullet.h"
#include "../Item/Item.h"
#include "../MapElement/MapElement.h"
#include "BigMap.h"
#include "ScreenMessage.h"
#include "../MusicManager.h"
#include "../Explosion.h"

PlatformMap::PlatformMap(const char* file,const char* TileSet) : MapProto(file,TileSet)
{
        RECT_H = 12 * 16 * 2;//zoom;
        RECT_W = 12 * 16 * 2;//zoom;
}

PlatformMap::~PlatformMap()
{
    //dtor
}

void PlatformMap::load()
{
    initEni();//  dans level
    Bullet::load();

    countDownBowl=50;

    menu=false;

    //load background
    SDL_Surface* sprite;
    sprite=IMG_Load("./data/map/background.png");
    bkgrnd=rotozoomSurfaceXY(sprite,0,4,4,0);
    SDL_FreeSurface(sprite);
    //end load background

//gestion music
    int musicZone;
    if (level()>=1 && level()<=6){
        musicZone=1;
    }else if(level()>=7 && level()<=13){
        musicZone=2;
    }else if(level()>=14 && level()<=17){
        musicZone=3;
    }else{
        musicZone=4;
    }
    MusicManager* musicManager;
    musicManager=dynamic_cast<MyGame *>(game)->musicManager();
    musicManager->goZone(musicZone);

    //fin music

#ifdef DEBUG
    std::cout<<"load debug"<<std::endl;
#endif

}

void PlatformMap::unload()
{
    SDL_FreeSurface(bkgrnd);
    Bullet::unload();
    bullets.clear();
    enis.clear();
    items.clear();
    std::cout<<"unload"<<std::endl;
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
                        if(event.key.repeat == 0)player.goEast();
                        break;
                    case SDLK_LEFT:
                    case SDLK_q:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        if(event.key.repeat == 0)player.goWest();
                        break;
                    case SDLK_UP:
                    case SDLK_z:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        if(event.key.repeat == 0)player.goNorth();
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        if(event.key.repeat == 0)player.goSouth();
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
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                         if(!player.isHurt())player.stopEast();
                        break;
                    case SDLK_LEFT:
                    case SDLK_q:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        if(!player.isHurt())player.stopWest();
                        break;
                    case SDLK_UP:
                    case SDLK_z:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        if(!player.isHurt())player.stopNorth();
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        //event.key.keysym.sym=0;//evite les pb de repetition de touche
                        if(!player.isHurt())player.stopSouth();
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
        //MenuScene::loach(this);
        BigMap bigMap;
        bigMap.exec();

        menu=false;
    }

    player.hurtControl();
    player.fall();//chutte
    playerMoov(player.velX(),player.velY(),player.hitBox());
    playerFallControle();
    TestActionTile();// test action genre porte etc..


    CustomIterator<Explosion> explIt = explosions.newIterator();
    while(explIt.hasNext()){
        Explosion* explosion = explIt.next();
        explosion->update();
        if(explosion->toDelete()){
            explIt.remove();
        }
    }

    CustomIterator<Eni> eniIt = enis.newIterator();
    while(eniIt.hasNext()){
        Eni* eni = eniIt.next();
        eni->update(this);
        eni->fireUpdate(&bullets);
        if(boxCollision(player.hitBox(),eni->hitBox())){
            player.damage(2);
        }
    }

    CustomIterator<Item> itemIt = items.newIterator();
    while(itemIt.hasNext()){
        Item* item = itemIt.next();

        if(boxCollision(player.hitBox(),item->hitBox())){
            item->action(this);
            itemIt.remove();
        }
    }

    CustomIterator<Bullet> bulletIt = bullets.newIterator();
    while(bulletIt.hasNext()){
        Bullet* bullet = bulletIt.next();
        bullet->update();
        SDL_Rect pos;
        pos.x=bullet->GetposX();
        pos.y=bullet->GetposY();
        pos.h=1;
        pos.w=1;

        if(collisionWall(pos) ||
           collisionTile(pos,3) ||
            collisionTile(pos,4) ||
            collisionTile(pos,5) ||
            collisionTile(pos,6) ||
            collisionTile(pos,10) ||
            collisionTile(pos,11) ||
            collisionTile(pos,12) ||
            collisionTile(pos,13)
           ){
            bulletIt.remove();
            continue;
        }

        if(bullet->GetTag()==Bullet::ENI){
            if(pointCollision(bullet->GetposX(),bullet->GetposY(),player.hitBox())){
                bulletIt.remove();
                if(!player.isHurt())player.damage(1);
                continue;
            }
        }

        if(bullet->GetTag()==Bullet::AMI){
            eniIt = enis.newIterator();
            while(eniIt.hasNext()){
                Eni* eni = eniIt.next();
                if(pointCollision(bullet->GetposX(),bullet->GetposY(),eni->hitBox())){
                    bulletIt.remove();
                    eni->damage(player.power());
                    if(eni->pv()<=0){
                        player.gainXp(eni->xp(),this);
                        eni->onDying(&items);
                        explosions.add(new Explosion(eni->posX(),eni->posY()));
                        eniIt.remove();
                    }
                    break;
                }
            }
        }


    }

    //Gestion collision avec item
        //if collision action item et remove item

    if(player.pv()<=0){
        dynamic_cast<MyGame *>(game)->reBoot();
        ScreenMessage::loach("Game Over",this,50);
        cout<<"game over"<<endl;
    }

//calcul place sur le big map
    player.setCurrentRoom(level(),player.posX()/RECT_W+player.posY()/RECT_H*((tileWidth()*width())/RECT_W));
    //place = player.posX()/RECT_W+player.posY()/RECT_H*((tileWidth()*width())/RECT_W);
/*
    if(collisionTile(player.hitBox(),3)){
        goNextLevel();
    }
    */
}

void PlatformMap::draw()
{
    //Gestion de la camera
    int camX;
    int camY;
    int levelWidth=tileWidth()*width();
    int levelHeight=tileHeight()*height();

    if(levelWidth<game->screenW()){//centrage si niveau plus petit que ecran
            camX=(levelWidth-game->screenW())/2;
    }else if(player.posX()+game->screenW()/2>levelWidth){//allignement a droite
        camX=levelWidth-game->screenW();
    }else{
        // suivei du player
        camX=player.posX()-game->screenW()/2;
        //allignement a gauche
        camX=camX<0?0:camX;
    }
    //idem pour l'axe Y
    if(levelHeight<game->screenH()){//centrage si niveau plus petit que ecran
            camY=(levelHeight-game->screenH())/2;
    }else if(player.posY()+game->screenH()/2>levelHeight){//allignement a droite
        camY=levelHeight-game->screenH();
    }else{
        // suivei du player
        camY=player.posY()-game->screenH()/2;
        //allignement a gauche
        camY=camY<0?0:camY;
    }

    setCamera(camX,camY);


    drawBackground();
    drawMap();

    CustomIterator<Explosion> explIt = explosions.newIterator();
    while(explIt.hasNext()){
        Explosion* explosion = explIt.next();
        explosion->draw(this->cameraX(),this->cameraY());
    }

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

    player.draw(this->cameraX(),this->cameraY());
}

void PlatformMap::drawBackground()
{
    //SDL_SetColorKey(tileSet,SDL_TRUE ,SDL_MapRGBA(tileSet->format,0,0,0,0));
    int levelWidth=tileWidth()*width();
    int levelHeight=tileHeight()*height();


    SDL_Rect pos;
    SDL_Rect src;
    pos.x=0;
    pos.y=0;
    src.x=0;
    src.y=0;
    src.w=levelWidth;
    src.h=levelHeight;


    if(levelWidth<game->screenW()){//centrage si niveau plus petit que ecran
            src.x=pos.x=(game->screenW()-levelWidth)/2;
    }

     if(levelHeight<game->screenH()){//centrage si niveau plus petit que ecran
            src.y=pos.y=(game->screenH()-levelHeight)/2;
    }
    src.y+=20;

    SDL_BlitSurface(bkgrnd,&src,SDL_GetWindowSurface(ecran),&pos);


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
        SDL_Rect hitBoxTest=player.hitBox();
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
                        if(player.hitBox().y+player.hitBox().h<=hitBoxTile.y){
                            player.setPosition(player.posX(),hitBoxTile.y-(player.hitBox().h/2+player.hitBox().h%2));
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
    if(testMoov(velX,velY,player.hitBox())){
        player.moov(velX,velY);
        return;
    }

    //affinage avec mur
    for(int i=0;i<ABS(velX);i++)
    {
        if (testMoov(SGN(velX),0,player.hitBox())) {
            player.moov(SGN(velX),0);
            hitBox.x+=SGN(velX);
        }else{
            break;
        }
    }
    for(int i=0;i<ABS(velY);i++)
    {
        if (testMoov(0,SGN(velY),player.hitBox())){
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
    hitBoxTest.y+=hitBoxTest.h;
    hitBoxTest.h=1;
    if(collisionWall(hitBoxTest)){
        if (player.velY()>0)player.stopFalling(),player.resetJump();
        return;
    }else if(collisionTile(hitBoxTest,2)){
        player.resetJump();
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
