#ifndef LEVEL4_H
#define LEVEL4_H

#include "../Scene/PlatformMap.h"


class Level4 : public PlatformMap
{
    public:
        Level4();
        virtual ~Level4();
        int level(){return 4;}

    protected:

    private:
        void initEni() ;
};

#endif // LEVEL4_H
