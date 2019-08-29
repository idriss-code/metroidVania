#include "Quit.h"
#include "../core/Game.h"

extern Game* game;

Quit::Quit(const char* name):ElementMenu(name)
{
    //ctor


}

Quit::~Quit()
{
    //dtor
}

int Quit::action(int val)
{
    game->quit();
    return val;
}

