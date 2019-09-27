#include "Start.h"
#include "../MyGame.h"
extern Game* game;


Start::Start(const char* name):ElementMenu(name)
{
    //ctor


}

Start::~Start()
{
    //dtor
}

int Start::action(int val)
{
    dynamic_cast<MyGame *>(game)->begining();
    return Game::PLAY;
}

