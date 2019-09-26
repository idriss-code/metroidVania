#ifndef Level18_H
#define Level18_H

#include "../Scene/PlatformMap.h"


class Level18 : public PlatformMap
{
    public:
        Level18();
        virtual ~Level18();
        int level(){return 18;}

    protected:

    private:
        void initEni() ;
};

#endif // Level18_H
