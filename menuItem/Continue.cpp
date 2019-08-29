#include "Continue.h"
#include "../core/Game.h"


Continue::Continue(const char* name):ElementMenu(name)
{
    //ctor


}

Continue::~Continue()
{
    //dtor
}

int Continue::action(int val)
{
    return Game::PLAY;
}

