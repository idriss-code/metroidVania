#include "Scene.h"
#include "Game.h"

extern Game* game;

Scene::Scene(Scene* parent):m_parent(parent),m_clean(true)
{
    //ctor
    setRGB(0,0,0);
}

Scene::~Scene()
{
    //dtor
}

void Scene::exec()
{
    loop=true;
    load();//LOAD

    while(loop)
    {
        //gestion dt
        int currentTime = SDL_GetTicks();
        dt=currentTime - lastTime;
        lastTime = currentTime;

        while(SDL_PollEvent(&event))
        {
            input();
        }
        update(dt);//UPDATE

        if(game->status()== Game::QUIT)loop = 0;//GESTION QUIT GAME

        //********** DRAW ***********
        if(loop)
        {
            if(m_clean)//  remise a zero de l'écran desactivable
            {
                clean();
            }
            draw();//DRAW
        }
        SDL_UpdateWindowSurface(ecran);
        SDL_Delay(30);
    }

    unload();//UNLOAD
}

void Scene::clean()//  remise a zero de l'écran
{
    SDL_FillRect(SDL_GetWindowSurface(ecran),NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,red,green,blue));
}

void Scene::load()
{

}

void Scene::unload()
{

}

void Scene::input()
{

}

void Scene::update(int dt)
{

}

void Scene::draw()
{

}

unsigned int Scene::dt=0;
unsigned int Scene::lastTime=0;
