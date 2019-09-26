#ifndef Level21_H
#define Level21_H

#include "../Scene/PlatformMap.h"


class Level21 : public PlatformMap
{
    public:
        Level21();
        virtual ~Level21();
        int level(){return 21;}

    protected:

    private:
        void initEni() ;
};

#endif // Level21_H
