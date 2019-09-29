#include "Boss3.h"

#include "../Player.h"
#include "../Scene/ScreenMessage.h"
#include "../CustomCollection.h"
#include "../Bullet.h"
#include "../MyGame.h"
extern Player player;
extern Game* game;

Boss3::Boss3(int x,int y):Insect2(x,y)
{
    m_pv=500;
}

Boss3::~Boss3()
{

}

void Boss3::onDying(CustomCollection<Item>*)
{
    #ifdef DEBUG
        cout<<"the end"<<endl;
    #endif

    ScreenMessage::loach("congratulation",game->currentScene(),50);
    ScreenMessage::loach("the end",game->currentScene(),50);
    dynamic_cast<MyGame *>(game)->reBoot();
}

void Boss3::fireUpdate(CustomCollection<Bullet>* bullets)
{
    if(--fireTime<=0){
        fireTime=fireCooldown;
        float angle=atan2(player.posY()-posY(),player.posX()-posX());
        bullets->add(new Bullet(this->posX(),this->posY(),angle+M_PI/6,Bullet::ENI,10));
        bullets->add(new Bullet(this->posX(),this->posY(),angle,Bullet::ENI,10));
        bullets->add(new Bullet(this->posX(),this->posY(),angle-M_PI/6,Bullet::ENI,10));
        changeOrientation();
        #ifdef DEBUG
            cout<<"fire"<<endl;
        #endif
    }
}

/*
    Bullet bullet(posX()+cos(angle)*30,posY()+sin(angle)*30,angle,Bullet::ENI);
    Bullet::vec.push_back(bullet);
    Bullet bullet2(posX()+cos(angle+M_PI/6)*30,posY()+sin(angle+M_PI/6)*30,angle,Bullet::ENI);
    Bullet::vec.push_back(bullet2);
    Bullet bullet3(posX()+cos(angle-M_PI/6)*30,posY()+sin(angle-M_PI/6)*30,angle,Bullet::ENI);
    Bullet::vec.push_back(bullet3);
    Mix_PlayChannel(-1, fireSound, 0);
*/
