#ifndef ENI_H
#define ENI_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>
using namespace std;

class MapProto;

class Eni
{
    public:
        Eni(int x,int y);
        virtual ~Eni();

        virtual void draw(int camX,int camY);
        virtual void update(MapProto* mapProto);
        void moov();
        void changeDirection();

        void setPosition(int x,int y){m_posX=x;m_posY=y;}
        int posX(){return m_posX;}
        int posY(){return m_posY;}
        int width(){return m_width;}
        int height(){return m_height;}

        int xp(){return m_xp;};


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

    protected:

        int m_posX;
        int m_posY;
        int m_width;
        int m_height;

        int m_velX;
        int m_velY;


private:
    SDL_Surface *m_sprite;
    int m_xp;


};

#endif // ENI_H
