#ifndef Level8_H
#define Level8_H

#include "../Scene/PlatformMap.h"


class Level8 : public PlatformMap
{
    public:
        Level8();
        virtual ~Level8();
        int level(){return 8;}

    protected:

    private:
        void initEni() ;
};

#endif // Level8_H
