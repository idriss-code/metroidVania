#ifndef FULLSCREENITEM_H
#define FULLSCREENITEM_H

#include "../menu/ElementMenu.h"

class FullScreen :public ElementMenu
{
    public:
        FullScreen(const char* name);

        virtual ~FullScreen();

        int action(int val=0);



    protected:

    private:


};

#endif // FULLSCREENITEM_H
