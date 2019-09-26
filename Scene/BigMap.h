#ifndef BIGMAP_H
#define BIGMAP_H

#include "../core/Scene.h"
#include "../CustomCollection.h"

class Item;
class Room;
class BigMap : public Scene
{
    public:
        BigMap();
        virtual ~BigMap();

    protected:
        virtual void load();
        virtual void unload();
        virtual void input();
        virtual void update(int dt);
        virtual void draw();

    private:
        //doit correspondre à Player
        static const int LVL=100;
        static const int PART=10;
        Room* rooms[LVL][PART];
        bool fullMap;

        void loadCorridor(int x,int y,int id);
        void loadKey(int x,int y,int id);
        void loadBoss(int x,int y,int id);
        void loadStairs(int x,int y,int id);

        CustomCollection<Item> items;

};

#endif // BIGMAP_H
