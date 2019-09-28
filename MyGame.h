#ifndef MYGAME_H
#define MYGAME_H

#include "core/Game.h"

class Intro;
class MapProto;
class TestScene;
class MusicManager;

class MyGame : public Game
{
    public:
        MyGame();
        virtual ~MyGame();

        MapProto* level(int val);
        Intro* intro;

        void begining();
        void reBoot();

        MusicManager* musicManager(){return m_musicManager;}

    protected:

    private:
        MapProto* m_level[100];
        MusicManager* m_musicManager;



};

#endif // MYGAME_H
