#include "Level20.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../Eni/Boss2.h"
#include "../Eni/Robot.h"
#include "../Eni/Biped.h"
#include "../Eni/Alien.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level20::Level20(): PlatformMap("data/map/wBoss.mp","data/map/warped.png")
{
    //ctor
}

Level20::~Level20()
{
    //dtor
}

void Level20::initEni()
{

    enis.add(new Boss2(800,280));

    Door* doorR = new Door(5);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(19),1100,256),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(21),52,256),4);
}
