#ifndef MYGAME_H
#define MYGAME_H

#include "core/Game.h"
#include "level/Level1.h"


class MyGame : public Game
{
    public:
        MyGame();
        virtual ~MyGame();

    protected:

    private:
        Level1* level1;

};

#endif // MYGAME_H
