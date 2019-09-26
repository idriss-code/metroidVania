#ifndef MYGAME_H
#define MYGAME_H

#include "core/Game.h"

class Level1;
class Level2;
class Level3;
class MapProto;
class TestScene;

class MyGame : public Game
{
    public:
        MyGame();
        virtual ~MyGame();

        MapProto* level(int val);

    protected:

    private:
        MapProto* m_level[100];

};

#endif // MYGAME_H
