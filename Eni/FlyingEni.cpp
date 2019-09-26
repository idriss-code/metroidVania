#include "FlyingEni.h"
#include "../Scene/PlatformMap.h"
#include "../util/collision.h"
#include "../MapElement/MapElement.h"

FlyingEni::FlyingEni(int x,int y):Eni(x,y)
{
    //ctor
    m_velX=-2;
    m_velY=2;
}

FlyingEni::~FlyingEni()
{
    //dtor
}


void FlyingEni::moov(int vx,int vy)
{
    m_posX+=vx;
    m_posY+=vy;
}

void FlyingEni::moov()
{
    m_posX+=velX();
    m_posY+=velY();
}

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))
void FlyingEni::recursiveMoov(int velX,int velY,SDL_Rect hitBox,MapProto* mapProto)
{
    // division du mouvement trop rapide
    if(velX >= mapProto->tileWidth() || velY >= mapProto->tileHeight() )
    {
        recursiveMoov(velX/2,velY/2,hitBox,mapProto);
        recursiveMoov(velX-velX/2,velY-velY/2,hitBox,mapProto);
        return;
    }

    //mouvement sans mur
    if(mapProto->testMoov(velX,velY,hitBox)){
        moov(velX,velY);
    }else{
        SDL_Rect hitBoxTest=hitBox;
        SDL_Rect hitBoxTile;
        hitBoxTest.x+=velX;
        hitBoxTest.y+=velY;
        hitBoxTile.w=mapProto->tileWidth();
        hitBoxTile.h=mapProto->tileHeight();

        int test=true;
        for(int i=0;i< mapProto->width() && test;i++){
            for(int j=0;j< mapProto->height() && test;j++){
                if(mapProto->element(mapProto->obj(i,j))->isAWall()){
                    hitBoxTile.x=i*mapProto->tileWidth();
                    hitBoxTile.y=j*mapProto->tileHeight();
                    if(boxCollision(hitBoxTest,hitBoxTile))
                    {
                        test=false;
                        if(hitBox.y+hitBox.h<=hitBoxTile.y && ! mapProto->element(mapProto->obj(i,j-1))->isAWall()){
                            setPosition(posX(),hitBoxTile.y-(hitBox.h/2+hitBox.h%2));
                            //action collision sol
                            m_velY=-ABS(m_velY);
                            //m_velY=0;
                            //std::cerr<<"down"<<std::endl;
                        }
                        if(hitBox.y>=hitBoxTile.y+hitBoxTile.h &&  ! mapProto->element(mapProto->obj(i,j+1))->isAWall()){
                            setPosition(posX(),hitBoxTile.y+hitBoxTile.h+(hitBox.h/2+hitBox.h%2));
                            //action collision plafond
                            m_velY=ABS(m_velY);
                            //std::cerr<<"up"<<std::endl;
                        }

                        if(hitBox.x+hitBox.w<=hitBoxTile.x && ! mapProto->element(mapProto->obj(i-1,j))->isAWall()){
                            setPosition(hitBoxTile.x-(hitBox.w/2+hitBox.w%2),posY());
                            //action collision mur droite
                            m_velX=-ABS(m_velX);
                            //std::cerr<<"right"<<std::endl;
                        }
                        if(hitBox.x>=hitBoxTile.x+hitBoxTile.w && ! mapProto->element(mapProto->obj(i+1,j-1))->isAWall()){
                            setPosition(hitBoxTile.x+hitBoxTile.w+(hitBox.w/2+hitBox.w%2),posY());
                            //action collision mur guauche
                            m_velX=ABS(m_velX);
                            //std::cerr<<"left"<<std::endl;
                        }

                    }
                }
            }
        }
    }
}


void FlyingEni::update(MapProto* mapProto)
{
    recursiveMoov(velX(),velY(),hitBox(),mapProto);
}
