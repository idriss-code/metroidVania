#ifndef CONTINUEITEM_H
#define CONTINUEITEM_H

#include "../menu/ElementMenu.h"

class Continue :public ElementMenu
{
    public:
        Continue(const char* name);

        virtual ~Continue();

        int action(int val=0);



    protected:

    private:


};

#endif // CONTINUEITEM_H
