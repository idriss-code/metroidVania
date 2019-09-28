#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <SDL_mixer.h>
#include <string>

class MusicManager
{
    public:
        MusicManager();
        virtual ~MusicManager();
        void goZone(int val);

    protected:

    private:
        int currentZone;
        Mix_Music *music;
        std::string file[10];
};

#endif // MUSICMANAGER_H
