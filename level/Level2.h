#ifndef LEVEL2_H
#define LEVEL2_H

#include "../Scene/PlatformMap.h"


class Level2 : public PlatformMap
{
    public:
        Level2();
        virtual ~Level2();
        int level(){return 2;}

    protected:

    private:
        void initEni() ;
};

#endif // LEVEL2_H
