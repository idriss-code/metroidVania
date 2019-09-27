#ifndef Insect_H
#define Insect_H

#include "FlyingEni.h"

#include <iostream>

class Insect : public FlyingEni
{
    public:
        Insect(int x,int y);
        virtual ~Insect();

        virtual void onDying(CustomCollection<Item>*){ std::cout<<"test"<<std::endl;}

    protected:

    private:

};

#endif // Insect_H
