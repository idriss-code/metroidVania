#ifndef WALKINGENI_H
#define WALKINGENI_H

#include "../Eni.h"


class WalkingEni : public Eni
{
    public:
        WalkingEni(int x,int y);
        virtual ~WalkingEni();
        virtual void update(MapProto* mapProto);

    protected:

    private:
        void moov(int vx,int vy);
        void moov();
        void fall();
        void recursiveMoov(int velX,int velY,SDL_Rect hitBox,MapProto* mapProto);
        void fallControle(MapProto* mapProto);

        bool falling;
};

#endif // WALKINGENI_H
