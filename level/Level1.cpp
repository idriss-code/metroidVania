#include "Level1.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
extern Game* game;

extern Player player;

Level1::Level1(): PlatformMap("data/map/caisse2.mp","data/map/caisse.png")
{
    std::cerr<<"test"<<std::endl;
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

}



void Level1::goNextLevel()
{
    std::cout<<"goNextLevel"<<std::endl;

    //dynamic_cast<MyGame *>(game)->goScene(10);
}
