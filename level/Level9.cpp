#include "Level9.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level9::Level9(): PlatformMap("data/map/wescalier9.mp","data/map/warped.png")
{
    //ctor
}

Level9::~Level9()
{
    //dtor
}

void Level9::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,12);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(8),1100,256),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(10),1100,256),5);


    Door* doorw = new Door(1);
    doorw->remplace(0,this);
    addElement(doorw,11);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(26),52,256),4);
}
