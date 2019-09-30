#include "LoadGame.h"
#include "../MyGame.h"
extern Game* game;
#include "../Player.h"
extern Player player;

LoadGame::LoadGame(const char* name):ElementMenu(name)
{
    //ctor


}

LoadGame::~LoadGame()
{
    //dtor
}

int LoadGame::action(int val)
{

    player.loadSave("game.sav");
    return Game::PLAY;
}

