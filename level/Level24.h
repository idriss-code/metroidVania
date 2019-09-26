#ifndef Level24_H
#define Level24_H

#include "../Scene/PlatformMap.h"


class Level24 : public PlatformMap
{
    public:
        Level24();
        virtual ~Level24();
        int level(){return 1;}

    protected:

    private:
        void initEni() ;
};

#endif // Level24_H
