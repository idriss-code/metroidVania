#include "Level26.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"

#include "../Item/SaveGame.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level26::Level26(): PlatformMap("data/map/save.mp","data/map/warped.png")
{
    //ctor
}

Level26::~Level26()
{
    //dtor
}

void Level26::initEni()
{

    items.add(new SaveGame(196,160));

    Door* doorL = new Door(1);
    doorL->remplace(0,this);
    addElement(doorL,10);

    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(22),100,256),3);
}
