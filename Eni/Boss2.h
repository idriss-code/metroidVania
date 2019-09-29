#ifndef Boss2_H
#define Boss2_H

#include"Robot.h"

template <class T> class CustomCollection;
class Item;
class Bullet;

class Boss2 : public Robot
{
    public:
        Boss2(int x,int y);
        virtual ~Boss2();
        void onDying(CustomCollection<Item>*);
        void fireUpdate(CustomCollection<Bullet>* bullets);


    protected:

    private:

};

#endif // Boss2_H
