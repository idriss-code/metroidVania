#include "MyGame.h"

#include <iostream>
#include "util/benrandom.h"
#include "menu/SousMenu.h"
#include "menuItem/Quit.h"
#include "menuItem/Continue.h"
#include "core/Game.h"

#include "level/Level1.h"
#include "level/Level2.h"
#include "level/Level3.h"
#include "level/Level4.h"
#include "level/Level5.h"
#include "level/Level6.h"
#include "level/Level7.h"
#include "level/Level8.h"
#include "level/Level9.h"
#include "level/Level10.h"
#include "level/Level11.h"
#include "level/Level12.h"
#include "level/Level13.h"
#include "level/Level14.h"
#include "level/Level15.h"
#include "level/Level16.h"
#include "level/Level17.h"
#include "level/Level18.h"
#include "level/Level19.h"
#include "level/Level20.h"
#include "level/Level21.h"
#include "level/Level22.h"
#include "level/Level23.h"
#include "level/Level24.h"

#include "Scene/Intro.h"

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

    numberFont=TTF_OpenFont("data/pusab.ttf",10);
    texteFont=TTF_OpenFont("data/Vibes.ttf",80);
    menuFont=TTF_OpenFont("data/pusab.ttf",20);


//*********************************** CHARGEMENT SCENE **********************************
    intro = new Intro();

    m_level[1] = new Level1;
    m_level[2] = new Level2;
    m_level[3] = new Level3;
    m_level[4] = new Level4;
    m_level[5] = new Level5;
    m_level[6] = new Level6;
    m_level[7] = new Level7;
    m_level[8] = new Level8;
    m_level[9] = new Level9;
    m_level[10] = new Level10;
    m_level[11] = new Level11;
    m_level[12] = new Level12;
    m_level[13] = new Level13;
    m_level[14] = new Level14;
    m_level[15] = new Level15;
    m_level[16] = new Level16;
    m_level[17] = new Level17;
    m_level[18] = new Level18;
    m_level[19] = new Level19;
    m_level[20] = new Level20;
    m_level[21] = new Level21;
    m_level[22] = new Level22;
    m_level[23] = new Level23;
    m_level[24] = new Level24;

    this->setCurrentScene(intro);
}

MyGame::~MyGame()
{
    //dtor
    //  fermeture du programme déchargement des modules et sprites

    TTF_CloseFont(texteFont);
    TTF_CloseFont(menuFont);
    TTF_CloseFont(numberFont);

}

MapProto* MyGame::level(int val)
{

    return m_level[val];
}

void MyGame::begining()
{
    player.init(128,128);
    this->goScene(level(1));
}

void MyGame::reBoot()
{
    this->goScene(intro);
}
