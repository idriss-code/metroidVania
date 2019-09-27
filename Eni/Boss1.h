#ifndef Boss1_H
#define Boss1_H

#include"Robot.h"

template <class T> class CustomCollection;
class Item;
class Bullet;

class Boss1 : public Robot
{
    public:
        Boss1(int x,int y);
        virtual ~Boss1();
        void onDying(CustomCollection<Item>*);
        void fireUpdate(CustomCollection<Bullet>* bullets);


    protected:

    private:

};

#endif // Boss1_H
