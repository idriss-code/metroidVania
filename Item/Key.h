#ifndef KEY_H
#define KEY_H

#include "Item.h"


class Key : public Item
{
    public:
        Key(int x,int y,int keyNumber);
        virtual ~Key();

        virtual void action(Player* player);

    protected:

    private:

        int m_keyNumber;
};

#endif // KEY_H
