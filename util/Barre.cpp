#include "Barre.h"
#include "fonctionDessin.h"
SDL_Rect Barre::position={0,0,0,0};

Barre::Barre(int &val,int &valmax): m_val(val),m_valmax(valmax)
{
    //ctor
    posBarX=0,posBarY=0;
    m_largeur=10;
    m_largeurBord=1;
    m_longueur=100;
    bR=bG=bB=0;
    fR=fG=fB=200;
}

Barre::~Barre()
{
    //dtor
}

void Barre::afficheGD(SDL_Window *ecran)
{

            bar=(m_val*m_longueur)/m_valmax;
            if (bar<=0)bar=0;
            barre=SDL_CreateRGBSurface(0,bar,m_largeur,32,0,0,0,0);
            SDL_FillRect(barre,NULL,SDL_MapRGB(barre->format,fR,fG,fB));
            barreMax=SDL_CreateRGBSurface(0,m_longueur+m_largeurBord*2,m_largeur+m_largeurBord*2,32,0,0,0,0);
            SDL_FillRect(barreMax,NULL,SDL_MapRGB(barreMax->format,bR,bG,bB));


            position.x=posBarX;
            position.y=posBarY;
            SDL_UpperBlit(barreMax,NULL,SDL_GetWindowSurface(ecran),&position);
            position.x=posBarX+m_largeurBord;
            position.y=posBarY+m_largeurBord;
            SDL_UpperBlit(barre,NULL,SDL_GetWindowSurface(ecran),&position);

            SDL_FreeSurface(barre);
            SDL_FreeSurface(barreMax);
}

void Barre::afficheDG(SDL_Window *ecran)
{

            bar=(m_val*m_longueur)/m_valmax;
            if (bar<=0)bar=0;
            barre=SDL_CreateRGBSurface(0,bar,m_largeur,32,0,0,0,0);
            SDL_FillRect(barre,NULL,SDL_MapRGB(barre->format,fR,fG,fB));
            barreMax=SDL_CreateRGBSurface(0,m_longueur+m_largeurBord*2,m_largeur+m_largeurBord*2,32,0,0,0,0);
            SDL_FillRect(barreMax,NULL,SDL_MapRGB(barreMax->format,bR,bG,bB));


            position.x=posBarX;
            position.y=posBarY;
            SDL_UpperBlit(barreMax,NULL,SDL_GetWindowSurface(ecran),&position);
            position.x=posBarX+m_largeurBord;
            position.x=posBarX+m_largeurBord-bar+m_longueur;
            position.y=posBarY+m_largeurBord;
            SDL_UpperBlit(barre,NULL,SDL_GetWindowSurface(ecran),&position);

            SDL_FreeSurface(barre);
            SDL_FreeSurface(barreMax);
}

void Barre::afficheHB(SDL_Window *ecran)
{

            bar=(m_val*m_longueur)/m_valmax;
            if (bar<=0)bar=0;
            barre=SDL_CreateRGBSurface(0,m_largeur,bar,32,0,0,0,0);
            SDL_FillRect(barre,NULL,SDL_MapRGB(barre->format,fR,fG,fB));
            barreMax=SDL_CreateRGBSurface(0,m_largeur+m_largeurBord*2,m_longueur+m_largeurBord*2,32,0,0,0,0);
            SDL_FillRect(barreMax,NULL,SDL_MapRGB(barreMax->format,bR,bG,bB));


            position.x=posBarX;
            position.y=posBarY;
            SDL_UpperBlit(barreMax,NULL,SDL_GetWindowSurface(ecran),&position);
            position.x=posBarX+m_largeurBord;
            position.y=posBarY+m_largeurBord;
            SDL_UpperBlit(barre,NULL,SDL_GetWindowSurface(ecran),&position);

            SDL_FreeSurface(barre);
            SDL_FreeSurface(barreMax);
}

