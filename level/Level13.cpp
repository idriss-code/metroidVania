#include "Level13.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"
#include "../Item/DoubleJump.h"

extern Game* game;

extern Player player;

Level13::Level13(): PlatformMap("data/map/wKey.mp","data/map/warped.png")
{
    //ctor
}

Level13::~Level13()
{
    //dtor
}

void Level13::initEni()
{
    if(!player.doubleJump())items.add(new DoubleJump(386,518));

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

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(12),52,256),6);
}
