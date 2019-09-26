#ifndef FlyingEni_H
#define FlyingEni_H

#include "../Eni.h"


class FlyingEni : public Eni
{
    public:
        FlyingEni(int x,int y);
        virtual ~FlyingEni();
        virtual void update(MapProto* mapProto);

    protected:

    private:
        void moov(int vx,int vy);
        void moov();
        void recursiveMoov(int velX,int velY,SDL_Rect hitBox,MapProto* mapProto);
};

#endif // FlyingEni_H
