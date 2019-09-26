#ifndef Level13_H
#define Level13_H

#include "../Scene/PlatformMap.h"


class Level13 : public PlatformMap
{
    public:
        Level13();
        virtual ~Level13();
        int level(){return 13;}

    protected:

    private:
        void initEni() ;
};

#endif // Level13_H
