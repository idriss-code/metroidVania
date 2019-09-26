#ifndef BounceEni_H
#define BounceEni_H

#include "../Eni.h"


class BounceEni : public Eni
{
    public:
        BounceEni(int x,int y);
        virtual ~BounceEni();
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

#endif // BounceEni_H
