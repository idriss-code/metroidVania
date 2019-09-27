#include "Boss1.h"

#include "../Player.h"

extern Player player;

Boss1::Boss1(int x,int y):Robot(x,y)
{

}

Boss1::~Boss1()
{

}

void Boss1::onDying(CustomCollection<Item>*)
{
    player.setKey(true,4);
}
