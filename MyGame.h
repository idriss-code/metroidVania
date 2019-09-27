#ifndef MYGAME_H
#define MYGAME_H

#include "core/Game.h"

class Intro;
class MapProto;
class TestScene;

class MyGame : public Game
{
    public:
        MyGame();
        virtual ~MyGame();

        MapProto* level(int val);
        Intro* intro;

        void begining();
        void reBoot();

    protected:

    private:
        MapProto* m_level[100];



};

#endif // MYGAME_H
