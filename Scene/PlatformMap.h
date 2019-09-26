#ifndef PLATFORMMAP_H
#define PLATFORMMAP_H

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

    protected:
        virtual void input();
        virtual void load();
        virtual void unload();
        virtual void update(int dt);

        virtual void initEni() = 0;

        virtual int level()=0;

        void TestActionTile();

        CustomCollection<Eni> enis;
        CustomCollection<Bullet> bullets;
        CustomCollection<Item> items;


    private:
        PlatformMap();

        void drawBackground();

        void playerMoov(int velX,int velY,SDL_Rect hitBox);
        void playerFallControle();

        bool menu;

        int countDownBowl;

        int RECT_H;
        int RECT_W;

        SDL_Surface* bkgrnd;

};

#endif // PLATFORMMAP_H
