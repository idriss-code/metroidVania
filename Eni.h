#ifndef ENI_H
#define ENI_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
using namespace std;

class MapProto;
class Bullet;
class Item;
template <class T> class CustomCollection;

class Eni
{
    public:
        Eni(int x,int y);
        virtual ~Eni();

        virtual void draw(int camX,int camY);
        virtual void update(MapProto* mapProto);
        virtual void fireUpdate(CustomCollection<Bullet>*);
        virtual void onDying(CustomCollection<Item>*);
        virtual void changeOrientation();
        void moov();

        void setPosition(int x,int y){m_posX=x;m_posY=y;}
        int posX(){return m_posX;}
        int posY(){return m_posY;}
        int width(){return m_width;}
        int height(){return m_height;}

        int xp(){return m_xp;}
        int pv(){return m_pv;}

        void damage(int val){m_pv-=val; damaged=true;}


        SDL_Rect hitBox()
        {
            SDL_Rect hitBox;
            hitBox.w=width();
            hitBox.h=height();
            hitBox.x=posX()-width()/2;
            hitBox.y=posY()-height()/2;
            return hitBox;
        }

        int velX(){return m_velX;}
        int velY(){return m_velY;}

        static void loadSound();
        static void unloadSound();

        static void deathSoundPlay();

    protected:

        int m_posX;
        int m_posY;
        int m_width;
        int m_height;

        int m_velX;
        int m_velY;

        SDL_Surface *m_sprite;
        SDL_Surface *m_spriteI;
        int spriteNumber;

        int m_xp;

        int spriteNumMax;
        int spriteWidth;
        int spriteHeight;
        int spriteCountDown;
        int animationDirection;

        int m_pv;

        int fireCooldown;
        int fireTime;

        static Mix_Chunk *fireSound;
        static Mix_Chunk *deathSound;

    private:

        bool damaged;


};

#endif // ENI_H
