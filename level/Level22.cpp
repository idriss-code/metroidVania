#include "Level22.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level22::Level22(): PlatformMap("data/map/wescalier9.mp","data/map/warped.png")
{
    //ctor
}

Level22::~Level22()
{
    //dtor
}

void Level22::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,12);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    Door* doorw = new Door(1);
    doorw->remplace(0,this);
    addElement(doorw,11);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(23),718,672),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(21),1100,256),5);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(25),52,256),4);
}
