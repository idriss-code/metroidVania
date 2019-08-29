/* pour compilation necessite SDL 2
C:\Program Files (x86)\CodeBlocks\SDL2-2.0.5
C:\Program Files (x86)\CodeBlocks\SDL2_ttf-2.0.14
C:\Program Files (x86)\CodeBlocks\SDL2_image-2.0.1

voir les .h pour présentation et commentaire

version pré-alpha 0.17 Idriss Benhamadouche (benlamouche78) 2016/2018
*/

#include "../MyGame.h"

Game* game=NULL;

int main ( int argc, char** argv )
{
    game=new MyGame;
    game->main();
    return 0;
}
