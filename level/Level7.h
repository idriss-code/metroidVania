#ifndef LEVEL7_H
#define LEVEL7_H

#include "../Scene/PlatformMap.h"


class Level7 : public PlatformMap
{
    public:
        Level7();
        virtual ~Level7();
        int level(){return 7;}

    protected:

    private:
        void initEni() ;
};

#endif // LEVEL7_H
