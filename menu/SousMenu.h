#ifndef SOUSMENU_H
#define SOUSMENU_H

#include "ElementMenu.h"
#include "Menu.h"


class SousMenu :public Menu, public ElementMenu
{
    public:
        SousMenu(const char* name,Menu* parent,bool chaine=false);

        virtual ~SousMenu();

        int action(int val=0){Menu::setMenuActif(this);return val;}

        virtual void affiche(SDL_Window *ecran);


    protected:

    private:
                bool m_chaine;

};

#endif // SOUSMENU_H
