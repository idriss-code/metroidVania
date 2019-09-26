#include "Level8.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../Eni/Crab.h"
#include "../Eni/Robot.h"
#include "../Eni/Biped.h"
#include "../Eni/Alien.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level8::Level8(): PlatformMap("data/map/wcouloir.mp","data/map/warped.png")
{
    //ctor
}

Level8::~Level8()
{
    //dtor
}

void Level8::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(7),1100,640),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(9),43,256),4);
}
