#ifndef Insect_H
#define Insect_H

#include "FlyingEni.h"

#include <iostream>

class Insect : public FlyingEni
{
    public:
        Insect(int x,int y);
        virtual ~Insect();

    protected:

    private:

};

#endif // Insect_H