void Barre::afficheBH(SDL_Window *ecran)
{

            bar=(m_val*m_longueur)/m_valmax;
            if (bar<=0)bar=0;
            barre=SDL_CreateRGBSurface(0,m_largeur,bar,32,0,0,0,0);
            SDL_FillRect(barre,NULL,SDL_MapRGB(barre->format,fR,fG,fB));
            barreMax=SDL_CreateRGBSurface(0,m_largeur+m_largeurBord*2,m_longueur+m_largeurBord*2,32,0,0,0,0);
            SDL_FillRect(barreMax,NULL,SDL_MapRGB(barreMax->format,bR,bG,bB));


            position.x=posBarX;
            position.y=posBarY;
            SDL_UpperBlit(barreMax,NULL,SDL_GetWindowSurface(ecran),&position);
            position.x=posBarX+m_largeurBord;
            position.y=posBarY+m_largeurBord-bar+m_longueur;
            SDL_UpperBlit(barre,NULL,SDL_GetWindowSurface(ecran),&position);

            SDL_FreeSurface(barre);
            SDL_FreeSurface(barreMax);
}
void Barre::afficheGDInv(SDL_Window *ecran)
{

            bar=((m_valmax-m_val)*m_longueur)/m_valmax;
            if (bar<=0)bar=0;
            barre=SDL_CreateRGBSurface(0,bar,m_largeur,32,0,0,0,0);
            SDL_FillRect(barre,NULL,SDL_MapRGB(barre->format,fR,fG,fB));
            barreMax=SDL_CreateRGBSurface(0,m_longueur+m_largeurBord*2,m_largeur+m_largeurBord*2,32,0,0,0,0);
            SDL_FillRect(barreMax,NULL,SDL_MapRGB(barreMax->format,bR,bG,bB));


            position.x=posBarX;
            position.y=posBarY;
            SDL_UpperBlit(barreMax,NULL,SDL_GetWindowSurface(ecran),&position);
            position.x=posBarX+m_largeurBord;
            position.y=posBarY+m_largeurBord;
            SDL_UpperBlit(barre,NULL,SDL_GetWindowSurface(ecran),&position);

            SDL_FreeSurface(barre);
            SDL_FreeSurface(barreMax);
}

void Barre::draw(SDL_Window *ecran)
{

            bar=(m_val*m_longueur)/m_valmax;
            if (bar<=0)bar=0;
            barre=SDL_CreateRGBSurface(0,bar,m_largeur,32,0,0,0,0);



            SDL_FillRect(barre,NULL,SDL_MapRGB(barre->format,fR,fG,fB));
// truc tré important de ouf !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            SDL_Surface *barreMax=SDL_CreateRGBSurfaceWithFormat(0, m_longueur+m_largeurBord*2,m_largeur+m_largeurBord*2, 32, SDL_PIXELFORMAT_RGBA32);
            //SDL_SetSurfaceBlendMode(barreMax,SDL_BLENDMODE_BLEND);

            SDL_FillRect(barreMax,NULL,SDL_MapRGBA(barreMax->format,255,0,0,0));
            ligneHorizontale(barreMax,1,0,m_longueur+m_largeurBord*2-2,SDL_MapRGB(barreMax->format,255,255,255));
            ligneHorizontale(barreMax,1,m_largeur+m_largeurBord*2-1,m_longueur+m_largeurBord*2-2,SDL_MapRGB(barreMax->format,255,255,255));
            ligneVerticale(barreMax,0,1,m_largeur+m_largeurBord*2-2,SDL_MapRGB(barreMax->format,255,255,255));
            ligneVerticale(barreMax,m_longueur+m_largeurBord*2-1,1,m_largeur+m_largeurBord*2-2,SDL_MapRGB(barreMax->format,255,255,255));

            position.x=posBarX;
            position.y=posBarY;
            SDL_UpperBlit(barreMax,NULL,SDL_GetWindowSurface(ecran),&position);
            position.x=posBarX+m_largeurBord;
            position.y=posBarY+m_largeurBord;
            SDL_UpperBlit(barre,NULL,SDL_GetWindowSurface(ecran),&position);

            SDL_FreeSurface(barre);
            SDL_FreeSurface(barreMax);
}
