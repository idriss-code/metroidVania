#include "Level12.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../Eni/Crab.h"
#include "../Eni/Robot.h"
#include "../Eni/Biped.h"
#include "../Eni/Jumper.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level12::Level12(): PlatformMap("data/map/wcouloir.mp","data/map/warped.png")
{
    //ctor
}

Level12::~Level12()
{
    //dtor
}

void Level12::initEni()
{
    enis.add(new Jumper(400,280));
    enis.add(new Jumper(600,280));
    enis.add(new Jumper(800,280));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);


    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(13),718,672),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(11),43,672),4);
}
