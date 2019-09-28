#include "Intro.h"
#include "../core/Game.h"
#include "MenuIntro.h"

#include <iostream>
#include "../util/fonctionTTF.h"
extern Game* game;

extern SDL_Color ROUGE;
extern TTF_Font* texteFont;


Intro::Intro()
{
    //ctor
}

Intro::~Intro()
{
    //dtor
}


void Intro::load()
{
    std::cerr<<"load"<<std::endl;
}

void Intro::unload()
{
    std::cerr<<"unload"<<std::endl;
}

void Intro::input()
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
                        break;
                    case SDLK_SPACE:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        break;
                }
        }

}

void Intro::update(int dt)
{
        MenuIntro::loach(this);
}

void Intro::draw()
{
    SDL_Rect pos;
    pos.x=270;
    pos.y=50;
    afficheTexte(pos,"Mission",ecran,texteFont,ROUGE);
    pos.x=170;
    pos.y=140;
    afficheTexte(pos,"Intersideral",ecran,texteFont,ROUGE);
}
