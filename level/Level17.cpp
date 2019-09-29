#include "Level17.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../Eni/Crab.h"
#include "../Eni/Robot.h"
#include "../Eni/Biped.h"
#include "../Eni/Alien.h"
#include "../Eni/Boss3.h"
#include "../Eni/Jumper.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level17::Level17(): PlatformMap("data/map/wBoss.mp","data/map/warped.png")
{
    //ctor
}

Level17::~Level17()
{
    //dtor
}

void Level17::initEni()
{

    enis.add(new Boss3(800,280));
    enis.add(new Jumper(700,280));
    enis.add(new Jumper(500,280));
    enis.add(new Jumper(300,280));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(9);
    doorL->remplace(0,this);
    addElement(doorL,10);

    //addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(6),1100,256),3);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(16),52,256),4);
}
