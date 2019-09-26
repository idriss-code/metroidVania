#include "Level6.h"
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

Level6::Level6(): PlatformMap("data/map/wcouloir.mp","data/map/warped.png")
{
    //ctor
}

Level6::~Level6()
{
    //dtor
}

void Level6::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(3),718,672),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(7),43,640),4);
}
