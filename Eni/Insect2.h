#ifndef Insect2_H
#define Insect2_H

#include "FlyingEni.h"

#include <iostream>

class Insect2 : public FlyingEni
{
    public:
        Insect2(int x,int y);
        virtual ~Insect2();

        virtual void onDying(CustomCollection<Item>*){ std::cout<<"test"<<std::endl;}

    protected:

    private:

};

#endif // Insect2_H
