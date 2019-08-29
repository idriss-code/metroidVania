#ifndef LOACHMENUITEM_H
#define LOACHMENUITEM_H

#include "../menu/ElementMenu.h"
#include "../menu/Menu.h"

class LoachMenu :public ElementMenu
{
    public:
        LoachMenu(Menu *parent,const char* name);

        virtual ~LoachMenu();

        int action(int val=0);

    protected:

    private:
        Menu *m_parent;

};

#endif // LOACHMENUITEM_H
