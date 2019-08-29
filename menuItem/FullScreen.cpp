#include "FullScreen.h"
#include "../core/Game.h"

extern Game* game;

FullScreen::FullScreen(const char* name):ElementMenu(name)
{
    //ctor
}

FullScreen::~FullScreen()
{
    //dtor
}

int FullScreen::action(int val)
{
    game->switchFullScreen();
    return val;
}

