#ifndef PLATFORMMAP_H
#define PLATFORMMAP_H

#include <vector>
using namespace std;
#include "../Map/MapProto.h"
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

    private:
        PlatformMap();

        void playerMoov(int velX,int velY,SDL_Rect hitBox);
        void playerFallControle();
        void newBowl();

        bool menu;

        int countDownBowl;
};

#endif // PLATFORMMAP_H
