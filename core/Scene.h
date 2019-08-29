#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

extern SDL_Window *ecran;//  main.cpp
class Game;
class Scene
{
    public:
        Scene(Scene* parent = NULL);
        virtual ~Scene();

        void exec();
        void exit(){loop=0;}
        void setRGB(int r,int g,int b){red =r,green=g,blue=b;}

        Scene* parent(){return m_parent;};

        virtual void draw();
        void clean();

    protected:
        virtual void load();
        virtual void unload();
        virtual void input();
        virtual void update(int dt);

        bool loop;
        SDL_Event event;
        void switchClean(){m_clean = !m_clean;}

    private:
        static unsigned int dt;
        static unsigned int lastTime;
        int red,green,blue;
        Scene* m_parent;
        bool m_clean;

};

#endif // SCENE_H
