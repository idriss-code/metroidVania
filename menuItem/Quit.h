#ifndef QUITITEM_H
#define QUITITEM_H

#include "../menu/ElementMenu.h"


class Quit :public ElementMenu
{
    public:
        Quit(const char* name);

        virtual ~Quit();

        int action(int val=0);



    protected:

    private:


};

#endif // QUITITEM_H
