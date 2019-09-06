#ifndef MYGAME_H
#define MYGAME_H

#include "core/Game.h"

class Level1;
class Level2;
class MapProto;

class MyGame : public Game
{
    public:
        MyGame();
        virtual ~MyGame();

        MapProto* level(int val);

    protected:

    private:
        Level1* level1;
        Level2* level2;

};

#endif // MYGAME_H
