#include "Key.h"

#include "../Player.h"
extern Player player;
extern SDL_Window *ecran;
#include "../gfx/SDL2_rotozoom.h"


Key::Key(int x,int y,int keyNumber):Item(x,y)
{
    //ctor

    m_keyNumber=keyNumber;

    SDL_Surface* temp=IMG_Load("./data/sprite/keyCard.png");
    sprite=rotozoomSurfaceXY(temp,0,2,2,0);
    SDL_FreeSurface(temp);
}

Key::~Key()
{
    //free surface
    SDL_FreeSurface(sprite);
    //dtor
}

void Key::action(Scene* parent)
{
    player.setKey(true,m_keyNumber);

    std::cout<<"item action"<<std::endl;
}

void Key::draw(int camX,int camY)
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
    src.h=24;
    src.x=(m_keyNumber-1)*src.w;
    src.y=0;
    pos.x=m_posX-camX-src.w/2;
    pos.y=m_posY-camY-src.h/2;
    SDL_BlitSurface(sprite,&src,SDL_GetWindowSurface(ecran),&pos);
}
