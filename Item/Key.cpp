#include "Key.h"

#include "../Player.h"

Key::Key(int x,int y,int keyNumber):Item(x,y)
{
    //ctor

    m_keyNumber=keyNumber;
}

Key::~Key()
{
    //dtor
}

void Key::action(Player* player)
{
    player->setKey(true,m_keyNumber);

    std::cout<<"item action"<<std::endl;
}
