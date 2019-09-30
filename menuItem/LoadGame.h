#ifndef LoadGameITEM_H
#define LoadGameITEM_H

#include "../menu/ElementMenu.h"

class LoadGame :public ElementMenu
{
    public:
        LoadGame(const char* name);

        virtual ~LoadGame();

        int action(int val=0);



    protected:

    private:


};

#endif // LoadGameITEM_H
