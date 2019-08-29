#include "LoachMenu.h"
#include "../core/Game.h"
#include "../Scene/MenuScene.h"

LoachMenu::LoachMenu(Menu *parent,const char* name):ElementMenu(name)
{
    //ctor
    m_parent=parent;
}

LoachMenu::~LoachMenu()
{
    //dtor
}

int LoachMenu::action(int val)
{
    MenuScene::loach(NULL);
    Menu::setMenuActif(m_parent);
    return val;
}

