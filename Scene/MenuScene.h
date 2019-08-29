#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "../core/Scene.h"
#include "../menu/Menu.h"


class MenuScene : public Scene
{
    public:
        MenuScene(Scene* parent = NULL);
        virtual ~MenuScene();
        static void loach(Scene* parent);
        virtual void draw();

    protected:
        virtual void load();
        virtual void unload();
        virtual void update(int dt);
        void input();


    private:
        Menu *mPrincipal;
};

#endif // MENUSCENE_H
