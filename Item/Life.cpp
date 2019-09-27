#include "Life.h"

#include "../Player.h"
extern Player player;
extern SDL_Window *ecran;
#include "../gfx/SDL2_rotozoom.h"
#include "../core/Scene.h"
#include "../Scene/ScreenMessage.h"


Life::Life(int x,int y):Item(x,y)
{
    //ctor

    SDL_Surface* temp=IMG_Load("./data/sprite/life.png");
    sprite=rotozoomSurfaceXY(temp,0,2,2,0);
    SDL_FreeSurface(temp);

    spriteNumber=0;
    countD=2;
}

Life::~Life()
{
    //free surface
    SDL_FreeSurface(sprite);
    //dtor
}

void Life::action(Scene* parent)
{
    player.gainPv(5);
}

void Life::draw(int camX,int camY)
{
    SDL_Rect pos;


    #ifdef DEBUG
     //affichage hitBox
    SDL_Surface* hitBoxSprite=SDL_CreateRGBSurface(0,hitBox().w,hitBox().h,32,0,0,0,0);
    SDL_FillRect(hitBoxSprite,NULL,SDL_MapRGB(hitBoxSprite->format,255,255,255));
    pos.x=hitBox().x-camX;
    pos.y=hitBox().y-camY;
    SDL_BlitSurface(hitBoxSprite,NULL,SDL_GetWindowSurface(ecran),&pos);
    SDL_FreeSurface(hitBoxSprite);
    #endif

    //affichage sprite
    SDL_Rect src;
    src.w=32;
    src.h=32;
    if(--countD<0)spriteNumber++,countD=2;
    src.x=(spriteNumber<3?spriteNumber:spriteNumber=0)*src.w;
    src.y=0;
    pos.x=m_posX-camX-src.w/2;
    pos.y=m_posY-camY-src.h/2;
    SDL_BlitSurface(sprite,&src,SDL_GetWindowSurface(ecran),&pos);
}
