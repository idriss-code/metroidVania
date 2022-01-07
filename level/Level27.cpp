#include "Level27.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/SaveGame.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level27::Level27(): PlatformMap("data/map/save.mp","data/map/warped.png")
{
    //ctor
}

Level27::~Level27()
{
    //dtor
}

void Level27::initEni()
{

    items.add(new SaveGame(196,160));

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(15),340,256),3);
}
