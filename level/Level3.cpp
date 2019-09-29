#include "Level3.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Eni/Insect.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level3::Level3(): PlatformMap("data/map/wlevel3.mp","data/map/warped.png")
{
    //ctor
}

Level3::~Level3()
{
    //dtor
}

void Level3::initEni()
{

    enis.add(new Insect(500,300));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    Door* doorDR = new Door(1);
    doorDR->remplace(0,this);
    addElement(doorDR,12);

    Door* doorDL = new Door(2);
    doorDL->remplace(0,this);
    addElement(doorDL,13);

// haut gauche
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(2),340,1024),3);
// haut droite
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(18),52,1024),4);
// bas guauche
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(4),1100,256),5);
// bas droite
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(6),52,256),6);
}
