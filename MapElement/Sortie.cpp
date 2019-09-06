#include "Sortie.h"

#include "../Player.h"
#include "../core/Game.h"
#include "../Map/MapProto.h"


extern Player player;

extern Game* game;

Sortie::Sortie(MapProto* destination,int x,int y):m_x(x),m_y(y),m_destination(destination)
{
    //ctor
}

Sortie::~Sortie()
{
    //dtor
}

Sortie::action()
{
    game->goScene(m_destination);
    player.setPosition(m_x,m_y);
    return Game::EXIT_SCN;
}
