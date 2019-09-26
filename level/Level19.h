#ifndef Level19_H
#define Level19_H

#include "../Scene/PlatformMap.h"


class Level19 : public PlatformMap
{
    public:
        Level19();
        virtual ~Level19();
        int level(){return 19;}

    protected:

    private:
        void initEni() ;
};

#endif // Level19_H
