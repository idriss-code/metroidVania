#include "Level24.h"
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
    /*
    enis.add(new Crab(1000,300));
    enis.add(new Alien(900,300));
    enis.add(new Robot(700,280));
    enis.add(new Biped(800,280));
*/
    if(!player.key(1))items.add(new Key(500,200,1));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(11),52,288),4);
}
