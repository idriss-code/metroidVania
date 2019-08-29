 #include"fonctionTTF.h"

 #include <cstdio>
    SDL_Color NOIR = {0, 0, 0};
    SDL_Color VERT = {0, 240, 0};
    SDL_Color GRIS = {50,50,50};
    SDL_Color BLANC  = {255,255,255};
    SDL_Color JAUNE  = {255,255,0};
    SDL_Color ROUGE  = {255,0,0};

void afficheTexte(SDL_Rect position,const char *txt,SDL_Window *ecran,TTF_Font *police,SDL_Color color)
{
    SDL_Surface *texte;
    texte=TTF_RenderText_Blended(police,txt,color);
    SDL_UpperBlit(texte,NULL,SDL_GetWindowSurface(ecran),&position);
    SDL_FreeSurface(texte);
}

void afficheInt(SDL_Rect position,int nombre,SDL_Window *ecran,TTF_Font *police,SDL_Color color)
{
    char txt[10];
    sprintf(txt,"%d",nombre);
    afficheTexte(position,txt,ecran,police,color);
}
void afficheIntSurInt(SDL_Rect position,int nombre1,int nombre2,SDL_Window *ecran,TTF_Font *police,SDL_Color color)
{
    char txt[10];
    sprintf(txt,"%d/%d",nombre1, nombre2);
    afficheTexte(position,txt,ecran,police,color);
}
