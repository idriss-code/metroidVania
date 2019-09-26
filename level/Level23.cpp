#include "Level23.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"


extern Game* game;

extern Player player;

Level23::Level23(): PlatformMap("data/map/wKey.mp","data/map/warped.png")
{
    //ctor
}

Level23::~Level23()
{
    //dtor
}

void Level23::initEni()
{
    if(!player.key(3))items.add(new Key(386,518,3));

    Door* doorR = new Door(9);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(9);
    doorL->remplace(0,this);
    addElement(doorL,10);

    Door* doorDR = new Door(9);
    doorDR->remplace(0,this);
    addElement(doorDR,12);

    Door* doorDL = new Door(1);
    doorDL->remplace(0,this);
    addElement(doorDL,13);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(22),52,256),6);
}
