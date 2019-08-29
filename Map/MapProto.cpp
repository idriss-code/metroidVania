#include "MapProto.h"

#include "../util/collision.h"
#include "../gfx/SDL2_rotozoom.h"

#include "../MapElement/Plan.h"
#include "../MapElement/Wall.h"
#include "../MapElement/Sortie.h"

#include <iostream>
using namespace std;

#include "../core/Game.h"
extern Game* game;


//  position du hero sur la map(pas sur l'ecran)

MapProto::MapProto(const char* file,const char* TileSet,int Zoom): Maploader(file),zoom(Zoom)
{
        m_cameraX=0;
        m_cameraY=0;
    //chargement du tileset et mise a l'echelle
        tileSet = IMG_Load(TileSet);
        SDL_Surface *temp = zoomSurface(tileSet,zoom,zoom,SMOOTHING_OFF);
        SDL_FreeSurface(tileSet);
        tileSet = temp;
        m_tileWidth = tileWidth()*zoom;
        m_tileHeight = tileHeight()*zoom;

    // valeur par default des objet tuile
        MapElement* tempEl = new Plan;
        for(int i=0;i<100;i++){mapElement[i]=tempEl;}
    // ajout des mur
        addElement(new Wall,0);
        WW =tileSet->w/tileWidth();
}

MapProto::~MapProto()
{
    SDL_FreeSurface(tileSet);
}

SDL_Rect MapProto::cameraBox(){
    SDL_Rect box;
    box.x=m_cameraX;
    box.y=m_cameraY;
    box.h=game->screenH();
    box.w=game->screenW();
    return box;
}



void MapProto::drawMap()
{
    SDL_Rect position,source;

    //calcul du nombre de tuile pas écran (écran doit etre initilisé)
    int nbtuecranx=game->screenW()/tileWidth();
    int nbtuecrany=game->screenH()/tileHeight();

    int beginX = cameraX()/tileWidth();
    int beginY = cameraY()/tileHeight();
    int endX = beginX + nbtuecranx +3 ;
    int endY = beginY + nbtuecrany +3 ;

    for(int i=beginX ; i < endX; i++){// affiche seulement ce qui est a l'ecran
        for(int j=beginY; j < endY ; j++){
//  for(int i=0;i<width();i++){
//      for(int j=0;j<height();j++){
            if (i>=0&&i< this->width()&&j>=0&&j< this->height()){

                position.h=tileHeight();
                source.h=tileHeight();
                position.w=tileWidth();
                source.w=tileWidth();

                position.x=i*tileWidth()-cameraX();
                position.y=j*tileHeight()-cameraY();

                source.x = tile(i,j)%WW*tileWidth();
                source.y = tile(i,j)/WW*tileHeight();

                SDL_BlitSurface(tileSet,&source,SDL_GetWindowSurface(ecran),&position);
            }
        }
    }
}

bool MapProto::collisionTile(SDL_Rect hitBox,int tile)
{
    /*test de collision obstacle */
        SDL_Rect hitBoxTest=hitBox;
        SDL_Rect hitBoxTile;
        hitBoxTile.w=tileWidth();
        hitBoxTile.h=tileHeight();
        int test=false;

        for(int i=0;i<width() && !test;i++){// voir pour double breack;
            for(int j=0;j<height() && !test;j++){
                if(obj(i,j) == tile){
                    hitBoxTile.x=i*tileWidth();
                    hitBoxTile.y=j*tileHeight();
                    if(boxCollision(hitBoxTest,hitBoxTile))
                    {
                        test=true;
                    }
                }
            }
        }
        return test;
}

bool MapProto::collisionWall(SDL_Rect hitBox)
{
    /*test de collision obstacle */
        SDL_Rect hitBoxTest=hitBox;
        SDL_Rect hitBoxWall;
        hitBoxWall.w=tileWidth();
        hitBoxWall.h=tileHeight();
        int test=false;

        for(int i=0;i<width() && !test;i++){// voir pour double breack;
            for(int j=0;j<height() && !test;j++){
                if(mapElement[obj(i,j)]->isAWall()){
                    hitBoxWall.x=i*tileWidth();
                    hitBoxWall.y=j*tileHeight();
                    if(boxCollision(hitBoxTest,hitBoxWall))
                    {
                        test=true;
                    }
                }
            }
        }
        return test;
}

bool MapProto::testMoov(int velX, int velY,SDL_Rect hitBox)
{
        hitBox.x+=velX;
        hitBox.y+=velY;
        return !collisionWall(hitBox);
}

void setTunnel(MapProto *map1,int obj1,MapProto* map2,int obj2)
{
    int x1(0),x2(0),y1(0),y2(0);
    for(int i = 0;i<map1->width();i++){
        for(int j = 0;j<map1->height();j++){
            if (map1->obj(i,j)==obj1){
                x1=i;
                y1=j;
            }
        }
    }
    for(int i = 0;i<map2->width();i++){
        for(int j = 0;j<map2->height();j++){
            if (map2->obj(i,j)==obj2){
                x2=i;
                y2=j;
            }
        }
    }
    y1+=2;
    y2+=2;
    map1->addElement(new Sortie(map2,x2*map2->tileWidth()+map2->tileWidth()/2,y2*map2->tileHeight()),obj1);
    map2->addElement(new Sortie(map1,x1*map1->tileWidth()+map1->tileWidth()/2,y1*map1->tileHeight()),obj2);
}
