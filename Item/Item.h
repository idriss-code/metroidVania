#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

class MapProto;
class Scene;

class Item
{
    public:
        Item(int x,int y);
        virtual ~Item();

        virtual void draw(int camX,int camY)=0;

        void setPosition(int x,int y){m_posX=x;m_posY=y;}
        int posX(){return m_posX;}
        int posY(){return m_posY;}
        int width(){return m_width;}
        int height(){return m_height;}
        virtual void action(Scene* parent)=0;

        static void playSound();
        static void loadSound();
        static void unloadSound();

        SDL_Rect hitBox()
        {
            SDL_Rect hitBox;
            hitBox.w=width();
            hitBox.h=height();
            hitBox.x=posX()-width()/2;
            hitBox.y=posY()-height()/2;
            return hitBox;
        }

    protected:
        int m_posX;
        int m_posY;
        int m_width;
        int m_height;

	private:

	    static Mix_Chunk *sound;

};

#endif // ITEM_H
