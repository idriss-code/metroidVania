#include "MusicManager.h"
#include <iostream>


MusicManager::MusicManager()
{
    //ctor
    currentZone = -1;
    music=NULL;

    file[0]="327500_sam.mp3";
    file[1]="830642_Velocity.mp3";
    file[2]="322725_Goa.mp3";
    file[3]="357874_Ambient__44khz_256kbps.mp3";
    file[4]="243749_evergreen.mp3";

}

MusicManager::~MusicManager()
{
    //dtor

    if(music){
        Mix_HaltMusic();//stop la musique
        Mix_FreeMusic(music);
    }
}

void MusicManager::goZone(int val)
{
    if(val != currentZone){
        //unload music
        if(music){
            Mix_HaltMusic();//stop la musique
            Mix_FreeMusic(music);
        }

        //load music
        music = Mix_LoadMUS(("data/music/"+file[val]).c_str());
        if(!music) {
        std::cerr<<"Mix_LoadMUS: "<< Mix_GetError()<<std::endl;
        // this might be a critical error...
        }
        Mix_VolumeMusic(MIX_MAX_VOLUME/3);
        Mix_PlayMusic(music,-1);

        currentZone = val;
    }
}
