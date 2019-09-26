#include "WalkingEni.h"
#include "../Scene/PlatformMap.h"
#include "../util/collision.h"
#include "../MapElement/MapElement.h"

WalkingEni::WalkingEni(int x,int y):Eni(x,y)
{
    //ctor
    falling = true;
    m_velX=-2;
}

WalkingEni::~WalkingEni()
{
    //dtor
}


void WalkingEni::moov(int vx,int vy)
{
    m_posX+=vx;
    m_posY+=vy;
}

void WalkingEni::moov()
{
    m_posX+=velX();
    m_posY+=velY();
}

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))
void WalkingEni::recursiveMoov(int velX,int velY,SDL_Rect hitBox,MapProto* mapProto)
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
                            //m_velY=-ABS(m_velY);
                            m_velY=0;
                            falling=false;
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


void WalkingEni::fallControle(MapProto* mapProto)
{
    SDL_Rect hitBoxTest=hitBox();
    hitBoxTest.y+=hitBoxTest.h+1;
    hitBoxTest.h=1;
    if(mapProto->collisionWall(hitBoxTest)){
        falling = false;
        return;
    }else if(mapProto->collisionTile(hitBoxTest,2)){
        return;
    }else{
        falling = true;
    }
}

void WalkingEni::fall()
{
    if(falling)m_velY+=1;
    if(m_velY>10)m_velY=10;
}

void WalkingEni::update(MapProto* mapProto)
{
    fallControle(mapProto);
    fall();
    recursiveMoov(velX(),velY(),hitBox(),mapProto);
}
