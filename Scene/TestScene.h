#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "../core/Scene.h"

class TestScene : public Scene
{
    public:
        TestScene();
        virtual ~TestScene();

    protected:
        virtual void load();
        virtual void unload();
        virtual void input();
        virtual void update(int dt);
        virtual void draw();
    private:
        bool menu;
        bool message;
};

#endif // TESTSCENE_H
