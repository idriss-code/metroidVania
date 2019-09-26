#ifndef LEVEL3_H
#define LEVEL3_H

#include "../Scene/PlatformMap.h"


class Level3 : public PlatformMap
{
    public:
        Level3();
        virtual ~Level3();
        int level(){return 3;}

    protected:

    private:
        void initEni() ;
};

#endif // LEVEL3_H
