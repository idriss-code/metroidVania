#ifndef Level15_H
#define Level15_H

#include "../Scene/PlatformMap.h"


class Level15 : public PlatformMap
{
    public:
        Level15();
        virtual ~Level15();
        int level(){return 15;}

    protected:

    private:
        void initEni() ;
};

#endif // Level15_H
