#ifndef Boss1_H
#define Boss1_H

#include"Biped.h"

template <class T> class CustomCollection;
class Item;
class Bullet;

class Boss1 : public Biped
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
