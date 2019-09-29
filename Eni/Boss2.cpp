#include "Boss2.h"

#include "../Player.h"

#include "../CustomCollection.h"
#include "../Bullet.h"

extern Player player;

Boss2::Boss2(int x,int y):Robot(x,y)
{
    m_pv=400;
}

Boss2::~Boss2()
{

}

void Boss2::onDying(CustomCollection<Item>*)
{
    player.setKey(true,5);
}

void Boss2::fireUpdate(CustomCollection<Bullet>* bullets)
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
