#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "util/Barre.h"
class Bullet;
class Scene;
template <class T> class CustomCollection;

class Player
{
    public:
        Player();
        virtual ~Player();

        void draw();
        void moov(int vx, int vy);
        void moov();

        void fire(CustomCollection<Bullet>*);

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
        void goEast(){m_velX=speed;orientation=RIGHT;}
        void goWest(){m_velX=-speed;orientation=LEFT;}

        void stopSouth(){m_velY=m_velY==speed?0:m_velY;}
        void stopNorth(){m_velY=m_velY==-speed?0:m_velY;}
        void stopEast(){m_velX=m_velX==speed?0:m_velX;}
        void stopWest(){m_velX=m_velX==-speed?0:m_velX;}

        void stopVelY(){m_velY=0;}

        int velX(){return m_velX;}
        int velY(){return m_velY;}

        int xp(){return m_xp;}
        int gainXp(int val,Scene* parent);
        int lvl(){return m_lvl;}

        int pv(){return m_pv;}
        void damage(int val);
        bool getKey(int keyNumber){return key[keyNumber];}
        void setKey(bool val,int keyNumber){key[keyNumber]=val;}

    protected:

    private:
        SDL_Surface *m_sprite;
        SDL_Surface *m_sprite2;
        SDL_Surface *m_sprite3;
        int m_posX;
        int m_posY;
        int m_width;
        int m_height;

        int speed;
        int m_velX;
        int m_velY;

        bool falling;
        enum {LEFT,RIGHT};
        int orientation;

        int m_xp;
        int m_lvl;
        int XP_LVL;
        int m_xpLvlSuivant;

        int m_pv;
        int m_pvMax;

        Barre pvBarre;
        Barre xpBarre;

        //inventaire des key getter et adder
        bool key[10];
};

#endif // PLAYER_H
