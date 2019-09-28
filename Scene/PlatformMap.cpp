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

    //itemInit
        //if key == true add item


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

        if(bullet->GetTag()==Bullet::ENI){
            if(pointCollision(bullet->GetposX(),bullet->GetposY(),player.hitBox())){
                bulletIt.remove();
                if(!player.isHurt())player.damage(1);
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
                        eniIt.remove();
                    }
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
            src.y=pos.y=P
9`UvX$"çï‚QuŒ1êÔzÄÔ[ÚLÊ¡²xN‡¹½.,6³ßİMıK)6ÚrNUW*êœYˆ‰qÆĞ÷ïOI¨éwŞêÀ´Å1ßÜu6˜şS{ÇiÖ­Ye<²fü\[Ñë8lé+{vyâ5/”|Š¬p’DîYQ_Æñ1áXÓ¬VÁ2üIş«kşéçĞyôgÊéÙŒ$œŸ¦3§xqh‚9³d*ª‘ÓÚ´Ús%.22H/µº„»¸éºÆ7¥Ç*1ËtÓ ü•67ÇæBm†$NÅ¤“¾ÛÊl$3¦
!á•™rßèB3îx—QÑ9JƒX/Ùğ,uT¹–¢S9Ktø=®™‹ŸÑ·µ¤­://‹>p^7»î«¦#Œ”çĞmŞõ‚N7vövÃ~ÌŒ€)ÑˆZ+-4e)|Y,`ñÃ
d®²ªú[#BİiÉï£—{›ÌJ£8B.õào_*/â“ã-Ø»úe§è§R;‚2?Ÿ=ifÖ®ÑàœÃ¯.·lrqºØ$Pì 3U#ÿœµìÆ§sı“•úDaæ°š@cYëÃ	H\õƒ%Lwn‘(c%ã*ÂW;ô/¡t…^<7¼eú&@ìCÔ3Ä2bQÚµ±@¯*MÃû¿Ì¹ˆ&#ÄÿzŒ¿Æ^TP
9`UvX$"çï‚QuŒ1êÔzÄÔ[ÚLÊ¡²xN‡¹½.,6³ßİMıK)6ÚrNUW*êœYˆ‰qÆĞ÷ïOI¨éwŞêÀ´Å1ßÜu6˜şS{ÇiÖ­Ye<²fü\[Ñë8lé+{vyâ5/”|Š¬p’DîYQ_Æñ1áXÓ¬VÁ2üIş«kşéçĞyôgÊéÙŒ$œŸ¦3§xqh‚9³d*ª‘ÓÚ´Ús%.22H/µº„»¸éºÆ7¥Ç*1ËtÓ ü•67ÇæBm†$NÅ¤“¾ÛÊl$3¦
!á•™rßèB3îx—QÑ9JƒX/Ùğ,uT¹–¢S9Ktø=®™‹ŸÑ·µ¤­://‹>p^7»î«¦#Œ”çĞmŞõ‚N7vövÃ~ÌŒ€)ÑˆZ+-4e)|Y,`ñÃ
d®²ªú[#BİiÉï£—{›ÌJ£8B.õào_*/â“ã-Ø»úe§è§R;‚2?Ÿ=ifÖ®ÑàœÃ¯.·lrqºØ$Pì 3U#ÿœµìÆ§sı“•úDaæ°š@cYëÃ	H\õƒ%Lwn‘(c%ã*ÂW;ô/¡t…^<7¼eú&@ìCÔ3Ä2bQÚµ±@¯*MÃû¿Ì¹ˆ&#ÄÿzŒ¿Æ^TP
9`UvX$"çï‚QuŒ1êÔzÄÔ[ÚLÊ¡²xN‡¹½.,6³ßİMıK)6ÚrNUW*êœYˆ‰qÆĞ÷ïOI¨éwŞêÀ´Å1ßÜu6˜şS{ÇiÖ­Ye<²fü\[Ñë8lé+{vyâ5/”|Š¬p’DîYQ_Æñ1áXÓ¬VÁ2üIş«kşéçĞyôgÊéÙŒ$œŸ¦3§xqh‚9³d*ª‘ÓÚ´Ús%.22H/µº„»¸éºÆ7¥Ç*1ËtÓ ü•67ÇæBm†$NÅ¤“¾ÛÊl$3¦
!á•™rßèB3îx—QÑ9JƒX/Ùğ,uT¹–¢S9Ktø=®™‹ŸÑ·µ¤­://‹>p^7»î«¦#Œ”çĞmŞõ‚N7vövÃ~ÌŒ€)ÑˆZ+-4e)|Y,`ñÃ
d®²ªú[#BİiÉï£—{›ÌJ£8B.õào_*/â“ã-Ø»úe§è§R;‚2?Ÿ=ifÖ®ÑàœÃ¯.·lrqºØ$Pì 3U#ÿœµìÆ§sı“•úDaæ°š@cYëÃ	H\õƒ%Lwn‘(c%ã*ÂW;ô/¡t…^<7¼eú&@ìCÔ3Ä2bQÚµ±@¯*MÃû¿Ì¹ˆ&#ÄÿzŒ¿Æ^TP
9`UvX$"çï‚QuŒ1êÔzÄÔ[ÚLÊ¡²xN‡¹½.,6³ßİMıK)6ÚrNUW*êœYˆ‰qÆĞ÷ïOI¨éwŞêÀ´Å1ßÜu6˜şS{ÇiÖ­Ye<²fü\[Ñë8lé+{vyâ5/”|Š¬p’DîYQ_Æñ1áXÓ¬VÁ2üIş«kşéçĞyôgÊéÙŒ$œŸ¦3§xqh‚9³d*ª‘ÓÚ´Ús%.22H/µº„»¸éºÆ7¥Ç*1ËtÓ ü•67ÇæBm†$NÅ¤“¾ÛÊl$3¦
!á•™rßèB3îx—QÑ9JƒX/Ùğ,uT¹–¢S9Ktø=®™‹ŸÑ·µ¤­://‹>p^7»î«¦#Œ”çĞmŞõ‚N7vövÃ~ÌŒ€)ÑˆZ+-4e)|Y,`ñÃ
d®²ªú[#BİiÉï£—{›ÌJ£8B.õào_*/â“ã-Ø»úe§è§R;‚2?Ÿ=ifÖ®ÑàœÃ¯.·lrqºØ$Pì 3U#ÿœµìÆ§sı“•úDaæ°š@cYëÃ	H\õƒ%Lwn‘(c%ã*ÂW;ô/¡t…^<7¼eú&@ìCÔ3Ä2bQÚµ±@¯*MÃû¿Ì¹ˆ&#ÄÿzŒ¿Æ^TP
9`UvX$"çï‚QuŒ1êÔzÄÔ[ÚLÊ¡²xN‡¹½.,6³ßİMıK)6ÚrNUW*êœYˆ‰qÆĞ÷ïOI¨éwŞêÀ´Å1ßÜu6˜şS{ÇiÖ­Ye<²fü\[Ñë8lé+{vyâ5/”|Š¬p’DîYQ_Æñ1áXÓ¬VÁ2üIş«kşéçĞyôgÊéÙŒ$œŸ¦3§xqh‚9³d*ª‘ÓÚ´Ús%.22H/µº„»¸éºÆ7¥Ç*1ËtÓ ü•67ÇæBm†$NÅ¤“¾ÛÊl$3¦
!á•™rßèB3îx—QÑ9JƒX/Ùğ,uT¹–¢S9Ktø=®™‹ŸÑ·µ¤­://‹>p^7»î«¦#Œ”çĞmŞõ‚N7vövÃ~ÌŒ€)ÑˆZ+-4e)|Y,`ñÃ
d®²ªú[#BİiÉï£—{›ÌJ£8B.õào_*/â“ã-Ø»úe§è§R;‚2?Ÿ=ifÖ®ÑàœÃ¯.·lrqºØ$Pì 3U#ÿœµìÆ§sı“•úDaæ°š@cYëÃ	H\õƒ%Lwn‘(c%ã*ÂW;ô/¡t…^<7¼eú&@ìCÔ3Ä2bQÚµ±@¯*MÃû¿Ì¹ˆ&#ÄÿzŒ¿Æ^TP
9`UvX$"çï‚QuŒ1êÔzÄÔ[ÚLÊ¡²xN‡¹½.,6³ßİMıK)6ÚrNUW*êœYˆ‰qÆĞ÷ïOI¨éwŞêÀ´Å1ßÜu6˜şS{ÇiÖ­Ye<²fü\[Ñë8lé+{vyâ5/”|Š¬p’DîYQ_Æñ1áXÓ¬VÁ2üIş«kşéçĞyôgÊéÙŒ$œŸ¦3§xqh‚9³d*ª‘ÓÚ´Ús%.22H/µº„»¸éºÆ7¥Ç*1ËtÓ ü•67ÇæBm†$NÅ¤“¾ÛÊl$3¦
!á•™rßèB3îx—QÑ9JƒX/Ùğ,uT¹–¢S9Ktø=®™‹ŸÑ·µ¤­://‹>p^7»î«¦#Œ”çĞmŞõ‚N7vövÃ~ÌŒ€)ÑˆZ+-4e)|Y,`ñÃ
d®²ªú[#BİiÉï£—{›ÌJ£8B.õào_*/â“ã-Ø»úe§è§R;‚2?Ÿ=ifÖ®ÑàœÃ¯.·lrqºØ$Pì 3U#ÿœµìÆ§sı“•úDaæ°š@cYë