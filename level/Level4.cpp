#include "Level4.h"
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

Level4::Level4(): PlatformMap("data/map/wcouloir.mp","data/map/warped.png")
{
    //ctor
}

Level4::~Level4()
{
    //dtor
}

void Level4::initEni()
{

    enis.add(new Alien(800,280));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);


    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(5),718,672),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(3),43,672),4);
}
