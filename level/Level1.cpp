#include "Level1.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../WalkingEni.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"
#include "../MapElement/Sortie.h"

extern Game* game;

extern Player player;

Level1::Level1(): PlatformMap("data/map/metroid1.mp","data/map/caisse.png")
{
    //ctor
}

Level1::~Level1()
{
    //dtor
}

void Level1::initPlayer()
{
    player.init(128,128);
}

void Level1::initEni()
{
    enis.add(new WalkingEni(800,1000));
    enis.add(new Eni(200,1000));
    enis.add(new Eni(300,1000));
    enis.add(new Eni(400,1000));
    enis.add(new Eni(500,1000));

    items.add(new Key(500,1000,1));

    Door* door = new Door(1);
    door->remplace(2,4,this);
    addElement(door,2);
    addElement(new Sortie(dynamic_cast<MyGame *>(game)->level(2),80,1183),3);
}



//inutile
void Level1::goNextLevel()
{
    std::cout<<"goNextLevel"<<std::endl;

    //dynamic_cast<MyGame *>(game)->goScene(10);
}