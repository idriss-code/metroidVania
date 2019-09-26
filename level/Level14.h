#ifndef Level14_H
#define Level14_H

#include "../Scene/PlatformMap.h"


class Level14 : public PlatformMap
{
    public:
        Level14();
        virtual ~Level14();
        int level(){return 14;}

    protected:

    private:
        void initEni() ;
};

#endif // Level14_H
