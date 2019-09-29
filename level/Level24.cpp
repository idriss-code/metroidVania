#include "Level24.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../Eni/Crab.h"
#include "../Eni/Jumper.h"
#include "../Eni/Biped.h"
#include "../Eni/Alien.h"

#include "../Item/Life.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level24::Level24(): PlatformMap("data/map/wcouloir3.mp","data/map/warped.png")
{
    //ctor
}

Level24::~Level24()
{
    //dtor
}

void Level24::initEni()
{

    enis.add(new Alien(500,300));
    enis.add(new Crab(700,280));
    enis.add(new Jumper(400,280));

    items.add(new Life(200,300));

    if(!player.key(1))items.add(new Key(500,200,1));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(11),52,288),4);
}
