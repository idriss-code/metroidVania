#ifndef Life_H
#define Life_H

#include "Item.h"

class Scene;
class Life : public Item
{
    public:
        Life(int x,int y);
        virtual ~Life();

        virtual void action(Scene* parent);
        void draw(int camX,int camY);

    protected:

    private:
        SDL_Surface* sprite;
        int spriteNumber;
        int countD;
};

#endif // Life_H
