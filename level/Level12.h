#ifndef Level12_H
#define Level12_H

#include "../Scene/PlatformMap.h"


class Level12 : public PlatformMap
{
    public:
        Level12();
        virtual ~Level12();
        int level(){return 12;}

    protected:

    private:
        void initEni() ;
};

#endif // Level12_H
