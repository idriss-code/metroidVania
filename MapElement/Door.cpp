#include "Door.h"

#include "../Player.h"
#include "../Map/MapProto.h"
extern Player player;

Door::Door(int key)
{
    keyNumber=key;
}

Door::~Door()
{
    //dtor
}

bool Door::isAWall() const
{
	//si pas cle pas cle on passe pas
	return ! player.key(keyNumber);
}
bool Door::doActionOnEnter() const
{
	//si cle ok on passe et on change la tile
	return player.key(keyNumber);;;
}

int Door::action()
{
	//change tile on open
	//void setTile(int x,int y, int val){tileMap[x][y]=val;}
	for (int i=0; i < map->width(); i++)
            for (int j=0; j < map->height(); j++)
                //if(map->tile(i,j)==aRemplacer)map->setTile(i,j,remplaceant);
                if(map->element(map->obj(i,j))== this)map->setTile(i,j,remplaceant);
	return 0;
}
