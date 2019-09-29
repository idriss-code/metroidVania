#include "Level11.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

#include "../Eni/Insect.h"

extern Game* game;

extern Player player;

Level11::Level11(): PlatformMap("data/map/wlevel11.mp","data/map/warped.png")
{
    //ctor
}

Level11::~Level11()
{
    //dtor
}

void Level11::initEni()
{
    enis.add(new Insect(500,300));
    enis.add(new Insect(400,500));

    Door* doorR = new Door(1);
    doorR->remplace(0,this);
    addElement(doorR,11);

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    Door* doorDR = new Door(1);
    doorDR->remplace(0,this);
    addElement(doorDR,12);

    Door* doorDL = new Door(3);
    doorDL->remplace(0,this);
    addElement(doorDL,13);

// haut gauche
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(24),1100,256),3);
// haut droite
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(10),52,256),4);
// bas guauche
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(12),1100,256),5);
// bas droite
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(14),52,256),6);
}
