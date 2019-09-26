#ifndef Level11_H
#define Level11_H

#include "../Scene/PlatformMap.h"


class Level11 : public PlatformMap
{
    public:
        Level11();
        virtual ~Level11();
        int level(){return 11;}

    protected:

    private:
        void initEni() ;
};

#endif // Level11_H
