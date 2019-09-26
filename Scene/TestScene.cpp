#include "TestScene.h"
#include "../core/Game.h"
#include "MenuScene.h"
#include "ScreenMessage.h"

#include <iostream>
extern Game* game;


TestScene::TestScene()
{
    //ctor
}

TestScene::~TestScene()
{
    //dtor
}


void TestScene::load()
{
    menu=false;
    message=false;
    std::cerr<<"load"<<std::endl;
}

void TestScene::unload()
{
    std::cerr<<"unload"<<std::endl;
}

void TestScene::input()
{
    switch(event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)//  Gestion des touches du clavier
                {
                    case SDLK_ESCAPE:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        menu=true;
                        break;
                    case SDLK_SPACE:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        message=true;
                        break;
                }
        }

}

void TestScene::update(int dt)
{
    if(menu){
        MenuScene::loach(this);
        menu=false;
    }

    if(message){
        ScreenMessage::loach("test",this);
        message=false;
    }
}

void TestScene::draw()
{

}
