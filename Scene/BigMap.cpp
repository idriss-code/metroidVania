#include "BigMap.h"
#include "../core/Game.h"
#include "MenuScene.h"
#include "ScreenMessage.h"

#include <iostream>
#include "../Player.h"
extern Player player;
extern Game* game;
extern TTF_Font* numberFont;
extern SDL_Color ROSE;

#include "../Room.h"
#include "../Item/Key.h"

BigMap::BigMap()
{
    //ctor
    for(int i=0;i<LVL;i++){
        for(int j=0;j<PART;j++){
            rooms[i][j]= NULL;
        }
    }
}

BigMap::~BigMap()
{
    //dtor
}

void BigMap::loadCorridor(int x,int y,int id){
    rooms[id-1][0] = new Room(x+0,y+0,WALL,WALL,DOOR,NO);
    rooms[id-1][1] = new Room(x+1,y+0,WALL,WALL,NO,NO);
    rooms[id-1][2] = new Room(x+2,y+0,WALL,WALL,NO,DOOR);
}

void BigMap::loadStairs(int x,int y,int id){
    rooms[id-1][0] = new Room(x+0,y+0,WALL,NO,DOOR,WALL);
    rooms[id-1][1] = new Room(x+0,y+1,NO,NO,WALL,WALL);
    rooms[id-1][2] = new Room(x+0,y+2,NO,WALL,DOOR,WALL);
}

void BigMap::loadKey(int x,int y,int id){
    rooms[id-1][0] = new Room(x+0,y+0,WALL,NO,WALL,NO);
    rooms[id-1][1] = new Room(x+1,y+0,WALL,NO,NO,WALL);
    rooms[id-1][2] = new Room(x+0,y+1,NO,WALL,WALL,NO);
    rooms[id-1][3] = new Room(x+1,y+1,NO,WALL,NO,DOOR);
}
void BigMap::loadBoss(int x,int y,int id){
    rooms[id-1][0] = new Room(x+0,y+0,WALL,NO,WALL,NO);
    rooms[id-1][1] = new Room(x+1,y+0,WALL,NO,NO,NO);
    rooms[id-1][2] = new Room(x+2,y+0,WALL,NO,NO,WALL);

    rooms[id-1][3] = new Room(x+0,y+1,NO,WALL,DOOR,NO);
    rooms[id-1][4] = new Room(x+1,y+1,NO,WALL,NO,NO);
    rooms[id-1][5] = new Room(x+2,y+1,NO,WALL,NO,DOOR);
}
void BigMap::load()
{
    #ifdef DEBUG
        fullMap =true ;
    #else
        fullMap =false ;
    #endif


    loadCorridor(2,6,4);
    loadCorridor(7,6,6);
    loadCorridor(13,6,8);
    loadCorridor(13,8,10);
    loadCorridor(8,9,12);
    loadCorridor(13,9,14);
    loadCorridor(13,11,16);
    loadCorridor(8,3,19);
    loadCorridor(14,3,21);
    loadCorridor(8,8,24);

    loadBoss(10,5,7);
    loadBoss(10,10,17);
    loadBoss(11,2,20);

    loadStairs(16,6,9);
    loadStairs(16,9,15);
    loadStairs(17,1,22);

    loadKey(0,5,5);
    loadKey(15,0,23);
    loadKey(6,8,13);

//salle3
    int x=5;
    int y=5;
    int id=3;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,NO,DOOR,NO);
    rooms[id-1][1] = new Room(x+1,y+0,WALL,NO,NO,DOOR);
    rooms[id-1][2] = new Room(x+0,y+1,NO,WALL,DOOR,NO);
    rooms[id-1][3] = new Room(x+1,y+1,NO,WALL,NO,DOOR);

//salle11
    x=11;
    y=8;
    id=11;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,NO,DOOR,NO);
    rooms[id-1][1] = new Room(x+1,y+0,WALL,NO,NO,DOOR);
    rooms[id-1][2] = new Room(x+0,y+1,NO,WALL,DOOR,NO);
    rooms[id-1][3] = new Room(x+1,y+1,NO,WALL,NO,DOOR);

    //escalier 2
    x=4;
    y=3;
    id=2;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,NO,DOOR,WALL);
    rooms[id-1][1] = new Room(x+0,y+1,NO,NO,WALL,WALL);
    rooms[id-1][2] = new Room(x+0,y+2,NO,WALL,WALL,DOOR);

    // escalier 18
    x=7;
    y=3;
    id=18;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,NO,WALL,DOOR);
    rooms[id-1][1] = new Room(x+0,y+1,NO,NO,WALL,WALL);
    rooms[id-1][2] = new Room(x+0,y+2,NO,WALL,DOOR,WALL);

    x=1;
    y=3;
    id=1;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,WALL,WALL,NO);
    rooms[id-1][1] = new Room(x+1,y+0,WALL,WALL,NO,NO);
    rooms[id-1][2] = new Room(x+2,y+0,WALL,WALL,NO,DOOR);

    x=8;
    y=8;
    id=24;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,WALL,WALL,NO);
    rooms[id-1][1] = new Room(x+1,y+0,WALL,WALL,NO,NO);
    rooms[id-1][2] = new Room(x+2,y+0,WALL,WALL,NO,DOOR);


    x=18;
    y=1;
    id=25;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,WALL,DOOR,WALL);


    x=17;
    y=6;
    id=26;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,WALL,DOOR,WALL);


    x=17;
    y=9;
    id=27;
    rooms[id-1][0] = new Room(x+0,y+0,WALL,WALL,DOOR,WALL);








    for(int i=1;i<4;i++){
        if(player.key(i)){
            items.add(new Key(700,30+i*30,i));
        }
    }
}

void BigMap::unload()
{
    for(int i=0;i<LVL;i++){
        for(int j=0;j<PART;j++){
            delete rooms[i][j];
            rooms[i][j]= NULL;
        }
    }

    items.clear();
}

void BigMap::input()
{
    switch(event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;

        }

}

void BigMap::update(int dt)
{
   MenuScene::loach(this);
   exit();
}

void BigMap::draw()
{
    for(int i=0;i<LVL;i++){
        for(int j=0;j<PART;j++){
            if( rooms[i][j]!= NULL && (player.visitedRoom(i,j) || fullMap) ){
                if(i==player.getRoom() && j==player.getPart()){
                    rooms[i][j]->activate();
                }
                rooms[i][j]->draw();
            }
        }
    }


//affichege life
    SDL_Rect pos;
    pos.x=100;
    pos.y=520;
    afficheTexte(pos,"Life",ecran,numberFont,ROSE);
    pos.x=200;
    afficheIntSurInt(pos,player.pv(),player.pvMax(),ecran,numberFont,ROSE);
//affichege Xp
    pos.x=100;
    pos.y=540;
    afficheTexte(pos,"Xp",ecran,numberFont,ROSE);
    pos.x=200;
    afficheIntSurInt(pos,player.xp(),player.xpMax(),ecran,numberFont,ROSE);

//affichege Xp
    pos.x=100;
    pos.y=560;
    afficheTexte(pos,"Lvl",ecran,numberFont,ROSE);
    pos.x=200;
    afficheInt(pos,player.lvl(),ecran,numberFont,ROSE);

     CustomIterator<Item> itemIt = items.newIterator();
    while(itemIt.hasNext()){
        Item* item = itemIt.next();
        item->draw(0,0);
    }

}
