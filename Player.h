#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "util/Barre.h"

class Player
{
    public:
        Player();
        virtual ~Player();

        void draw();
        void moov(int vx, int vy);
        void moov();

        void setPosition(int x,int y){m_posX=x;m_posY=y;}
        int posX(){return m_posX;}
        int posY(){return m_posY;}
        int width(){return m_width;}
        int height(){return m_height;}

        bool isFalling(){return falling;}
        void startFalling(){falling=true;}
        void stopFalling(){falling=false;m_velY=0;}
        void fall(){if(falling)m_velY+=1;}

        void init(int x,int y);

        SDL_Rect hitBox()
        {
            SDL_Rect hitBox;
            hitBox.w=width();
            hitBox.h=height();
            hitBox.x=posX()-width()/2;
            hitBox.y=posY()-height()/2;
            return hitBox;
        }

        void goSouth(){m_velY=speed;}
        void goNorth(){if(!falling)m_velY=-20;falling=true;}
        void goEast(){m_velX=speed;}
        void goWest(){m_velX=-speed;}

        void stopSouth(){m_velY=m_velY==speed?0:m_velY;}
        void stopNorth(){m_velY=m_velY==-speed?0:m_velY;}
        void stopEast(){m_velX=m_velX==speed?0:m_velX;}
        void stopWest(){m_velX=m_velX==-speed?0:m_velX;}

        void stopVelY(){m_velY=0;}

        int velX(){return m_velX;}
        int velY(){return m_velY;}

    protected:

    private:
        SDL_Surface *m_sprite;
        int m_posX;
        int m_posY;
        int m_width;
        int m_height;

        int speed;
        int m_velX;
        int m_velY;

        bool falling;

};

#endif // PLAYER_H
