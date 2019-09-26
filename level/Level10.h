#ifndef Level10_H
#define Level10_H

#include "../Scene/PlatformMap.h"


class Level10 : public PlatformMap
{
    public:
        Level10();
        virtual ~Level10();
        int level(){return 10;}

    protected:

    private:
        void initEni() ;
};

#endif // Level10_H
