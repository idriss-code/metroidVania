#ifndef Level27_H
#define Level27_H

#include "../Scene/PlatformMap.h"


class Level27 : public PlatformMap
{
    public:
        Level27();
        virtual ~Level27();
        int level(){return 27;}

    protected:

    private:
        void initEni() ;
};

#endif // Level27_H
