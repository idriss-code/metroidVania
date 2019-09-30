#ifndef SaveGame_H
#define SaveGame_H

#include "Item.h"

class Scene;
class SaveGame : public Item
{
    public:
        SaveGame(int x,int y);
        virtual ~SaveGame();

        virtual void action(Scene* parent);
        void draw(int camX,int camY);

    protected:

    private:
        SDL_Surface* sprite;
        int spriteNumber;
};

#endif // SaveGame_H
