#include "Level1.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../Eni/Crab.h"
#include "../Eni/Robot.h"
#include "../Eni/Biped.h"
#include "../Eni/Alien.h"

#include "../Item/Key.h"
#include "../Item/Life.h"
#include "../Item/DoubleJump.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level1::Level1(): PlatformMap("data/map/wcouloir3.mp","data/map/warped.png")
{
    //ctor
}

Level1::~Level1()
{
    //dtor
}

void Level1::initEni()
{

    enis.add(new Crab(1000,300));
    enis.add(new Alien(900,300));
    enis.add(new Robot(700,280));
    enis.add(new Biped(800,280));

    if(!player.key(1))items.add(new Key(500,200,1));
    items.add(new Life(500,300));

    //items.add(new DoubleJump(400,200));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(2),43,256),4);
}
