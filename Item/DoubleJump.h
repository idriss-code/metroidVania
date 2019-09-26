#ifndef DoubleJump_H
#define DoubleJump_H

#include "Item.h"

class Scene;
class DoubleJump : public Item
{
    public:
        DoubleJump(int x,int y);
        virtual ~DoubleJump();

        virtual void action(Player* player,Scene* parent);
        void draw(int camX,int camY);

    protected:

    private:
        SDL_Surface* sprite;
        int spriteNumber;
};

#endif // DoubleJump_H
