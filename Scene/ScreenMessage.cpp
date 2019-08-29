#include "ScreenMessage.h"
#include <iostream>
#include <cstdio>
#include "../core/Game.h"
#include "../util/fonctionTTF.h"

extern Game* game;

extern SDL_Window *ecran;//  main.cpp
extern TTF_Font* texteFont;
//  fonctionTTF.cpp
extern SDL_Color ROUGE ;

ScreenMessage::ScreenMessage(const char * text,Scene* parent):Scene(parent)
{
    //ctor
    sprintf(m_text,text);
    setRGB(0,0,0);
    delay=50;
    texte=TTF_RenderText_Blended(texteFont,text,ROUGE);
    if(parent != NULL)switchClean();
}

ScreenMessage::~ScreenMessage()
{
    SDL_FreeSurface(texte);
    //dtor
}

void ScreenMessage::load()
{
  std::cerr<<"load ScreenMessage"<<std::endl;
}

void ScreenMessage::unload()
{
    std::cerr<<"unload ScreenMessage"<<std::endl;
}

void ScreenMessage::update(int dt)
{
    switch(event.type)
    {
        case SDL_QUIT:
            game->quit();
            break;
    }

    if(delay-- <= 0)loop=0;
    if(game->status() == Game::QUIT)loop = 0;
}

void ScreenMessage::draw()
{
    if(parent() != NULL)parent()->draw();
    SDL_Rect position;
    position.x=game->screenW()/2-texte->w/2;
    position.y=game->screenH()/2-texte->h/2;

    SDL_UpperBlit(texte,NULL,SDL_GetWindowSurface(ecran),&position);
}

void ScreenMessage::loach(const char * text,Scene* parent)
{
    std::cerr<<"loach ScreenMessage"<<std::endl;
    ScreenMessage* screenMessage = new ScreenMessage(text,parent);
    screenMessage->exec();
    delete screenMessage;
}

void ScreenMessage::loachBckGrnd(const char * text,int r,int g, int b)
{
    std::cerr<<"loach ScreenMessage Bckgrnd"<<std::endl;
    ScreenMessage* screenMessage = new ScreenMessage(text,NULL);
    screenMessage->setRGB(r,g,b);
    screenMessage->exec();
    delete screenMessage;
}
