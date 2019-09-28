#ifndef INTRO_H
#define INTRO_H

#include "../core/Scene.h"

class Intro : public Scene
{
    public:
        Intro();
        virtual ~Intro();

    protected:
        virtual void load();
        virtual void unload();
        virtual void input();
        virtual void update(int dt);
        virtual void draw();
    private:
};

#endif // INTRO_H
