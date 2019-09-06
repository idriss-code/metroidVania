#ifndef MAPPROTO_H
#define MAPPROTO_H

#include "Maploader.h"
#include "../core/Scene.h"
#include <SDL.h>



class MapElement;

class MapProto : public Maploader, public Scene
{
    public:
        MapProto(const char* file,const char* TileSet,int Zoom=2);
        virtual ~MapProto();
        void addElement(MapElement* val,int position){mapElement[position]=val;}
        MapElement* element(int val){return mapElement[val];}
        virtual void draw()=0;
        void drawMap();
        bool collisionTile(SDL_Rect hitBox,int tile);
        bool collisionWall(SDL_Rect hitBox);
        bool testMoov(int velX, int velY,SDL_Rect hitBox);
        void setCamera(int x,int y){m_cameraX=x;m_cameraY=y;}
        int cameraX(){return m_cameraX;}
        int cameraY(){return m_cameraY;}
        SDL_Rect cameraBox();


    protected:
        virtual void load()=0;
        virtual void unload()=0;
        virtual void input()=0;
        virtual void update(int dt)=0;


    private:
        MapProto();
        SDL_Surface* tileSet;

        MapElement* mapElement[100];

        int zoom;
        int WW;
        int m_cameraX;
        int m_cameraY;
};

void setTunnel(MapProto *map1,int obj1,MapProto* map2,int obj2);

#endif // MAPPROTO_H
