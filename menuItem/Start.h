#ifndef StartITEM_H
#define StartITEM_H

#include "../menu/ElementMenu.h"

class Start :public ElementMenu
{
    public:
        Start(const char* name);

        virtual ~Start();

        int action(int val=0);



    protected:

    private:


};

#endif // StartITEM_H
