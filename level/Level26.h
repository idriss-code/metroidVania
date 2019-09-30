#ifndef Level26_H
#define Level26_H

#include "../Scene/PlatformMap.h"


class Level26 : public PlatformMap
{
    public:
        Level26();
        virtual ~Level26();
        int level(){return 26;}

    protected:

    private:
        void initEni() ;
};

#endif // Level26_H
