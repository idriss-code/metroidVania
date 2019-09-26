#include "Level15.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level15::Level15(): PlatformMap("data/map/wescalier9.mp","data/map/warped.png")
{
    //ctor
}

Level15::~Level15()
{
    //dtor
}

void Level15::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,12);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(14),1100,256),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(16),1100,256),5);
}
