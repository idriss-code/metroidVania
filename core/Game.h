#ifndef GAME_H
#define GAME_H

#include "Scene.h"

class Game
{
    public:
        Game(const char* name = "game",int screenW = 800,int screenH = 600);
        void initSDL();// dans constructeur
        virtual ~Game();

        void main();

        int status(){return m_status;}

        enum {QUIT,RESET,PLAY,MENU,EXIT_SCN};
        void quit(){m_status=QUIT;}
        void reset(){m_status=RESET;}
        void play(){m_status=PLAY;}

        Scene* currentScene(){return m_currentScene;}
        void setCurrentScene(Scene* scene){m_currentScene=scene;}
        void goScene(Scene* scene){m_currentScene->exit();setCurrentScene(scene);}

        void switchFullScreen();
        int screenW(){return m_screenW;};
        int screenH(){return m_screenH;};


    protected:
        int m_status;
        Scene* m_currentScene;
        bool FullScreen;

    private:
        int m_screenH;
        int m_screenW;
};

#endif // GAME_H
