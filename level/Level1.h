#ifndef LEVEL1_H
#define LEVEL1_H

#include "../Scene/PlatformMap.h"


class Level1 : public PlatformMap
{
    public:
        Level1();
        virtual ~Level1();

    protected:

    private:
        void initPlayer();
        void initEni() ;
        void goNextLevel();//WTF
};

#endif // LEVEL1_H
