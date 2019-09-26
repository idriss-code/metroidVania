#ifndef BULLET_H
#define BULLET_H
#include <SDL.h>
#include <vector>
using namespace std;

class Bullet
{
    public:
        enum from {AMI,ENI};

        Bullet(int x, int y, float angle,from fm,int speed=25);
        virtual ~Bullet();

        from GetTag(){ return frm; }

        int GetposX() { return posX; }
        void SetposX(int val) { posX = val; }
        int GetposY() { return posY; }
        void SetposY(int val) { posY = val; }
        int GetvelX() { return velX; }
        void SetvelX(int val) { velX = val; }
        int GetvelY() { return velY; }
        void SetvelY(int val) { velY = val; }

        void update();
        void draw(int camX,int camY);

        static vector<Bullet> vec;
        static vector<Bullet>::iterator it;

        static void load();
        static void unload();


    protected:

    private:
        int posX;
        int posY;
        int velX;
        int velY;

        static SDL_Surface *m_sprite1;
        static SDL_Surface *m_sprite2;

        from frm;
};

#endif // BULLET_H
