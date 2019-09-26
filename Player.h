#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

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

        void draw(int camX,int camY);
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
        void stopFalling(){falling=false;m_velY=0;status=velX()!=0?RUN:STAND;spriteNumber=0;}
        void fall(){if(falling)m_velY+=2;}

        void hurtControl(){
            if(status==HURT){
                if(--hurtCooldown<0){
                    status=STAND;
                    m_velX=0;
                }
            }
        }

        bool isHurt(){return status==HURT;}

        void init(int x,int y);

        SDL_Rect hitBox();

        void goSouth(){if(m_velY==0)m_velX=0,status=DUCK;}
        void goNorth(){if(!falling || dJump)m_velY=-24;status=JUMP;spriteNumber=0;if(falling)dJump=false;falling=true;}
        void goEast(){m_velX=speed;orientation=RIGHT;if(status!=JUMP)status=RUN;spriteNumber=0;}
        void goWest(){m_velX=-speed;orientation=LEFT;if(status!=JUMP)status=RUN;spriteNumber=0;}

        void stopSouth(){}//{m_velY=m_velY==speed?0:m_velY;}
        void stopNorth(){}//{m_velY=m_velY==-speed?0:m_velY;}
        void stopEast(){if(status!=JUMP)status=m_velX==-speed?RUN:STAND,spriteNumber=0;m_velX=m_velX==speed?0:m_velX;}
        void stopWest(){if(status!=JUMP)status=m_velX==speed?RUN:STAND,spriteNumber=0;m_velX=m_velX==-speed?0:m_velX;}

        void stopVelY(){m_velY=0;}

        int velX(){return m_velX;}
        int velY(){return m_velY;}

        int xp(){return m_xp;}
        int xpMax(){return m_xpLvlSuivant;}
        int gainXp(int val,Scene* parent);
        int lvl(){return m_lvl;}

        int pv(){return m_pv;}
        int pvMax(){return m_pvMax;}
        void damage(int val);

        bool key(int keyNumber){return m_key[keyNumber];}
        void setKey(bool val,int keyNumber){m_key[keyNumber]=val;}

        bool doubleJump(){return m_doubleJump;}
        void setDoubleJump(){m_doubleJump=true;}

        bool visitedRoom(int room,int part){return rooms[room][part];}
        void setCurrentRoom(int room,int part);
        int getRoom(){return currentRoom;}
        int getPart(){return currentPart;}
        void resetJump(){if(m_doubleJump)dJump=true;}

    protected:

    private:
        int m_posX;
        int m_posY;
        int m_width;
        int m_height;

        int speed;
        int m_velX;
        int m_velY;

        bool falling;

        int m_xp;
        int m_lvl;
        int XP_LVL;
        int m_xpLvlSuivant;

        int m_pv;
        int m_pvMax;

        Barre pvBarre;
        Barre xpBarre;

        //inventaire des key getter et adder
        bool m_key[4];
        bool m_doubleJump;

        //doit correspondre à Big Map
        static const int LVL=100;
        static const int PART=10;
        bool rooms[LVL][PART];
        int currentRoom;
        int currentPart;

        //Sprite
        enum{DUCK,STAND,JUMP,RUN,HURT};
        int status;
        bool firing;
        bool dJump;
        enum {LEFT,RIGHT};
        int orientation;
        int spriteWidth;
        int spriteHeight;
        int spriteNumber;

        int hurtCooldown;

        SDL_Surface* duckSprite;
        SDL_Surface* duckSpriteI;

        SDL_Surface* jumpSprite;
        SDL_Surface* jumpSpriteI;

        SDL_Surface* fireSprite;
        SDL_Surface* fireSpriteI;

        SDL_Surface* runSprite;
        SDL_Surface* runSpriteI;

        SDL_Surface* runFireSprite;
        SDL_Surface* runFireSpriteI;

        SDL_Surface* idleSprite;
        SDL_Surface* idleSpriteI;

        SDL_Surface* hurtSprite;
        SDL_Surface* hurtSpriteI;

};

#endif // PLAYER_H
