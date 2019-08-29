#ifndef BARRE_H
#define BARRE_H
#include <iostream>
#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/* sert a afficher des barre (cooldown barre de vie) */

class Barre
{
    public:
        Barre(int &val,int &valmax);

        virtual ~Barre();

        int Getval() { return m_val; }
        void Setval(int &val) { m_val = val; }
        int Getvalmax() { return m_valmax; }
        void Setvalmax(int &val) { m_valmax = val; }
        void setPosition(int x,int y){posBarX=x,posBarY=y;}
        void setLLL(int longueur=100,int largeur=15,int largeurBord=1)
        {m_longueur=longueur;m_largeur=largeur;m_largeurBord=largeurBord;}
        void setColor(int R,int G,int B)
        {
            fR=R;
            fG=G;
            fB=B;
        }

        void setBackColor(int R,int G,int B)
        {
            bR=R;
            bG=G;
            bB=B;
        }

        void afficheGD(SDL_Window *ecran);//  affiche Gauche Droite
        void afficheDG(SDL_Window *ecran);
        void afficheHB(SDL_Window *ecran);
        void afficheBH(SDL_Window *ecran);
        void afficheGDInv(SDL_Window *ecran);//  Variante pour les cooldown barre pleine quand cooldown = 0

        void draw(SDL_Window *ecran);

    protected:

    private:
        int m_largeur;
        int m_largeurBord;
        int &m_val;//  valeur courante
        int &m_valmax;
        int m_longueur;
        SDL_Surface *barre;
        SDL_Surface *barreMax;
        int bar,posBarX,posBarY;
        static SDL_Rect position;
        //color RGB
        int fR,fG,fB,bR,bG,bB;

};
//unsigned int Barre::m_largeurBord=1;

#endif // BARRE_H
