#ifndef Level17_H
#define Level17_H

#include "../Scene/PlatformMap.h"


class Level17 : public PlatformMap
{
    public:
        Level17();
        virtual ~Level17();
        int level(){return 17;}

    protected:

    private:
        void initEni() ;
};

#endif // Level17_H
