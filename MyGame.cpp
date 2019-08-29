#include "MyGame.h"

#include <iostream>
#include "util/benrandom.h"
#include "menu/SousMenu.h"
#include "menuItem/Quit.h"
#include "menuItem/Continue.h"


#include "Scene/TestScene.h"

#include "core/Game.h"

using namespace std;

//  variables globales
#include "Player.h"
Player player;


TTF_Font* numberFont=NULL;
TTF_Font* texteFont=NULL;
TTF_Font* menuFont=NULL;

Menu *mPrincipal=NULL;



extern SDL_Color NOIR ;//  fonctionTTF.cpp
extern SDL_Color VERT ;

MyGame::MyGame():Game(800,600)
{
    //ctor

// ***********  CHARGEMENT FONT **********************************

    numberFont=TTF_OpenFont("data/Fette.ttf",15);
    texteFont=TTF_OpenFont("data/Augusta.ttf",80);
    menuFont=TTF_OpenFont("data/Fette.ttf",30);


//*********************************** CHARGEMENT SCENE **********************************
    level1 = new Level1;
    this->setCurrentScene(level1);
}

MyGame::~MyGame()
{
    //dtor
    //  fermeture du programme déchargement des modules et sprites

    TTF_CloseFont(texteFont);
    TTF_CloseFont(menuFont);
    TTF_CloseFont(numberFont);

}


