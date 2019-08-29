#include "MenuScene.h"
#include "../core/Game.h"

#include "../menu/SousMenu.h"
#include "../menuItem/Quit.h"
#include "../menuItem/Continue.h"
#include "../menuItem/FullScreen.h"


#include <iostream>

extern Game* game;

extern SDL_Window *ecran;//  main.cpp
extern TTF_Font * menuFont;


MenuScene::MenuScene(Scene* parent): Scene(parent)
{
    //ctor
}

MenuScene::~MenuScene()
{
    //dtor
}

void MenuScene::load()
{
    mPrincipal= new Menu(200,100,menuFont,50);
    mPrincipal->addElement(new Continue("Continue"));
    mPrincipal->addElement(new FullScreen("Full Screen"));
    mPrincipal->addElement(new Quit("Quit"));
    Menu::setMenuActif(mPrincipal);
    setRGB(50,100,100);
    if(parent()){
        switchClean();
    }
}

void MenuScene::unload()
{

}


void MenuScene::input()
{
    switch(event.type)
    {
        case SDL_QUIT:
            game->quit();
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    loop=0;
                    break;
                case SDLK_UP:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::menuActif()->up();
                    break;
                case SDLK_DOWN:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::menuActif()->down();
                    break;
                case SDLK_RETURN:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::activation();
                    break;
                case SDLK_BACKSPACE:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::setMenuActif(Menu::menuActif()->menuParent());
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN  :
                switch(event.button.button)//  Gestion des bouton souris
                {
                    case SDL_BUTTON_LEFT:
                        event.button.button=0;
                        Menu::activation();// a optimiser fonctionne en dehor du menu
                        break;
                }
                break;
        case SDL_MOUSEMOTION:
                Menu::menuActif()->onMouse(event.motion.x,event.motion.y);
            break;
    }
}

void MenuScene::update(int dt)
{
    int returnVal =0;
    returnVal = Menu::updateMenu(returnVal);
    if(returnVal == Game::PLAY){
        loop = 0;
    }

    if(game->status() == Game::QUIT)loop = 0;
}

void MenuScene::draw()
{
    if(parent()){
        parent()->clean();
        parent()->draw();
    }

    Menu::menuActif()->affiche(ecran);
}

void MenuScene::loach(Scene* parent)
{
    MenuScene menuScene(parent);
    menuScene.exec();
}
