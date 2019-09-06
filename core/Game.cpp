#include "Game.h"

#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

SDL_Window *ecran = NULL;//  chargé en variable globale pour simplifier la syntaxe

Game::Game(int screenW ,int screenH ):m_status(PLAY),m_screenH(screenH),m_screenW(screenW)
{
    FullScreen=false;
    //ctor
    initSDL();

    // **************************************** INIT ECRAN ****************************
    ecran = SDL_CreateWindow("Game",
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          screenW, screenH,
                          SDL_WINDOW_OPENGL);
}

Game::~Game()
{
    //dtor
    Mix_CloseAudio();
    while(Mix_Init(0))Mix_Quit();// force a quit

    TTF_Quit();
    SDL_DestroyWindow(ecran);
    SDL_Quit();
}

void Game::main()
{
    while(this->status()!=QUIT){
        this->play();
        while(this->status()==PLAY){
            this->currentScene()->exec();
        }
    }
}

void Game::initSDL()
{
    //*******************************  INIT SDL  **************************************************
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cerr<<"Unable to init SDL: %s\n"<< SDL_GetError()<<endl;
        exit(1);
    }

    //*******************************  INIT SDL_TTF  **************************************************
    TTF_Init();

    //*******************************  INIT SDL_MIXER  **************************************************

    Mix_Init(MIX_INIT_MP3);
    // start SDL with audio support
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        cerr<<"SDL_Init Audio: %s\n"<< SDL_GetError()<<endl;
        exit(1);
    }
    // open 44.1KHz, signed 16bit, system byte order,
    //      stereo audio, using 1024 byte chunks
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        cerr<<"Mix_OpenAudio: %s\n"<< Mix_GetError()<<endl;
        exit(2);
    }
}

void Game::switchFullScreen()
{
    if(FullScreen){
        FullScreen=false;
        SDL_SetWindowFullscreen(ecran,0);
    }else{
        FullScreen=true;
        SDL_SetWindowFullscreen(ecran,SDL_WINDOW_FULLSCREEN);
    }
}
