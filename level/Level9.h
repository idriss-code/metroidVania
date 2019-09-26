#ifndef Level9_H
#define Level9_H

#include "../Scene/PlatformMap.h"


class Level9 : public PlatformMap
{
    public:
        Level9();
        virtual ~Level9();
        int level(){return 9;}

    protected:

    private:
        void initEni() ;
};

#endif // Level9_H
