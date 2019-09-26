#ifndef Level23_H
#define Level23_H

#include "../Scene/PlatformMap.h"


class Level23 : public PlatformMap
{
    public:
        Level23();
        virtual ~Level23();
        int level(){return 23;}

    protected:

    private:
        void initEni() ;
};

#endif // Level23_H
