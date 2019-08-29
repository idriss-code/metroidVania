#include "Menu.h"
#include "../util/collision.h"//pour gestion souris

extern SDL_Color NOIR;
extern SDL_Color VERT;
extern SDL_Color GRIS;
extern SDL_Color ROUGE;

Menu::Menu():m_x(0),m_y(0),m_longueur(150),m_hauteurLigne(10),m_menuParent(this)
{
    //ctor
}

Menu::Menu(Menu* parent):
    m_longueur(parent->m_longueur),m_hauteurLigne(parent->m_hauteurLigne),m_menuParent(parent),m_police(parent->m_police)
{
    setPosition(parent->position().x,parent->position().y);

    //ctor
}

Menu::Menu(int x,int y,TTF_Font *police,int hauteurLigne,int longueur):
    m_x(x),m_y(y),m_longueur(longueur),m_hauteurLigne(hauteurLigne),m_menuParent(this),m_police(police)
{
    //ctor
}


Menu::~Menu()
{
    //dtor

    for(it=vec.begin();it!=vec.end();it++){
            delete *it;
        }
}

void Menu::affiche(SDL_Window *ecran)
{
    SDL_Rect pos=position();
    for(it=vec.begin();it!=vec.end();it++){
            if(it==m_actif){
                afficheTexte(pos,(*it)->name(),ecran,m_police,ROUGE);
            }else{
                afficheTexte(pos,(*it)->name(),ecran,m_police,GRIS);
            }
            pos.y+=m_hauteurLigne;
        }

}

void Menu::onMouse(int x,int y)
{
    SDL_Rect pos=position();
    pos.h=m_hauteurLigne;
    pos.w=m_longueur;//a verifier1 a optimiser ??????????????
    for(it=vec.begin();it!=vec.end();it++){
            if(pointCollision(x,y,pos)){
                m_actif=it;
                break;
            }
            pos.y+=m_hauteurLigne;
        }
}

int Menu::updateMenu(int val){
    if(active()){
        finActivation();
        return menuActif()->actif()->action(val);
    }
    else{return val;}
}

Menu* Menu::m_menuActif=NULL;
bool Menu::m_active=false;
