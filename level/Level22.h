#ifndef Level22_H
#define Level22_H

#include "../Scene/PlatformMap.h"


class Level22 : public PlatformMap
{
    public:
        Level22();
        virtual ~Level22();
        int level(){return 22;}

    protected:

    private:
        void initEni() ;
};

#endif // Level22_H
