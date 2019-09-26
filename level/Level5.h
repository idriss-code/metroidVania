#ifndef LEVEL5_H
#define LEVEL5_H

#include "../Scene/PlatformMap.h"


class Level5 : public PlatformMap
{
    public:
        Level5();
        virtual ~Level5();
        int level(){return 5;}

    protected:

    private:
        void initEni() ;
};

#endif // LEVEL5_H
