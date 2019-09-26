#include "Level2.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level2::Level2(): PlatformMap("data/map/wescalier.mp","data/map/warped.png")
{
    //ctor
}

Level2::~Level2()
{
    //dtor
}

void Level2::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(1),1100,256),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(3),52,288),4);
}
