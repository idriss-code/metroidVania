#include "Level18.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level18::Level18(): PlatformMap("data/map/wescalier18.mp","data/map/warped.png")
{
    //ctor
}

Level18::~Level18()
{
    //dtor
}

void Level18::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,12);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(3),718,256),5);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(19),52,256),4);
}
