#include "SousMenu.h"

SousMenu::SousMenu(const char* name,Menu* parent,bool chaine):Menu(parent),ElementMenu(name),m_chaine(chaine)
{
    //ctor
        if(chaine){
                m_x+=parent->longueur();
                m_y+=(parent->vecSize()*parent->hauteurLigne());
        }

}

SousMenu::~SousMenu()
{
    //dtor
}

void SousMenu::affiche(SDL_Window *ecran)
{
    Menu::affiche(ecran);
        if(m_chaine&&m_menuParent!=this)m_menuParent->affiche(ecran);
}
