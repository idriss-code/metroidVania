#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <SDL.h>

bool pointCollision(int x,int y,SDL_Rect box);
bool boxCollision(SDL_Rect box1,SDL_Rect box2);
bool CollisionDroiteSeg(SDL_Point A,SDL_Point B,SDL_Point O,SDL_Point P);
bool CollisionSegSeg(SDL_Point A,SDL_Point B,SDL_Point O,SDL_Point P);
bool CollisionSegSeg(int Ax ,int Ay ,int Bx ,int By,int Ox ,int Oy,int Px ,int Py);

struct Cercle
{
   int x,y;
   int rayon;
};
// gestion des cercles
bool Collision(int x,int y,Cercle C);
bool CollisionPointCercle(SDL_Point A,Cercle C);
bool Collision(Cercle C1,Cercle C2);
bool CollisionDroite(SDL_Point A,SDL_Point B,Cercle C);
bool CollisionSegment(SDL_Point A,SDL_Point B,Cercle C);
bool CollisionCercleRect(Cercle C1,SDL_Rect box1);
#endif // COLLISION_H_INCLUDED
