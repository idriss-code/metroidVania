#ifndef FONCTIONTTF_H_INCLUDED
#define FONCTIONTTF_H_INCLUDED


#include <SDL_ttf.h>


//  fonctions pour la gestion du texte

void afficheTexte(SDL_Rect position,const char *txt,SDL_Window *ecran,TTF_Font *police,SDL_Color color);
void afficheInt(SDL_Rect position,int nombre,SDL_Window *ecran,TTF_Font *police,SDL_Color color);

//  affiche 2 nombres seraré par une barre de fraction genre PV/PVMAX
void afficheIntSurInt(SDL_Rect position,int nombre1,int nombre2,SDL_Window *ecran,TTF_Font *police,SDL_Color color);


#endif // FONCTIONTTF_H_INCLUDED
