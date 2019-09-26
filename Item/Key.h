#ifndef KEY_H
#define KEY_H

#include "Item.h"


class Key : public Item
{
    public:
        Key(int x,int y,int keyNumber);
        virtual ~Key();

        virtual void action(Player* player,Scene* parent);
        void draw(int camX,int camY);

    protected:

    private:

        int m_keyNumber;
        SDL_Surface* sprite;
};

#endif // KEY_H
