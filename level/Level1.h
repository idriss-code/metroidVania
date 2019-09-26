#ifndef LEVEL1_H
#define LEVEL1_H

#include "../Scene/PlatformMap.h"


class Level1 : public PlatformMap
{
    public:
        Level1();
        virtual ~Level1();
        int level(){return 1;}

    protected:

    private:
        void initEni() ;
};

#endif // LEVEL1_H
