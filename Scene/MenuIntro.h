#ifndef MenuIntro_H
#define MenuIntro_H

#include "../core/Scene.h"
#include "../menu/Menu.h"


class MenuIntro : public Scene
{
    public:
        MenuIntro(Scene* parent = NULL);
        virtual ~MenuIntro();
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

#endif // MenuIntro_H
