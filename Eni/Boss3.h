#ifndef Boss3_H
#define Boss3_H

#include"Insect2.h"

template <class T> class CustomCollection;
class Item;
class Bullet;

class Boss3 : public Insect2
{
    public:
        Boss3(int x,int y);
        virtual ~Boss3();
        void onDying(CustomCollection<Item>*);
        void fireUpdate(CustomCollection<Bullet>* bullets);


    protected:

    private:

};

#endif // Boss3_H
