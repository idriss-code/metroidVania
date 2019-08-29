#ifndef MENU_H
#define MENU_H

#include <vector>
#include "../util/fonctionTTF.h"
#include "ElementMenu.h"

using namespace std;

class Menu
{
    public:
        Menu();
        Menu(Menu* parent);
        Menu(int x,int y,TTF_Font *police=NULL,int hauteurLigne=12,int longueur=150);
        virtual ~Menu();

        void setLongueur(int longueur){m_longueur=longueur;}

        void setPolice(TTF_Font *val){m_police=val;}
        void destroyPolice(){TTF_CloseFont(m_police);}

        int longueur()const{return m_longueur;}
        int hauteurLigne()const{return m_hauteurLigne;}
        int vecSize()const{return vec.size();}

        //  retouyne l'element du menu actif
        ElementMenu* actif() { return *m_actif; }

        //  ajoute un element au menu
        void addElement(ElementMenu* val){vec.push_back(val);m_actif=vec.begin();}

        //  affichage du menu
        virtual void affiche(SDL_Window *ecran);

        //permet la navigation au clavier
        void up(){if(m_actif!=vec.begin())m_actif--;}
        void down(){if(m_actif!=vec.end()-1)m_actif++;}

        //permet l activation au clavier
        static void activation(){m_active=true;}
        static void finActivation(){m_active=false;}
        static bool active(){return m_active;}

        //  permet d'acceder a un element via truc[]
        ElementMenu* operator[](int val){return vec[val];}

        //  gestion du menu actif
        static Menu* menuActif(){return m_menuActif;}
        static void setMenuActif(Menu* val){m_menuActif=val;}
        Menu* menuParent()const{return m_menuParent;}

        //  gestion position menu
        SDL_Rect position(){SDL_Rect pos; pos.x=m_x; pos.y=m_y; return pos;}
        void setPosition(int x,int y){m_x=x;m_y=y;}

        //gestion de la souris
        void onMouse(int x,int y);

        //  GESTION COMPLETE DU MENU

        static int updateMenu(int val=0);

    protected:

    //private:
        //  positionj du menu
        int m_x;
        int m_y;

        int m_longueur;
        int m_hauteurLigne;

        Menu* m_menuParent;

        vector<ElementMenu*> vec;
        vector<ElementMenu*>::iterator it, m_actif;

        TTF_Font *m_police;


        //permet l activation au clavier
        static bool m_active;
        static Menu* m_menuActif;

};

#endif // MENU_H
