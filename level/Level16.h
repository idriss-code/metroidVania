#ifndef Level16_H
#define Level16_H

#include "../Scene/PlatformMap.h"


class Level16 : public PlatformMap
{
    public:
        Level16();
        virtual ~Level16();
        int level(){return 16;}

    protected:

    private:
        void initEni() ;
};

#endif // Level16_H
