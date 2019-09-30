#include "Item.h"
#include <iostream>


Item::Item(int x,int y)//
{
    m_height=32;
    m_width=32;

    m_posX=x ;
    m_posY=y ;
}

Item::~Item()
{

}


void Item::loadSound()
{
    //**************** sfx ****************
    sound=Mix_LoadWAV("data/son/DM-CGS-41.WAV");
    if(!sound) {
        std::cerr<<"Mix_LoadWAV: "<< Mix_GetError()<<std::endl;
    }
}

void Item::unloadSound()
{
    //**************** sfx ****************
    Mix_FreeChunk(sound);
    sound=NULL;
}



void Item::playSound()
{
    Mix_PlayChannel(-1, sound, 0);
}


Mix_Chunk * Item::sound=NULL;

