#ifndef Level20_H
#define Level20_H

#include "../Scene/PlatformMap.h"


class Level20 : public PlatformMap
{
    public:
        Level20();
        virtual ~Level20();
        int level(){return 20;}

    protected:

    private:
        void initEni() ;
};

#endif // Level20_H
