#ifndef Level25_H
#define Level25_H

#include "../Scene/PlatformMap.h"


class Level25 : public PlatformMap
{
    public:
        Level25();
        virtual ~Level25();
        int level(){return 25;}

    protected:

    private:
        void initEni() ;
};

#endif // Level25_H
