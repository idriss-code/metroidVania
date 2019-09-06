#include "Level2.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
#include "../WalkingEni.h"

#include "../Item/Key.h"
#include "../MapElement/Door.h"

extern Game* game;

extern Player player;

Level2::Level2(): PlatformMap("data/map/metroid2.mp","data/map/caisse.png")
{
    //ctor
}

Level2::~Level2()
{
    //dtor
}

void Level2::initPlayer()
{
    player.init(128,128);
}

void Level2::initEni()
{
    enis.add(new WalkingEni(800,950));
    enis.add(new Eni(200,1000));
    enis.add(new Eni(300,1000));
    enis.add(new Eni(400,1000));
    enis.add(new Eni(500,1000));

    items.add(new Key(500,1100,1));

    Door* door = new Door(1);
    door->remplace(3,2,this);
    addElement(door,3);
}

void Level2::goNextLevel()
{
    std::cout<<"goNextLevel"<<std::endl;

    //dynamic_cast<MyGame *>(game)->goScene(10);
}
