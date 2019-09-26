#ifndef LEVEL6_H
#define LEVEL6_H

#include "../Scene/PlatformMap.h"


class Level6 : public PlatformMap
{
    public:
        Level6();
        virtual ~Level6();
        int level(){return 6;}

    protected:

    private:
        void initEni() ;
};

#endif // LEVEL6_H
