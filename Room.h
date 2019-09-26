#ifndef ROOM_H
#define ROOM_H

#include "core/Scene.h"
enum{WALL,DOOR,NO};

class Room
{
    public:
        Room(int X,int Y,int up,int down,int left,int right);
        virtual ~Room();
        enum{UP,DOWN,LEFT,RIGHT};

        void draw();
        void activate(){activated=true;}

    protected:

    private:
        int x;
        int y;
        int side[4];

        int HEIGHT;
        int WIDTH;
        bool activated;
};

#endif // ROOM_H
