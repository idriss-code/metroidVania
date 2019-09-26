#include "Level10.h"
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

Level10::Level10(): PlatformMap("data/map/wcouloir.mp","data/map/warped.png")
{
    //ctor
}

Level10::~Level10()
{
    //dtor
}

void Level10::initEni()
{

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(11),718,256),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(9),43,1024),4);
}
