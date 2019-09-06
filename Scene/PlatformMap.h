#ifndef PLATFORMMAP_H
#define PLATFORMMAP_H

#include <vector>
using namespace std;
#include "../Map/MapProto.h"

#include "../CustomCollection.h"

class Eni;
class Bullet;
class Item;

class PlatformMap : public MapProto
{
    public:
        PlatformMap(const char* file,const char* TileSet);
        virtual ~PlatformMap();
        virtual void draw();

        void restart();

    protected:
        virtual void input();
        virtual void load();
        virtual void unload();
        virtual void update(int dt);

        virtual void initPlayer() = 0;
        virtual void initEni() = 0;

        virtual void goNextLevel()=0;

        void TestActionTile();

        CustomCollection<Eni> enis;
        CustomCollection<Bullet> bullets;
        CustomCollection<Item> items;
    private:
        PlatformMap();

        void playerMoov(int velX,int velY,SDL_Rect hitBox);
        void playerFallControle();

        bool menu;

        int countDownBowl;

};

#endif // PLATFORMMAP_H
